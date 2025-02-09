#!/bin/bash
 
FILE_PATH="body.txt"

UPLOAD_URL="http://localhost:8081/upload.php"

curl -F "file=@${FILE_PATH}" ${UPLOAD_URL}