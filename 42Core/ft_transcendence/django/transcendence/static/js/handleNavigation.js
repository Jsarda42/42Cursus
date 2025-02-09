import { checkAuth } from "./check_auth.js"
import { getAuth } from "./get_auth.js"
import { loadLeaderboardPage, loadHomePage, loadPongPage, loadProfilPage, loadSigninPage, loadSignupPage } from "./loader.js"
import { connectWss, initWebSocket} from './Socket.js';
import { runMulti, falseRunMulti} from "./pong_multi.js";
import { runLocal, falseRunLocal } from "./pong_local.js";
import { runTournament, falserunTournament } from "./pong_tournament.js";
import { runUltra, falseRunUltra } from "./pong_ultra.js";
import { runIA, falseRunIA } from "./pong_ia.js";
function quitGame()
{
	if (runMulti || runLocal || runIA || runTournament || runUltra){
		falseRunMulti();
		falseRunIA();
		falseRunLocal();
		falserunTournament();
		falseRunUltra();
	}
}

document.addEventListener("DOMContentLoaded", function () {
	const pongLink = document.getElementById("pong-link");
	const leaderboardLink = document.getElementById("leaderboard-link");
	const homeLink = document.getElementById("home-link");
	const signinLink = document.getElementById("signin-link");
	const signupLink = document.getElementById("signup-link");
	const logoutBtn = document.getElementById("logout-btn");
	const usernameElement = document.getElementById("username_info");
	const userProfileImg = document.getElementById("user-profile-img");
	const profilLink = document.getElementById("profil-link");

	initWebSocket();

	const updateDropdownMenu = (isAuthenticated, userData) => {
		//console.log(userData)
		if (isAuthenticated.isAuthenticated && userData) {
			const baseUrl = "";
			const mediaUrl = userData.data.profile.avatar || "/static/images/login.jpg";
			const fullUrl = `${baseUrl}${mediaUrl}`;

			usernameElement.textContent = userData.data.user.username || "User";
			userProfileImg.src = fullUrl || "https://github.com/mdo.png";
			signinLink.style.display = "none";
			signupLink.style.display = "none";
			logoutBtn.style.display = "block";

			// Logout logic
			logoutBtn.addEventListener("click", function (event) {
				event.preventDefault();
				const csrfToken = document.cookie.match(/csrftoken=([^;]+)/)?.[1];
				fetch("/logout/", {
					method: "POST",
					headers: {
						"Content-Type": "application/json",
						"X-CSRFToken": csrfToken,
					},
					credentials: "same-origin",
				})
					.then((response) => {
						if (response.ok) {
							//console.log("Logged out successfully");
							if (connectWss) {
								connectWss.close();
								//console.log("WebSocket closed.");
							}
							loadHomePage();
							updateDropdownMenu({ isAuthenticated: false }, null);
						} else {
							console.error("Error logging out");
						}
					})
					.catch((error) => console.error("Error logging out:", error));
			});
		} else {
			usernameElement.textContent = "";
			userProfileImg.src = "/static/images/login.jpg";
			signinLink.style.display = "block";
			signupLink.style.display = "block";
			logoutBtn.style.display = "none";
		}
	};

	const updateProfileView = (isAuthenticated, userData) => {
		const waitForElements = () => {
			const profilePic = document.querySelector("#profil-content .profile-pic");
			const profileNameEdit = document.querySelector("#profil-content .profile-name-edit");
			if (profilePic && profileNameEdit) {
				clearInterval(checkInterval);
				const baseUrl = "https://localhost:3000";
				const mediaUrl = userData.data.profile.avatar || "/static/images/login.jpg";
				const fullUrl = `${baseUrl}${mediaUrl}`;
				//console.log(fullUrl);

				if (isAuthenticated) {
					profilePic.src = fullUrl || "https://github.com/mdo.png";
					//console.log(userData.data.user.username);
					profileNameEdit.value = userData.data.user.username || "User";

					fetch("api/wl/", { credentials: "include" })
                    .then(response => response.json())
                    .then(data => {
                        //console.log("Win/Loss Data:", data); // Console log the data
                    })
                    .catch(error => console.error("Error fetching win/loss:", error));

                // Fetch match history
                fetch("api/matchhistory", { credentials: "include" })
                    .then(response => response.json())
                    .then(data => {
                        //console.log("Match History Data:", data); // Console log the data
                     
                    })
                    .catch(error => console.error("Error fetching match history:", error));

				} else {
					profilePic.src = "/static/images/login.jpg";
					profileNameEdit.value = "User";
					profileNameEdit.disabled = true;
					console.warn("User not authenticated on profile page");
				}

				const containers = document.querySelectorAll("#profil-content .data-container");
				containers.forEach(container => {
					if (isAuthenticated && userData.data.user.username) {
						container.querySelector("input").style.display = "block";
						container.querySelector("input").value = userData.data.user.username;
						profilePic.classList.remove("not-you");
					} else {
						container.querySelector("input").style.display = "none";
						profilePic.classList.add("not-you");
					}
				});
			}
		};

		const checkInterval = setInterval(waitForElements, 100);
	};

	checkAuth().then((auth_status) => {
		if (auth_status.isAuthenticated) {
			getAuth().then((data) => {
				updateDropdownMenu(auth_status, data);
				updateProfileView(auth_status, data);
			});
		}
		else {
			updateDropdownMenu(auth_status, null);
		}
	});

	pongLink.addEventListener("click", function (event) {
		event.preventDefault();
		history.pushState({ page: "pong" }, "Pong", "/pong");
		loadPongPage();
	});

	profilLink.addEventListener("click", function (event) {
		quitGame();
		event.preventDefault();
		history.pushState({ page: "profil" }, "Profil", "/profil");
		loadProfilPage();
	});

	leaderboardLink.addEventListener("click", function (event) {
		//console.log("clicking leaderboard link")
		//console.log("clicking leaderboard link")
		quitGame();
		event.preventDefault();
		history.pushState({ page: "leaderboard" }, "Leaderboard", "/leaderboard");
		loadLeaderboardPage();
	});

	homeLink.addEventListener("click", function (event) {
		quitGame();
		event.preventDefault();
		history.pushState({ page: "home" }, "Home", "/home");
		loadHomePage();
	});

	signinLink.addEventListener("click", function (event) {
		quitGame();
		event.preventDefault();
		history.pushState({ page: "signin" }, "Sign In", "/signin");
		loadSigninPage();
	});

	signupLink.addEventListener("click", function (event) {
		quitGame();
		event.preventDefault();
		history.pushState({ page: "signup" }, "Sign Up", "/signup");
		loadSignupPage();
	});

	window.addEventListener("popstate", function (event) {
		const state = event.state;
		if (state) {
			quitGame();
			if (state.page === "pong") {
				loadPongPage();
			} else if (state.page === "leaderboard") {
				loadLeaderboardPage();
			} else if (state.page === "signin") {
				loadSigninPage();
			} else if (state.page === "signup") {
				loadSignupPage();
			} else if (state.page === "profil") {
				loadProfilPage();
			} else {
				loadHomePage();
			}
		}
	});

	document.body.addEventListener("click", function (event) {
		const target = event.target;

		if (target && target.id === "signup-link") {
			event.preventDefault();
			history.pushState({ page: "signup" }, "Sign Up", "/signup");
			quitGame();
			loadSignupPage();
		}

		if (target && target.id === "signin-link") {
			event.preventDefault();
			history.pushState({ page: "signin" }, "Sign In", "/signin");
			quitGame();
			loadSigninPage();
		}
	});

	const currentPath = window.location.pathname;

	if (currentPath === "/pong") {
		quitGame();
		loadPongPage();
	} else if (currentPath === "/leaderboard") {
		quitGame();
		loadLeaderboardPage();
	} else if (currentPath === "/signin") {
		quitGame();
		loadSigninPage();
	} else if (currentPath === "/signup") {
		quitGame();
		loadSignupPage();
	} else if (currentPath === "/profil") {
		quitGame();
		loadProfilPage();
	} else {
		quitGame();
		loadHomePage();
	}
});