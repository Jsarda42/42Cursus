export function displayError(message, containerSelector = "#main-content") {
    const container = document.querySelector(containerSelector);

    if (!container) {
        console.error(`${containerSelector} not found!`);
        return;
    }
    //console.log(container)
    const errorContainer = document.createElement('div');
    errorContainer.classList.add('error-message');
    errorContainer.textContent = message;

    container.insertBefore(errorContainer, container.firstChild);

    setTimeout(() => {
        errorContainer.remove();
    }, 5000);
}

export function displayValid(message, containerSelector = "#main-content") {
    const container = document.querySelector(containerSelector);

    if (!container) {
        console.error(`${containerSelector} not found!`);
        return;
    }

    const validContainer = document.createElement('div');
    validContainer.classList.add('valid-message');
    validContainer.textContent = message;

    container.insertBefore(validContainer, container.firstChild);
    setTimeout(() => {
        validContainer.remove();
    }, 5000);
}

