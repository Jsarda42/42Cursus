// Get the button and hidden message
const surpriseButton = document.getElementById('surpriseButton');
const hiddenMessage = document.getElementById('hiddenMessage');

// Get the video button and video element
const videoButton = document.getElementById('videoButton');
const funVideo = document.getElementById('funVideo');

// Add an event listener to the surprise button for a click event
surpriseButton.addEventListener('click', () => {
    // Show the hidden message
    hiddenMessage.style.display = 'block';

    // Change the button text after click
    surpriseButton.textContent = "You're Amazing! 🎉";

    // Add an animation to the hidden message
    hiddenMessage.style.animation = "fadeIn 2s ease-in-out";

    // Change the background color of the page to add excitement
    document.body.style.transition = "background-color 1s ease";
    document.body.style.backgroundColor = "#ffeb3b"; // Bright yellow for fun!

    // Play a sound when the button is clicked
    const surpriseSound = new Audio('https://www.soundjay.com/button/beep-07.wav');
    surpriseSound.play();
});

// Add an event listener to the video button to show the video
videoButton.addEventListener('click', () => {
    // Show the video when the button is clicked
    funVideo.style.display = 'block';
    videoButton.textContent = "Enjoy the Video! 🎬";
    videoButton.disabled = true; // Disable the button after it's clicked
    funVideo.play(); // Play the video automatically
});


