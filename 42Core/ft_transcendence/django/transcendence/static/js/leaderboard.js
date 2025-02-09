import { getAuth } from "./get_auth.js";
import { loadLeaderboardPage } from "./loader.js";

export async function loadLeaderboard() {
	//console.log("Fetching leaderboard data...");
	try {
		const response = await fetch('/api/leaderboard/');
		if (!response.ok) throw new Error("Failed to fetch leaderboard data");

		const leaderboardData = await response.json();
		leaderboardData.sort((a, b) => b.wins - a.wins);

		//console.log("Leaderboard Data:", leaderboardData);

		const leaderboardContainer = document.querySelector(".user-items");
		if (!leaderboardContainer) {
			//console.log("Leaderboard container not found!");
			return;
		}

		leaderboardContainer.innerHTML = "";
		const authData = await getAuth();

		let rank = 1;
		for (const user of leaderboardData) {
			//console.log("User data:", user);
			const userItem = document.createElement("div");
			userItem.classList.add("user-item");

			const isUserFriend = await isFriend(user.username);
			const avatarUrl = user.avatar && user.avatar.url ? user.avatar.url : '/static/images/login.jpg';
			if (!isUserFriend && authData.data.user.username !== user.username) { 
				userItem.innerHTML = `
					<div class="item-size">${rank}</div>
					<div class="item-size"><img src="${avatarUrl}" alt="${user.username}'s avatar" class="user-avatar" />${user.username}</div>
					<div class="item-size">${user.wins}</div>
					<div class="item-size">${user.losses}</div>
					<div class="addfriend-icon"><i class="bi bi-person-fill-add"></i></div>
				`;
				leaderboardContainer.appendChild(userItem);

				const addFriend = userItem.querySelector(".addfriend-icon");
				addFriend.addEventListener("click", async function (event) {
					event.preventDefault();
					try {
						const response = await fetch("/api/add_friend/", {
							method: "POST",
							headers: { "Content-Type": "application/json" },
							body: JSON.stringify({ friend_username: user.username }),
						});

						if (response.ok) {
							//console.log("Friend request sent.");
							loadLeaderboardPage();
						} else {
							console.error("Failed to send friend request.");
						}
					} catch (error) {
						console.error("Error Adding friend:", error);
					}
				});
			} else {
				userItem.innerHTML = `
					<div class="item-size">${rank}</div>
					<div class="item-size"><img src="${avatarUrl}" alt="${user.username}'s avatar" class="user-avatar" />${user.username}</div>
					<div class="item-size">${user.wins}</div>
					<div class="item-size">${user.losses}</div>
				`;
				leaderboardContainer.appendChild(userItem);
			}

			rank++;

		}

		if (leaderboardData.length > 0) {
			const loggedInUsername = authData.data.user.username;
			document.getElementById("user-leaderboard-username").textContent = loggedInUsername;
		}
	} catch (error) {
		console.error("Error loading leaderboard:", error);
	}
}

async function getFriend() {
	try {
		const response = await fetch("/api/friends/", {
			method: "GET",
			headers: { "Content-Type": "application/json" },
		});

		if (!response.ok) {
			console.error("Friend list not received");
			return null;
		}

		const friendsData = await response.json();
		//console.log("Received friend data:", friendsData);
		return friendsData;
	} catch (error) {
		console.error("Error getting friends:", error);
		return null;
	}
}

async function isFriend(username) {
	const friendsData = await getFriend();

	if (!friendsData || !Array.isArray(friendsData.friends)) {
		console.error("Error: Friends list is not an array", friendsData);
		return false;
	}
	return friendsData.friends.some(friend => friend.username === username);
}



