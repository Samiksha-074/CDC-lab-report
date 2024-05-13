<!DOCTYPE html>
<html>
<head>
    <title>Multiple Image Upload</title>
</head>
<body>
    <h2>Upload Images</h2>
    <form action="upload.php" method="post" enctype="multipart/form-data">
        <input type="file" name="images[]" multiple accept="image/jpeg, image/png, image/gif" />
        <input type="submit" value="Upload" />
    </form>

<?php
$uploadDir = 'uploads/';

// Check if the images array exists in the POST request
if(isset($_FILES['images'])) {
    $uploadedFiles = $_FILES['images'];

    // Loop through all the uploaded files
    for($i = 0; $i < count($uploadedFiles['name']); $i++) {
        $fileName = $uploadedFiles['name'][$i];
        $fileTmpName = $uploadedFiles['tmp_name'][$i];
        $fileType = strtolower(pathinfo($fileName, PATHINFO_EXTENSION));

        // Define allowed file types
        $allowedTypes = array('jpg', 'jpeg', 'png', 'gif');

        // Check if the uploaded file type is allowed
        if (in_array($fileType, $allowedTypes)) {
            $destination = $uploadDir . $fileName;

            // Attempt to move the uploaded file to the destination folder
            if (move_uploaded_file($fileTmpName, $destination)) {
                echo "File '$fileName' has been uploaded successfully.<br>";
            } else {
                echo "Error uploading '$fileName'.<br>";
            }
        } else {
            echo "Sorry, only JPG, JPEG, PNG, and GIF files are allowed.<br>";
        }
    }
}
?>
</body>
</html>
