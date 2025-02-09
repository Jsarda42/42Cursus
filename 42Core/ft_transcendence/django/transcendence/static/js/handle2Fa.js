const TwofaValidationButton = document.getElementById("2FA_Button");
TwofaValidationButton.addEventListener("click", function (event) {
	event.preventDefault();

	const codeInput = document.getElementById("code");
	const code = codeInput ? codeInput.value.trim() : null;
	if (!code) {
		console.error("Please enter the verification code.");
		return;
	}
	TwofaValidationButton.disabled = true;
	const userData = window.currentUserData || {};
	//console.log(userData)
	if (!userData.user_id) {
		console.error("User information is missing. Please try again.");
		TwofaValidationButton.disabled = false;
		return;
	}
	fetch("/api/2fa/", {
		method: "POST",
		headers: {
			"Content-Type": "application/json",
		},
		body: JSON.stringify({ otp : code, user_id: userData.user_id }),
	})
		.then((response) => {
			TwofaValidationButton.disabled = false;
			if (!response.ok) {
				throw new Error(`Verification failed: ${response.statusText}`);
			}
			return response.json();
		})
		.then((result) => {
			if (result.success) {
				console.error("Verification successful!");
				window.location.href = "/home"; 
			} else {
				console.error("Invalid code. Please try again.");
			}
		})
		.catch((error) => {
			console.error("Error during code verification:", error);
			console.error("An error occurred. Please try again later.");
			TwofaValidationButton.disabled = false;
		});
});