all: build

build:
	mkdir -p postgres/data
	docker-compose -f docker-compose.yml up --build -d
# docker run --rm -v $(PWD):/data alpine sh -c "chmod -R a+wr /data/postgres/data"

re:
	docker-compose -f docker-compose.yml down --volumes --remove-orphans
	$(MAKE) build

clean:
	docker-compose -f docker-compose.yml down --rmi all --volumes --remove-orphans

populate_data:
	docker exec -it django /bin/bash -c "python manage.py populate_users"

rm_db:
	docker run --rm -v $(PWD):/data alpine sh -c "rm -rf /data/postgres/data && mkdir -p /data/postgres/data && chmod -R a+wr /data/postgres/data"
	echo "\033[0;32mDatabase deleted, you should now run 'make re'\033[0m"

.PHONY: build clean re all rm_db
