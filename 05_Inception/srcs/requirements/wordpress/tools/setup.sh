#!/bin/sh

# Esperamos a que MariaDB este lista. 'wp' es el CLI wp-cli.phar que hemos acortado con el comando move en el dockerfile
sleep 10

if [ ! -f /var/www/wordpress/wp-config.php ]; then
    # el que no exista el wp-config.php es que no se ha instalado. El core Download es como bajar el .zip de worpress
    # el --allow-root es necesario en todos por que por defecto al root de linux no se le permite ejecutar 'wp' en wordpress
    wp core download --allow-root

    # Generamos el archivo de configuración wp-config.php que conecta wordpress con MariaDB.
    # --dbhost=mariadb:3306 dice que busque en el contenedor que en el docker-compose se llama mariadb. 
    wp config create \
        --dbname=$SQL_DATABASE \
        --dbuser=$SQL_USER \
        --dbpass=$SQL_PASSWORD \
        --dbhost=mariadb:3306 --allow-root

    # rellena las tablas de la base de datos de MariaDB. Aquí se crea el administrador y abajo el usuario.
    wp core install \
        --url=$DOMAIN_NAME \
        --title=$SITE_TITLE \
        --admin_user=$ADMIN_USER \
        --admin_password=$WP_ADMIN_PASSWORD \
        --admin_email=$WP_ADMIN_EMAIL \
        --allow-root

    # role=author hace que no sea administrador.
    wp user create \
        $USER_LOGIN $USER_EMAIL \
        --role=author \
        --user_pass=$USER_PASSWORD \
        --allow-root
fi

# Cambiamos el dueño a www-data de forma recursiva
# www-data:www-data (usuario:grupo) definidos en el www.conf
chown -R www-data:www-data /var/www/wordpress
# Aseguramos permisos de escritura para el grupo
chmod -R 775 /var/www/wordpress/wp-content


# con -F hacemos daemon off lo lanza en primer plano
# exec consigue que herede el PID1 y mate el shell secundario haciendolo PID1 tambien
# docker solo escucha señales en PID1
exec /usr/sbin/php-fpm8.2 -F
