import { getAuth } from "./get_auth.js"
import { initPongGame } from "./pong.js";
import { applyTranslation, getSavedLanguage } from "./translation.js";
import { initializeSigninForm } from "./signin.js"
import { initializeSignupForm } from "./signup.js"
import { checkAuth } from "./check_auth.js";
import { game_ia } from "./pong_ia.js";
import { game_multi } from "./pong_multi.js";
import { game_local } from "./pong_local.js";
import { loadLeaderboard } from "./leaderboard.js";
import { tournament } from "./pong_tournament.js"; // tourmament
import { game_ultra } from "./pong_ultra.js";
import { ProfileUploader } from "./profil.js";



const loadCSS = (href) => {
	if (!document.querySelector(`link[href="${href}"]`)) {
		const link = document.createElement('link');
		link.rel = 'stylesheet';
		link.href = href;
		document.head.appendChild(link);
	}
};

const loadJS = (src, callback) => {
	if (!document.querySelector(`script[src="${src}"]`)) {
		let script = document.createElement('script');
		script.src = src;
		script.type = 'module';
		script.onload = callback;
		document.body.appendChild(script);
	} else if (callback) {
		callback();
	}
};

export const loadSigninPage = () => {
	const mainContent = document.getElementById("main-content");
	fetch("/static/signin.html")
		.then(response => response.text())
		.then(data => {
			mainContent.innerHTML = data;
			loadCSS("/static/css/signin.css");
			loadJS("/static/js/signin.js", function () {
				initializeSigninForm();
			});
		})
		.catch(error => console.error("Error loading SignIn page:", error));
};

// tournament
export const loadPongTournamentPage = async () => {
	//console.log("Checking auth...");
	const authStatus = await checkAuth();

	if (!authStatus.isAuthenticated) {
		//console.log("User not authenticated, redirecting to login...");
		loadSigninPage();
		return;
	}

	const mainContent = document.getElementById("main-content");
	fetch("/static/pong_tournament.html")
		.then(response => response.text())
		.then(data => {
			mainContent.innerHTML = data;

			// Load Tournament Game Logic
			let script = document.createElement('script');
			script.src = '/static/js/pong_tournament.js';
			script.type = 'module';
			script.onload = function () {
				//console.log('Tournament script loaded');
				tournament();
			};
			document.body.appendChild(script);
		})
		.catch(error => console.error("Error loading Tournament page:", error));
};

async function top3Users() {
	try {
		const response = await fetch('/api/leaderboard/');
		if (!response.ok) {
			throw new Error("Failed to fetch leaderboard data");
		}

		const leaderboardData = await response.json();

		leaderboardData.sort((a, b) => b.wins - a.wins);


		return leaderboardData.slice(0, 3);
	} catch (error) {
		console.error("Error fetching top 3 users:", error);
		return [];
	}
}


export const loadHomePage = () => {
	const mainContent = document.getElementById("main-content");

	fetch("/static/home.html")
		.then(response => response.text())
		.then(async data => {
			mainContent.innerHTML = data;

			const savedLanguage = getSavedLanguage();
			applyTranslation(savedLanguage);

			if (!document.querySelector('script[src="/static/js/translation.js"]')) {
				let script = document.createElement('script');
				script.src = '/static/js/translation.js';
				script.type = 'module';
				script.onload = function () {
					//console.log('Translation script loaded successfully');
				};
				document.body.appendChild(script);
			}

			const top3 = await top3Users();
			if (top3.length >= 3) {
				const playerCards = document.querySelectorAll(".leaderboard-card-container");

				top3.forEach((user, index) => {
					const card = playerCards[index];

					const imgTag = card.querySelector(".card-img-top");
					const titleTag = card.querySelector(".card-title");
					imgTag.src = user.avatar && user.avatar.url ? user.avatar.url : '/static/images/login.jpg';
					titleTag.textContent = user.username; 
				});
			}
		})
		.catch(error => console.error("Error loading Home page:", error));
};




