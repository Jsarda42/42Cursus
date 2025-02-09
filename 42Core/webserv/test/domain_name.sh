#!/bin/bash

echo -e "\033[1;32mjulien.fr\033[0m"
curl -v --resolve julien.fr:8080:127.0.0.1 http://julien.fr:8080
echo -e "\n"

echo -e "\033[1;32mlocalhost\033[0m"
curl -v --resolve localhost:8081:127.0.0.1 http://localhost:8081
echo -e "\n"

echo -e "\033[1;32menzo.fr\033[0m"
curl -v --resolve enzo.fr:8082:127.0.0.1 http://enzo.fr:8082