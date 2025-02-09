FROM debian:bullseye
RUN apt update -y && apt upgrade -y
RUN  apt install nginx curl -y
RUN mkdir /etc/nginx/certs
RUN openssl req -newkey rsa:2048 -nodes -keyout /etc/nginx/certs/server.key -x509 -days 365 -out /etc/nginx/certs/server.crt -subj "/C=FR/ST=Ile-de-France/L=Paris/O=42/OU=42 Paris/CN=*.jsarda.42.fr/emailAddress=jsarda@student.42.fr"
COPY default /etc/nginx/sites-available/.
CMD ["nginx", "-g", "daemon off;"]