export const loadProfilPage = async () => {
	//console.log("Checking auth...");
	const authStatus = await checkAuth();

	if (!authStatus.isAuthenticated) {
		//console.log("User not authenticated, redirecting to login...");
		loadSigninPage()
		return;
	}

	//console.log("User is authenticated, loading profile page...");
	const mainContent = document.getElementById("main-content");
	const response = await fetch("/static/profil.html");
	const data = await response.text();
	mainContent.innerHTML = data;

	const savedLanguage = getSavedLanguage();
	applyTranslation(savedLanguage);
	const authData = await getAuth();
	const profileImage = document.querySelector(".profile-pic");
	const profileNameEdit = document.querySelector("#profil-content .profile-name-edit");
	if (profileNameEdit) {
		profileNameEdit.value = authData.data.user.username || "User";
	}
	if (profileImage && authData.data.profile.avatar) {
		profileImage.src = authData.data.profile.avatar;
	}
	else {
		profileImage.src = "/static/images/login.jpg"
	}
	loadCSS("/static/css/profil.css");
	loadJS("/static/js/profil.js");

	if (!document.querySelector('script[src="/static/js/translation.js"]')) {
		const script = document.createElement("script");
		script.src = "/static/js/translation.js";
		script.type = "module";
		document.body.appendChild(script);
	}

	new ProfileUploader(
		".profile-pic", "/api/avatar/",
		".profile-name-edit", "/api/username/",
		".profile-name-btn-save", ".profile-name-btn-edit", ".profile-name-btn-reset"
	);
};


export const loadPongPage = async () => {
	//console.log("Checking auth...");
	const authStatus = await checkAuth();

	if (!authStatus.isAuthenticated) {
		//console.log("User not authenticated, redirecting to login...");
		loadSigninPage()
		return;
	}
	const mainContent = document.getElementById("main-content");

	fetch("/static/pong.html")
		.then(response => response.text())
		.then(data => {
			mainContent.innerHTML = data;

			if (!document.querySelector('script[src="/static/js/pong.js"]')) {
				let script = document.createElement('script');
				script.src = '/static/js/pong.js';
				script.type = 'module';
				script.onload = function () {
					//console.log('Pong game script loaded');
					initPongGame();
				};
				document.body.appendChild(script);
			} else {
				initPongGame();
			}
		})
		.catch(error => console.error("Error loading Pong game:", error));

};

export const loadMultiPage = async () => {
	//console.log("Checking auth...");
	const authStatus = await checkAuth();

	if (!authStatus.isAuthenticated) {
		//console.log("User not authenticated, redirecting to login...");
		loadSigninPage()
		return;
	}
	const mainContent = document.getElementById("main-content");

	fetch("/static/pong_multi.html")
		.then(response => response.text())
		.then(data => {
			mainContent.innerHTML = data;

			if (!document.querySelector('script[src="/static/js/pong_multi.js"]')) {
				let script = document.createElement('script');
				script.src = '/static/js/pong_multi.js';
				script.type = 'module';
				script.onload = function () {
					//console.log('Multi Pong game script loaded');
					game_multi();
				};
				document.body.appendChild(script);
			} else {
				game_multi();
			}
		})
		.catch(error => console.error("Error loading Pong game:", error));

};

export const loadUltraPage = async () => {
	//console.log("Checking auth...");
	const authStatus = await checkAuth();

	if (!authStatus.isAuthenticated) {
		//console.log("User not authenticated, redirecting to login...");
		loadSigninPage()
		return;
	}
	const mainContent = document.getElementById("main-content");
	if (!mainContent.querySelector("#pong-canvas")) {
		fetch("/static/pong_ultra.html")
			.then(response => response.text())
			.then(data => {
				mainContent.innerHTML = data;

				if (!document.querySelector('script[src="/static/js/pong_ultra.js"]')) {
					let script = document.createElement('script');
					script.src = '/static/js/pong_ultra.js';
					script.type = 'module';
					script.onload = function () {
						//console.log('Ultra Pong game script loaded');
						game_ultra();
					};
					document.body.appendChild(script);
				} else {
					game_ultra();
				}
			})
			.catch(error => console.error("Error loading Pong game:", error));
	}
};

