<?php
echo "<h1>GET Data</h1>";
echo "<pre>";
print_r($_GET);
echo "</pre>";

echo "<h1>POST Data</h1>";
echo "<pre>";
print_r($_POST);
echo "</pre>";

echo "<h1>FILES Data</h1>";
echo "<pre>";
print_r($_FILES);
echo "</pre>";


// Vérifie si des fichiers ont été envoyés
if (!empty($_FILES['file'])) {
    // Création du dossier 'upload' s'il n'existe pas
    $uploadDir = 'upload';
    if (!is_dir($uploadDir)) {
        mkdir($uploadDir, 0777, true);
    }

    // Récupère les informations du fichier envoyé
    $fileName = basename($_FILES['file']['name']);
    $uploadFile = $uploadDir . DIRECTORY_SEPARATOR . $fileName;

    // Déplace le fichier vers le dossier 'upload'
    if (move_uploaded_file($_FILES['file']['tmp_name'], $uploadFile)) {
        echo "<p>Le fichier <strong>$fileName</strong> a été téléchargé avec succès dans le dossier <strong>$uploadDir</strong>.</p>";
    } else {
        echo "<p>Erreur : le fichier n'a pas pu être téléchargé.</p>";
    }
} else {
    echo "<p>Aucun fichier envoyé.</p>";
}

phpinfo();

?>