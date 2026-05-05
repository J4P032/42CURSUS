# docker compose gestiona diferentes dockers a la vez. -f es para leer el archivo de config
NAME		= inception
COMPOSE		= docker compose -f srcs/docker-compose.yml
USER_DATA	= /home/jrollon-/data
CHECKER		= .containers_up

all: setup $(CHECKER)

# up crea y arranca dockers, -d los ejecuta en segundo plano detached para no secuestrar...
# ...el terminal con dichos dockers que son procesos.
# --build para que no busque la imagen en internet sino la construya
$(CHECKER): srcs/docker-compose.yml
	@echo "\033[0;32mLevantando todo...\033[0m"
	$(COMPOSE) up -d --build
	@touch $(CHECKER)

setup:
	@echo "\033[0;32mCreando directorios de datos en $(USER_DATA)...\033[0m"
	@mkdir -p $(USER_DATA)/mariadb
	@mkdir -p $(USER_DATA)/wordpress

# Ver el estado de los servicios. Tambien con "docker ps".
# para ver las imagenes hay que poner "docker image ls"
ps:
	$(COMPOSE) ps

# Abrir una terminal en un servicio (Ejemplo: make shell SERVICE=mariadb)
# Tambien valdria con 'docker exec -it mariadb sh' (-it modo interactivo)
# Una vez dentro para meterme en databases: mysql -u usuario(jrollon-) -p(password)
# Listar Databases: show databases;
# para seleccionar una database: use nombreDatabase(wordpress);
# seleccionar las tablas: show tables;
# ver las tablas: select * from tabla(wp_users);
# control + d para salir del contenedor.
# los archivos de php estaran en /var/www/wordpress/ tanto end dockers de wordpress como nginx
# tambien se puede entrar como docker exec -it wordpress bash (o sh si bash no esta instalado). -it=modo interactivo
shell:
	@if [ -z "$(SERVICE)" ]; then echo "Uso: make shell SERVICE=nombre_del_servicio"; exit 1; fi
	$(COMPOSE) exec $(SERVICE) sh

# para parar un contenedor podemos hacer "docker stop mariadb". No consumira ram...
# ... y reanudarlo con "docker start mariadb".
# para cerrarlo "docker rm -f wordpress"...
# ...y levantarlo docker compose -f srsc/docker-compose.yml up -d wordpress"
down:
	@echo "\033[0;31mDeteniendo servicios...\033[0m"
	$(COMPOSE) down
	@rm	-f $(CHECKER)

up:
	@echo "\033[0;31mReabriendo Servicios...\033[0m"
	$(COMPOSE) up -d

restart: down up

# Limpia contenedores y volumenes, pero mantiene las imagenes
# $(comando) en bash ejecuta un comando, por eso ha de llevar $$ pq en bash $$ = $. con un $ solo, espera una variable
# 2> es salida por stderr (1> stdoutput) dev/null es que no muestre nada por terminal.
# || true. Es un "o" (esto o aquello) Cada linea de make da un true o false si se ejecutan. Si no tiene volumenes daria false, pero esto hace que continue con el make por que daria true
clean: down
	@echo "\033[0;31mBorrando volúmenes y carpetas de datos...\033[0m"
	@docker volume rm $$(docker volume ls -q) 2>/dev/null || true
	@sudo rm -rf $(USER_DATA)/mariadb
	@sudo rm -rf $(USER_DATA)/wordpress
	@rm	-f $(CHECKER)

# Limpieza profunda pero ESPECIFICA (Imágenes, redes, volúmenes, todo)
# @docker system prune -a --force se cargaria todos las imagenes de los dockers inactivos PERO DE TODO EL SISTEMA. NO queremos eso
# al hacerlo con docker compose -f.... down --rmi(borra la imagen) all... borra solo las creadas. Para probarlo:
# docker run -d --name myNombre alpine sleep 1000
# docker stop myNombre (la imagen quedara). despues de hacer make fclean, borrara dicha imagen
# remove-orphans por si se cambia algun nombre de servicio para borrar el antiguo.
# para ver las imagenes hay que poner "docker image ls"
fclean: clean
	@echo "\033[0;31mBorrando TODAS las imágenes de Docker...\033[0m"
	$(COMPOSE) down --rmi all --volumes --remove-orphans

# para evaluar sin cache. Tarda mas al descargar debian de nuevo
# podria poner en el fclean "docker builder prune -f" pero eso borraria la cache de todo lo construido ademas de Inception
re: fclean setup
	@echo "\033[0;33mReconstruyendo todo desde cero...\033[0m"
	$(COMPOSE) build --no-cache
	$(COMPOSE) up -d
	@touch $(CHECKER)

.PHONY: all setup ps shell down clean fclean re restart up
