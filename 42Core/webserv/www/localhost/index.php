<?php

echo "Hello, World!\n";

// Print all GET parameters
echo "GET Parameters:\n";
foreach ($_GET as $key => $value) {
    echo htmlspecialchars($key) . ": " . htmlspecialchars($value) . "\n";
}

// Print all POST parameters
echo "POST Parameters:\n";
foreach ($_POST as $key => $value) {
    echo htmlspecialchars($key) . ": " . htmlspecialchars($value) . "\n";
}
?>