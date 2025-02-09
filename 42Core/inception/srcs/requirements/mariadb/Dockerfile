FROM debian:bullseye

RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get install -y mariadb-server
RUN apt-get install -y mariadb-client
RUN apt-get install -y procps
RUN apt-get install -y sudo

COPY ./conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
RUN chmod 710 /etc/mysql/mariadb.conf.d/50-server.cnf

RUN mkdir -p /run/mysqld
RUN mkdir -p /var/log/mysql
RUN chown mysql:mysql /var/log/mysql
RUN mkdir -p /var/lib/mysql
RUN chown mysql:mysql /run/mysqld/
RUN chmod -R 755 /run/mysqld/
RUN chown mysql:mysql /var/lib/mysql/
RUN chmod -R 755 /var/lib/mysql/

EXPOSE 3306

COPY ./tools/dbscript.sh ./
RUN chmod +x ./dbscript.sh

CMD ["bash", "./dbscript.sh"]
