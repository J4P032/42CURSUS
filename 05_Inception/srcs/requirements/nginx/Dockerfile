# Usamos Debian Bookworm(la penúltima estable en abril de 2026)
FROM debian:bookworm

# Actualizamos el sistema e instalamos Nginx y OpenSSL
RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y nginx openssl

# Creamos la carpeta donde guardaremos los certificados SSL
RUN mkdir -p /etc/nginx/ssl

# Generamos el certificado auto-firmado (TLS es obligatorio) que cumpla con standard X509
# -nodes para que la llave privada no esté protegida por contraseña y asi Nginx arranque automaticamente en el contendor
# -out lo guarda en dicha direccion. Tiene que ser creada antes con mkdir en este dockerfile. Es pública
# -keyout es privada.
# -subj es el sujeto y en comillas va toda la informacion. CN (dominio) debe coincidir con la config de nginx.
RUN openssl req -x509 -nodes -out /etc/nginx/ssl/inception.crt -keyout /etc/nginx/ssl/inception.key -subj "/C=ES/ST=Madrid/L=Madrid/O=42/OU=42/CN=jrollon-.42.fr/UID=jrollon-"

# Copiamos el archivo de configuración
COPY conf/nginx.conf /etc/nginx/conf.d/default.conf
COPY tools/setup.sh /usr/local/bin/setup.sh

# Añadimos esto para asegurar carpetas y permisos
RUN mkdir -p /var/www/wordpress
RUN chown -R www-data:www-data /var/www/wordpress
RUN chmod +x /usr/local/bin/setup.sh

# Exponemos el puerto 443 para HTTPS, tal como pide el subject
# Esto es a titulo informativo. Se puede borrar de aqui, pero no en el docker-compose.yml
EXPOSE 443

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