export const loadPongIAPage = async () => {
	//console.log("Checking auth...");
	const authStatus = await checkAuth();

	if (!authStatus.isAuthenticated) {
		//console.log("User not authenticated, redirecting to login...");
		loadSigninPage()
		return;
	}
	const mainContent = document.getElementById("main-content");

	fetch("/static/pong_ia.html")
		.then(response => response.text())
		.then(data => {
			mainContent.innerHTML = data;

			if (!document.querySelector('script[src="/static/js/pong_ia.js"]')) {
				let script = document.createElement('script');
				script.src = '/static/js/pong_ia.js';
				script.type = 'module';
				script.onload = function () {
					//console.log('IA Pong game script loaded');
					game_ia();
				};
				document.body.appendChild(script);
			} else {
				game_ia();
			}
		})
		.catch(error => console.error("Error loading Pong game:", error));

};

export const loadPongLocalPage = async () => {
	//console.log("Checking auth...");
	const authStatus = await checkAuth();

	if (!authStatus.isAuthenticated) {
		//console.log("User not authenticated, redirecting to login...");
		loadSigninPage()
		return;
	}
	const mainContent = document.getElementById("main-content");

	fetch("/static/pong_local.html")
		.then(response => response.text())
		.then(data => {
			mainContent.innerHTML = data;

			if (!document.querySelector('script[src="/static/js/pong_local.js"]')) {
				let script = document.createElement('script');
				script.src = '/static/js/pong_local.js';
				script.type = 'module';
				script.onload = function () {
					//console.log('Pong game script loaded');
					game_local();
				};
				document.body.appendChild(script);
			} else {
				game_local();
			}
		})
		.catch(error => console.error("Error loading Pong game:", error));

};

export const loadLeaderboardPage = async () => {
	//console.log("Checking auth...");
	const authStatus = await checkAuth();

	if (!authStatus.isAuthenticated) {
		//console.log("User not authenticated, redirecting to login...");
		loadSigninPage()
		return;
	}
	const mainContent = document.getElementById("main-content");

	fetch("/static/leaderboard.html")
		.then(response => response.text())
		.then(async (data) => {
			mainContent.innerHTML = data;
			loadCSS("/static/css/leaderboard.css");
			loadJS("/static/js/translation.js");
			const authData = await getAuth();
			const savedLanguage = getSavedLanguage();
			const profileImage = document.querySelector("#user-leaderboard-img");
			const profileUserName = document.querySelector("#user-leaderboard-username");
			applyTranslation(savedLanguage);
			if (profileImage && authData.data.profile.avatar && profileUserName) {
				profileImage.src = authData.data.profile.avatar;
			}
			else {
				profileImage.src = "/static/images/login.jpg"
			}
			if (profileUserName)
				profileUserName.textContent = authData.data.user.username || "User";

			if (!document.querySelector('script[src="/static/js/translation.js"]')) {
				let script = document.createElement('script');
				script.src = '/static/js/translation.js';
				script.type = 'module';
				script.onload = function () {
					//console.log('Translation script loaded successfully');
				};
				document.body.appendChild(script);
			}

			if (!document.querySelector('script[src="/static/js/leaderboard.js"]')) {
				//console.log("script loader")
				let leaderboardScript = document.createElement('script');
				leaderboardScript.src = '/static/js/leaderboard.js';
				leaderboardScript.type = 'module';
				leaderboardScript.onload = function () {
					//console.log('Leaderboard script loaded successfully');
					if (typeof loadLeaderboard === 'function') {
						loadLeaderboard();
					} else {
						console.error("loadLeaderboard function not found in leaderboard.js");
					}
				};
				document.body.appendChild(leaderboardScript);
			} else {
				loadLeaderboard();
			}
		})
		.catch(error => console.error("Error loading Home page:", error));

};

export const loadSignupPage = () => {
	const mainContent = document.getElementById("main-content");

	fetch("/static/signup.html")
		.then(response => response.text())
		.then(data => {
			mainContent.innerHTML = data;
			loadCSS("/static/css/signup.css");
			loadJS("/static/js/signup.js", function () {
				initializeSignupForm();
			});
		})
		.catch(error => console.error("Error loading SignUp page:", error));

};



