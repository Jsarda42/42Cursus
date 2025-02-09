FROM debian:bullseye

RUN apt-get update && apt-get install -y nginx openssl

COPY nginx/nginx.conf /etc/nginx/sites-available/default

RUN mkdir /etc/nginx/certs
RUN openssl req -newkey rsa:2048 -nodes -keyout /etc/nginx/certs/server.key -x509 -days 365 -out /etc/nginx/certs/server.crt -subj "/C=FR/ST=Ile-de-France/L=Paris/O=42/OU=42 Paris/CN=localhost/emailAddress=edegraev@student.42.fr"
RUN ln -sf /dev/stdout /var/log/nginx/access.log && ln -sf /dev/stderr /var/log/nginx/error.log

EXPOSE 3000

CMD ["nginx", "-g", "daemon off;"]