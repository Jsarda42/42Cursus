#!/bin/bash
set -euo pipefail

until mysqladmin ping -h "mariadb" -u ${SQL_USER} -P 3306 --password=${SQL_PASSWORD} --connect-timeout=10; do
	echo "Waiting for database connection..."
done
if
	wp core is-installed --allow-root --path="/var/www/html";
then
	echo "wordpress already install"
else
	wp core install --allow-root --path="/var/www/html" --url="https://jsarda.42.fr/" --title="Your Site Title"     --admin_user="${SQL_USER}" --admin_password="${SQL_PASSWORD}"     --admin_email="admin@example.com" --skip-email
fi

if
	wp user exists --allow-root --path="/var/www/html" jsarda;
then
	echo "user jsarda exist"
else
	wp user create --allow-root --path="/var/www/html" jsarda jsarda@icloud.com --role=subscriber --user_pass=jsarda
fi
php-fpm7.4 -F
