SHELL := /bin/bash

ENV		= .env

-include $(ENV)
export

# descomentar cuando tenga que existir el .env
#$(ENV):
#	@exit 1

all: build

# Generar database/.env desde .env raíz
generate-env:
	@bash ./scripts/generate-env.sh

build: #$(ENV)
	docker compose -f ./docker-compose.yml build

up: generate-env
	docker compose -f ./docker-compose.yml up --build -d

# Detiene los contenedores conservando los volúmenes (datos de postgres).
down:
	docker compose -f ./docker-compose.yml down

# Elimina los datos persistidos de postgres. Destructivo.
clean-data:
	docker compose -f ./docker-compose.yml down -v

ps:
	docker compose -f ./docker-compose.yml ps

volumes:
	docker volume ls

logs:
	docker compose logs -f

# Solo limpia imágenes/cache de este proyecto, no toca el resto del sistema.
clean: down
	docker compose -f ./docker-compose.yml down --rmi local --remove-orphans
	docker builder prune -f

fclean: clean-data
	docker compose down --rmi all --volumes --remove-orphans

add-volumes:
	mkdir -p ./data/postgres
	@echo "Created dir volume for database data."

exec-db:
	docker exec -it transcendence_postgres psql -U $(shell grep '^POSTGRES_USER=' $(ENV) | cut -d'=' -f2)

re: fclean all

.PHONY: all up down clean-data logs clean fclean build ps volumes generate-env add-volumes exec-db re
