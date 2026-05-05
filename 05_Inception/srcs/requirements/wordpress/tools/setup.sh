#!/bin/sh

# Esperamos a que MariaDB este lista
sleep 10

if [ ! -f /var/www/wordpress/wp-config.php ]; then
    wp core download --allow-root

    wp config create \
        --dbname=$SQL_DATABASE \
        --dbuser=$SQL_USER \
        --dbpass=$SQL_PASSWORD \
        --dbhost=mariadb:3306 --allow-root

    wp core install \
        --url=$DOMAIN_NAME \
        --title=$SITE_TITLE \
        --admin_user=$ADMIN_USER \
        --admin_password=$WP_ADMIN_PASSWORD \
        --admin_email=$WP_ADMIN_EMAIL \
        --allow-root

    wp user create \
        $USER_LOGIN $USER_EMAIL \
        --role=author \
        --user_pass=$USER_PASSWORD \
        --allow-root
fi

# Cambiamos el dueño a www-data de forma recursiva
chown -R www-data:www-data /var/www/wordpress
# Aseguramos permisos de escritura para el grupo
chmod -R 775 /var/www/wordpress/wp-content


# con -F hacemos daemon off lo lanza en primer plano
# exec consigue que herede el PID1 y mate el shell secundario haciendolo PID1 tambien
# docker solo escucha señales en PID1
exec /usr/sbin/php-fpm8.2 -F
