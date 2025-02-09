export class ProfileUploader {
	constructor(profilePicSelector, uploadUrl, profileNameSelector, usernameUrl, profileNameSaveSelector, profileNameEditSelector, profileNameResetSelector) {
		this.profilePic = document.querySelector(profilePicSelector);
		this.uploadUrl = uploadUrl;
		this.profileNameInput = document.querySelector(profileNameSelector);
		this.profileNameInputSave = document.querySelector(profileNameSaveSelector);
		this.usernameUrl = usernameUrl;
		this.profileNameEdit = document.querySelector(profileNameEditSelector);
		this.profileNameReset = document.querySelector(profileNameResetSelector);
		this.disable2faBtn = document.getElementById("disable-2fa-btn");
		this.enable2faBtn = document.getElementById("enable-2fa-btn");
		this.count = document.getElementById("count");

		this.originalName = this.profileNameInput.value;

		this.initialize();
	}

	timeElapsed(dateString) {
		const inputDate = new Date(dateString.replace(' ', 'T'));
		const now = new Date();
		const diffMs = now - inputDate;

		if (diffMs < 0) {
			return "idk";
		}

		const diffSeconds = Math.floor(diffMs / 1000);
		const diffMinutes = Math.floor(diffSeconds / 60);
		const diffHours = Math.floor(diffMinutes / 60);
		const diffDays = Math.floor(diffHours / 24);

		if (diffSeconds < 60) {
			return "now";
		}
		if (diffMinutes < 60) {
			return `${diffMinutes}min`;
		}
		if (diffHours < 24) {
			return `${diffHours}h`;
		}
		return `${diffDays}d`;
	}
	
	editMode()
	{
		this.originalName = this.profileNameInput.value;
		this.profileNameEdit.style.display = "none";
		this.profileNameReset.style.display = "block";
		this.profileNameInputSave.style.display = "block";
		this.profileNameInput.removeAttribute("disabled");
		this.profileNameInput.focus();
	}

	displayMode()
	{
		this.profileNameReset.style.display = "none";
		this.profileNameEdit.style.display = "block";
		this.profileNameInputSave.style.display = "none";
		this.profileNameInput.setAttribute("disabled", "true");
	}

	handle2faChange(isEnabled) {
		fetch("/api/change_2fa/", {
			method: "POST",
			headers: {
				"Content-Type": "application/json",
			},
			body: JSON.stringify({ is_2fa_enabled: isEnabled }),
		})
		.then(response => {
			if (!response.ok) {
				throw new Error("Failed to change 2FA");
			}
			return response.json();
		})
		.then(data => {
			//console.log("2FA changed successfully:", data);
			this.message("2FA changed successfully!", "success");
			this.enable2faBtn.style.display = isEnabled ? "none" : "block";
			this.disable2faBtn.style.display = isEnabled ? "block" : "none";
		})
		.catch(error => {
			console.error("Error:", error);
			this.message("Failed to change 2FA.", "error");
		});
	}

	initialize() {
		const list = [
			this.profilePic,
			this.profileNameInput,
			this.profileNameInputSave,
			this.profileNameEdit,
			this.profileNameReset,
			this.enable2faBtn,
			this.disable2faBtn,
			this.count
		];
		list.forEach((element) => {
			if (!element) {
				console.error("Element not found");
			}
		});
		
		this.profilePic.addEventListener("click", () => this.handleProfilePicClick());
		this.profileNameInputSave.addEventListener("click", () => this.handleProfileNameClick());
		this.profileNameEdit.addEventListener("click", () => this.editMode());
		this.profileNameReset.addEventListener("click", () => {
			this.displayMode();
			this.profileNameInput.value = this.originalName;
		});

		fetch("api/wl/", { credentials: "include" })
			.then(response => response.json())
			.then(data => {
				const winCountElement = document.querySelector("#count .win-count .number");
				const lossesCountElement = document.querySelector("#count .loose-count .number");

				winCountElement.textContent = data.wins;
				lossesCountElement.textContent = data.losses;
			})
			.catch(error => console.error("Error fetching win/losses count:", error));

		fetch("/api/change_2fa/")
			.then(response => response.json())
			.then(data => {
				const is2faEnabled = data.is_2fa_enabled;
				//console.log("2FA status:", is2faEnabled);
	
				this.enable2faBtn.style.display = is2faEnabled ? "none" : "block";
				this.disable2faBtn.style.display = is2faEnabled ? "block" : "none";
			})
			.catch(error => {
				console.error("Error fetching 2FA status:", error);
				this.message("Failed to fetch 2FA status.", "error");
			});

		this.disable2faBtn.addEventListener("click", () => this.handle2faChange(false));
		this.enable2faBtn.addEventListener("click", () => this.handle2faChange(true));

		this.loadFriendsList();
		this.loadMatchHistory();
	}

	async loadFriendsList() {
        try {
            const response = await fetch("/api/friends/");
            if (!response.ok) {
                throw new Error("Failed to fetch friends");
            }
            const data = await response.json();
            const friendList = data.friends;
            this.displayFriends(friendList);
        } catch (error) {
            console.error("Error:", error);
        }
    }

	displayFriends(friends) {
		const friendListContainer = document.getElementById("friend-list");
		friendListContainer.innerHTML = ''; // Clear existing list
		if (friends.length === 0) {
			if (document.documentElement.lang === "fr") {
				friendListContainer.innerHTML = '<li data-translate="no_friends">Aucun ami trouvé.</li>';
			}
			else if (document.documentElement.lang === "kr") {
				friendListContainer.innerHTML = '<li data-translate="no_friends">친구 없음.</li>';
			}
			else {
				friendListContainer.innerHTML = '<li data-translate="no_friends">No friends found.</li>';
			}
			return;
		}

		friends.forEach(friend => {
			const li = document.createElement("li");
			// Avatar image
			const img = document.createElement("img");
			img.src = friend.avatar ? friend.avatar : "/static/images/login.jpg";
			img.alt = friend.username;
			img.style.width = '40px';
			img.style.height = '40px';
			img.style.borderRadius = '50%';

			// Username
			const span = document.createElement("span");
			span.textContent = friend.username;

			// Online/Offline Status
			const statusIndicator = document.createElement("span");
			statusIndicator.style.marginLeft = "10px";
			statusIndicator.textContent = friend.is_online ? "🟢" : "⚫";

			li.appendChild(img);
			li.appendChild(span);
			li.appendChild(statusIndicator);
			friendListContainer.appendChild(li);
		});
	}
	
	loadMatchHistory() {
		fetch("api/matchhistory", { credentials: "include" })
			.then(response => response.json())
			.then(data => {
				//console.log("Enzo Match History Data:", data.match_history); // Console log the data
				const matchHistoryContainer = document.getElementById("match-history-list");

				data.match_history.forEach(match => {
					//console.log("Match:", match);
					const li = document.createElement("li");
					const opponent = document.createElement("span");
					const score = document.createElement("span");
					const date = document.createElement("span");

					opponent.textContent = match.opponent;
					date.textContent = this.timeElapsed(match.date);
					score.textContent = match.user_score + " - " + match.opponent_score;

					li.appendChild(opponent);
					li.appendChild(score);
					li.appendChild(date);
					
					matchHistoryContainer.appendChild(li);
				});
				
			})
			.catch(error => console.error("Error fetching match history:", error));
	}

	handleProfilePicClick() {
		const input = this.createFileInput();
		const form = this.createForm(input);

		document.body.appendChild(form);
		input.click();

		input.addEventListener("change", () => this.handleFileChange(input));
	}

	createFileInput() {
		const input = document.createElement("input");
		input.type = "file";
		input.name = "avatar";
		input.accept = "image/*";
		return input;
	}

	createForm(input) {
		const form = document.createElement("form");
		form.enctype = "multipart/form-data";
		form.appendChild(input);
		return form;
	}

	message(message, type) {
		document.getElementById("data-message").innerHTML = message;
		if(type === "error")
		{
			document.getElementById("data-message").classList.add("error");
			document.getElementById("data-message").classList.remove("success");
		}
		else if(type === "success")
		{
			document.getElementById("data-message").classList.add("success");
			document.getElementById("data-message").classList.remove("error");
		}
	}

	async handleFileChange(input) {
		const file = input.files[0];
		if (file) {
			const formData = new FormData();
			formData.append("avatar", file);

            let uploadResponse;

			try {
				uploadResponse = await fetch(this.uploadUrl, {
					method: "PUT",
					body: formData,
				});

				if (!uploadResponse.ok) {
					throw new Error("Failed to upload avatar");
				}

				const uploadData = await uploadResponse.json();
				//console.log("Upload successful:", uploadData);
				this.message("Avatar uploaded successfully!", "success");
				const profilePic = document.querySelector("#profil-content .profile-pic");
				const userProfileImg = document.getElementById("user-profile-img");
				const baseUrl = "https://localhost:3000"; 
				const mediaUrl = uploadData.avatar_url
				const fullUrl = `${baseUrl}${mediaUrl}`;
				profilePic.src = fullUrl
				userProfileImg.src = fullUrl
				//console.log("profil pic src", fullUrl)

			} catch (error) {
				console.error("Error:", error);
               
                if (uploadResponse.status === 413) {
					this.message("Image is too large. Please upload a smaller image.", "error");
                }
                if (uploadResponse.status >= 500 && uploadResponse.status < 600) {
					this.message("Server error. Please try again later.", "error");
                }
                else {
                    console.error("Error:", error);
					this.message("Failed to upload avatar or fetch updated profile.", "error");
                }
            
            }
		}
	}


	async handleProfileNameClick() {
		const username = sanitizeInput(this.profileNameInput.value.trim());

		if (username) {
			try {
				const response = await fetch(this.usernameUrl, {
					method: "POST",
					headers: {
						"Content-Type": "application/json",
					},
					body: JSON.stringify({ username }),
				});

				if (!response.ok) {
					throw new Error("Failed to update username");
				}

				const data = await response.json();
				//console.log("Username update successful:", data);
				this.message("Username updated successfully!", "success");
				this.originalName = username;
				// ici
				const userPofileUsername = document.getElementById("username_info");
				userPofileUsername.innerHTML = username;
			} catch (error) {
				console.error("Error:", error);
				this.message("Failed to update username.", "error");
			}
			this.displayMode();
		}
	}
}

function sanitizeInput(input) {
    const tempElement = document.createElement('div');
    tempElement.innerText = input.trim();
    return tempElement.innerHTML;
}