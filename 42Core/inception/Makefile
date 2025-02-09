all: create_folders
	@docker compose -f ./srcs/docker-compose.yml up -d --build

create_folders:
	@test -d /home/jsarda/data/wordpress || mkdir -p /home/jsarda/data/wordpress
	@test -d /home/jsarda/data/mariadb || mkdir -p /home/jsarda/data/mariadb

remove_folders:
	rm -rf /home/jsarda/data/wordpress || sudo rm -rf /home/jsarda/data/wordpress
	rm -rf /home/jsarda/data/mariadb || sudo rm -rf /home/jsarda/data/mariadb

down:
	@docker compose -f ./srcs/docker-compose.yml down

up:
	@docker compose -f ./srcs/docker-compose.yml up

clean: remove_folders
	@docker compose -f ./srcs/docker-compose.yml down -v
	@docker system prune -af

.PHONY: all down clean up remove_folders create_folders