FROM debian:bookworm

# Necesario en Dockerfile el -y (yes. Desea continuar?) por que no es interativo.
RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y mariadb-server

# Copiamos el archivo de configuración y el script de inicio
COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
COPY tools/setup.sh /usr/local/bin/setup.sh

# Damos permisos de ejecución al script
RUN chmod +x /usr/local/bin/setup.sh

# Exponemos el puerto estándar de MySQL
# Esto es a titulo informativo. Se puede borrar de aqui, pero no en el docker-compose.yml
EXPOSE 3306

# Ejecutamos el script al arrancar el contenedor en PID1
# PID 1 es como tiene que estar. Es decir proceso principal. Si no seria otro PID
# Docker puede ser cualquier PID, y de hecho, como proceso en el ordenador raiz es distinto de 1...
# ...pero la magia de docker es que NO SON MAQUINAS VIRTUALES sino que es los procesos que arrancan
# ...mariadb, wordpress, nginx, etc.. y lo que hace docker es AISLAR dicho contendor del resto del ordenador...
# ...haciendo que pueda asignarle el PID 1 a dicho programa, siendo el más importante y permitiendo a docker...
# ...leer las señales para cerrarlos (down, stop, etc..) y no se queden huerfanos, o se cierren nada más crearse.
# Entrypoint (podria ser CMD en vez, pero podria ser alterado desde fuera, y entrypoint es más seguro...
# al tener corchetes hace que sh (shell) se lance como PID1. PERO luego dentro del script que ejecutamos...
# ...(setup.sh) al tener la ultima linea el comando 'exec' mata el shell como pid1...
# ...y el servicio pasa a ser el PID1.
ENTRYPOINT ["sh", "/usr/local/bin/setup.sh"]
