import { translations } from './translationData.js';

// Function to get the translation object for a specific language
const getTranslation = (lang) => translations.languages[lang] || translations.languages[translations.default];

// Function to apply translations to the DOM
const applyTranslation = (lang) => {
	const translation = getTranslation(lang);

	// Update the HTML document's lang attribute
	document.documentElement.lang = lang;

	// Update text content of elements with the data-translate attribute
	document.querySelectorAll('[data-translate]').forEach((element) => {
		const key = element.getAttribute('data-translate');
		if (Object.hasOwn(translation, key)) {
			element.textContent = translation[key];
		} else {
			console.warn(`Missing translation for key: "${key}"`);
		}
	});

	document.querySelectorAll('[data-translate-placeholder]').forEach((element) => {
		const key = element.getAttribute('data-translate-placeholder');
		if (Object.hasOwn(translation, key)) {
			element.placeholder = translation[key];
		} else {
			console.warn(`Missing translation for placeholder key: "${key}"`);
		}
	});

	// Sync the language selector value, if present
	const languageSelector = document.getElementById('languageSelector');
	if (languageSelector) languageSelector.value = lang;

	// Save the selected language to LocalStorage
	try {
		localStorage.setItem('selectedLanguage', lang);
	} catch (error) {
		console.warn('Unable to save language to LocalStorage.');
	}
};

// Function to get the saved language from LocalStorage or use the default
const getSavedLanguage = () => {
	try {
		return localStorage.getItem('selectedLanguage') || translations.default;
	} catch (error) {
		console.warn('LocalStorage is not accessible. Using default language.');
		return translations.default;
	}
};

// Initialize translation logic
const initTranslation = () => {
	// Apply the saved or default language
	applyTranslation(getSavedLanguage());

	// Set up language selector event listener
	document.body.addEventListener('change', (event) => {
		if (event.target && event.target.id === 'languageSelector') {
			const selectedLanguage = event.target.value;
			//console.log('Language changed to:', selectedLanguage);
			applyTranslation(selectedLanguage);
		}
	});
};

// Initialize when DOM is ready
document.addEventListener('DOMContentLoaded', initTranslation);

export { applyTranslation, getSavedLanguage };


