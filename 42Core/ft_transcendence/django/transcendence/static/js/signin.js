import { applyTranslation, getSavedLanguage } from "./translation.js";
import { displayError, displayValid } from "./display_message.js";

function sanitizeInput(input) {
    const tempElement = document.createElement('div');
    tempElement.innerText = input.trim();
    return tempElement.innerHTML;
}

export function initializeSigninForm() {
	const signinForm = document.querySelector('form');
	const csrfToken = document.querySelector('meta[name="csrf-token"]').getAttribute('content');

	if (signinForm) {
		const savedLanguage = getSavedLanguage();
		applyTranslation(savedLanguage);

		signinForm.addEventListener('submit', function (event) {
			event.preventDefault();

			const email = sanitizeInput(document.getElementById('email').value);
			const password = sanitizeInput(document.getElementById('password').value);
			const formData = { email, password };

			fetch('/api/login/', {
				method: 'POST',
				headers: {
					'Content-Type': 'application/json',
					'X-CSRFToken': csrfToken,
				},
				body: JSON.stringify(formData)
			})
				.then(response => response.json())
				.then(data => {
					if (data.success) {
						window.currentUserData = data;
						//console.log("data.need_2fa:", data.need_2fa);
						if (data.need_2fa)
						{
							show2FAModal();
						}
						else
						{
							window.location.href = "/home";
						}
					} else {
						if (data.error) {
							displayError(data.error);
						} else {
							displayError("Login failed! Please check your credentials.");
						}
					}
				})
				.catch(error => {
					displayError('An error occurred. Please try again.');
				});
		});
	}
}

function show2FAModal() {
	const modalContainer = document.getElementById('modalContainer');
	const savedLanguage = getSavedLanguage();
	const modalContent = `
    <div id="twoFAModal" class="modal">
      <div class="modal-content">
        <h2 data-translate="enter2FA"></h2>
        <p class="modal-p" data-translate="twoFaP"></p>
        <input type="text" id="twoFACode" data-translate-placeholder="placeholder2FACode" />
        <div>
          <button data-translate="cancel" class="btn btn-warning" id="closeModal">Cancel</button>
          <button data-translate="submit" class="btn btn-success" id="submitTwoFACode"></button>
        </div>
      </div>
    </div>
  `;
	modalContainer.innerHTML = modalContent;
	applyTranslation(savedLanguage);

	modalContainer.style.display = 'flex';
	const modal = document.getElementById('twoFAModal');
	modal.style.display = 'flex';

	document.getElementById('closeModal').addEventListener('click', function () {
		modal.style.display = 'none';
		modalContainer.style.display = 'none';
	});

	document.getElementById('submitTwoFACode').addEventListener('click', function () {
		const twoFACode = document.getElementById('twoFACode').value.trim();

		if (!twoFACode) {
			displayError("Please enter a valid 2FA code.", "#twoFAModal");
			return;
		}

		const userData = window.currentUserData;
		if (!userData || !userData.user_id) {
			displayError("User information is missing. Please try again.", "#twoFAModal");
			return;
		}
		handle2FACodeSubmission(userData.user_id, twoFACode);
	});
}

function handle2FACodeSubmission(userId, twoFACode) {
	const csrfToken = document.querySelector('meta[name="csrf-token"]').getAttribute('content');

	const formData = {
		user_id: userId,
		otp: twoFACode
	};

	fetch('/api/2fa/', {
		method: 'POST',
		headers: {
			'Content-Type': 'application/json',
			'X-CSRFToken': csrfToken,
		},
		body: JSON.stringify(formData)
	})
		.then(response => response.json())
		.then(data => {
			if (data.success) {
				displayValid("2FA Verification successful!");
				window.location.href = "/home";
			} else {
				displayError("Invalid 2FA code. Please try again.", "#twoFAModal");
			}
		})
		.catch(error => {
			displayError('An error occurred. Please try again.', "#twoFAModal");
		});
}


