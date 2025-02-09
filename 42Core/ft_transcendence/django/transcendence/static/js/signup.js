import { applyTranslation, getSavedLanguage } from "./translation.js";
import { translations } from "./translationData.js";
import { displayError, displayValid } from "./display_message.js";

function sanitizeInput(input) {
    const tempElement = document.createElement('div');
    tempElement.innerText = input.trim();
    return tempElement.innerHTML;
}

export function initializeSignupForm() {
	const signupForm = document.querySelector('form');

	if (signupForm) {
		const savedLanguage = getSavedLanguage();
		applyTranslation(savedLanguage);

		signupForm.addEventListener('submit', function (event) {
			event.preventDefault();

			const username = sanitizeInput(document.getElementById('username').value);
			const email = sanitizeInput(document.getElementById('email').value);
			const password = document.getElementById('password').value;
			const confirmPassword = document.getElementById('confirm-password').value;

			if (password !== confirmPassword) {
				displayError(translations.languages[getSavedLanguage()].passwordMismatch);
				return;
			}

			if (!isValidPassword(password)) {
				displayError(translations.languages[getSavedLanguage()].invalidPassword);
				return;
			}

			const formData = { username, email, password };

			fetch('/api/signup/', {
				method: 'POST',
				headers: {
					'Content-Type': 'application/json',
				},
				body: JSON.stringify(formData)
			})
				.then(response => response.json())
				.then(data => {
					if (data.success) {
						displayValid(translations.languages[getSavedLanguage()].signupSuccess);
						window.location.href = '/signin';
					} else {
						if (data.email) {
							displayError("This email already exists.");
						} 
						if (data.username) {
							displayError("This user already exists.");
						} 
						displayError(translations.languages[getSavedLanguage()].signupFailure);
					}
				})
				.catch(error => {
						displayError(error);
				});
		});
	}
}

function isValidPassword(password) {
	const passwordPattern = /^(?=.*[A-Z])(?=.*[0-9])(?=.*[\W_]).{5,}$/;
	return passwordPattern.test(password);
}

