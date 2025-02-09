<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $name = $_POST['name'];
    $email = $_POST['email'];
    $message = $_POST['message'];

    // Process the form data (e.g., store it, send an email, etc.)
    // For testing, we'll simply echo the data

    echo "Thank you for your message, $name. We have received the following details:<br>";
    echo "Email: $email<br>";
    echo "Message: $message<br>";

    // Optionally, redirect or give feedback
    // header("Location: thank_you.html");
} else {
    echo "Invalid request method.";
}
?>
