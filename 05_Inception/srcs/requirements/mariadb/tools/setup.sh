#!/bin/sh

service mariadb start
sleep 2

# Usamos las variables del .env
# mariadb -e "CREATE DATABASE IF NOT EXISTS \`${SQL_DATABASE}\`;"
# mariadb -e "CREATE USER IF NOT EXISTS \`${SQL_USER}\`@'localhost' IDENTIFIED BY '${SQL_PASSWORD}';"
# mariadb -e "GRANT ALL PRIVILEGES ON \`${SQL_DATABASE}\`.* TO \`${SQL_USER}\`@'%' IDENTIFIED BY '${SQL_PASSWORD}';"
# mariadb -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${SQL_ROOT_PASSWORD}';"
# mariadb -e "FLUSH PRIVILEGES;"

# 1. Creamos la base de datos
# mariadb es un comando que sustituye al antiguo mysql
# -e es para que ejecute la sentencia SQL que está entre comillas sin entrar en modo interactivo.
# SQL va como: ACCION - OBJETO - CONDICION - con final en ';'. las \`(`), garantizan preservar los caractereres especiales o espacios.
mariadb -e "CREATE DATABASE IF NOT EXISTS \`${SQL_DATABASE}\`;"

# 2. Creamos el usuario para CUALQUIER conexión ('%') y le damos permisos SOLO a la base de datos $SQL_DATABASE. .* son todas las tablas dentro
# Esto (%) es por que el usuario de wordpress se conecta desde FUERA (desde el contenedor de wordpress)
mariadb -e "CREATE USER IF NOT EXISTS \`${SQL_USER}\`@'%' IDENTIFIED BY '${SQL_PASSWORD}';"
mariadb -e "GRANT ALL PRIVILEGES ON \`${SQL_DATABASE}\`.* TO \`${SQL_USER}\`@'%';"

# 3. Cambiamos la contraseña de root. En realidad le damos una, por que mariadb crea el root SIN contraseña. Asi más seguridad.
# aquí es localhost, por que el root SIEMPRE es local host. No sería % (desde fuera)
mariadb -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${SQL_ROOT_PASSWORD}';"

# 4. Refrescamos y apagamos para reiniciar con 'exec'
mariadb -p${SQL_ROOT_PASSWORD} -e "FLUSH PRIVILEGES;"
mysqladmin -u root -p${SQL_ROOT_PASSWORD} shutdown

# exec consigue que herede el PID1 y mate el shell secundario haciendolo PID1 también
# docker solo escucha señales en PID1
# mysqld_safe es el proceso para para lanzar mariadb. Safe...
# ...para relanzarlo en caso de problema. Ya está definido para que no sea un daemon por defecto.
exec mysqld_safe
