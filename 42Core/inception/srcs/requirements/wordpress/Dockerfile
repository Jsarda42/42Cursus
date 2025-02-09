FROM debian:bullseye

RUN mkdir -p /run/php/ /var/www/html
RUN apt update -y && apt upgrade -y && apt install -y php7.4-fpm php-mysqli curl mariadb-client -y
RUN curl -O https://wordpress.org/latest.tar.gz
RUN tar -zxvf latest.tar.gz
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
RUN chmod +x wp-cli.phar
RUN mv wp-cli.phar /usr/local/bin/wp
RUN mv wordpress/* /var/www/html/
COPY www.conf /etc/php/7.4/fpm/pool.d/www.conf
COPY wp-config.php /var/www/html/wp-config.php
COPY ./tools/wpscript.sh /usr/local/bin/wpscript.sh
RUN chmod +x /usr/local/bin/wpscript.sh
EXPOSE 9000

CMD ["/bin/bash", "/usr/local/bin/wpscript.sh"]

