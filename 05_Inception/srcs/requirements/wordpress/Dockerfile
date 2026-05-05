FROM debian:bookworm

RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y wget php8.2 php-fpm php-mysql net-tools

# Descargamos el CLI de WordPress (herramienta para configurar WP por comandos)
RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
RUN chmod +x wp-cli.phar
RUN mv wp-cli.phar /usr/local/bin/wp

# Creamos la carpeta para PHP y el directorio raíz de la web. CLI descargará los archivos, pero he de decirle donde
# /run/php es donde se creará el archivo socket (comunicación rápida), y /var/www/wordpress donde se pondrán los archivos
RUN mkdir -p /run/php
RUN mkdir -p /var/www/wordpress

# Copiamos la configuración de PHP-FPM y nuestro script de setup. Ha de ser en dichos directorios.
COPY conf/www.conf /etc/php/8.2/fpm/pool.d/www.conf
COPY tools/setup.sh /usr/local/bin/setup.sh
RUN chmod +x /usr/local/bin/setup.sh

# hace un cd permanente a dicho directorio. Todos los comandos de dockerfile se ejecutarán ahi.
# el directorio ha de coincidir con lo que se ponga en la config de Nginx.  root /var/www/wordpress;
WORKDIR /var/www/wordpress

# Esto es a titulo informativo. Se puede borrar de aqui, pero no en el docker-compose.yml
EXPOSE 9000

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
