#!/bin/bash

service mariadb start

mariadb -e "CREATE DATABASE IF NOT EXISTS ${SQL_DATABASE};"
mariadb -e "CREATE USER IF NOT EXISTS '${SQL_USER}'@'%' IDENTIFIED BY '${SQL_PASSWORD}';"
mariadb -e "GRANT ALL PRIVILEGES ON ${SQL_DATABASE}.* TO '${SQL_USER}'@'%';"
mariadb -e "FLUSH PRIVILEGES;"


service mariadb stop

exec mysqld_safe
