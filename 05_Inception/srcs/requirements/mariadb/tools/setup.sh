#!/bin/sh

service mariadb start
sleep 2

# Usamos las variables SQL_DATABASE, SQL_USER, SQL_PASSWORD y SQL_ROOT_PASSWORD del .env
# mariadb -e "CREATE DATABASE IF NOT EXISTS \`${SQL_DATABASE}\`;"
# mariadb -e "CREATE USER IF NOT EXISTS \`${SQL_USER}\`@'localhost' IDENTIFIED BY '${SQL_PASSWORD}';"
# mariadb -e "GRANT ALL PRIVILEGES ON \`${SQL_DATABASE}\`.* TO \`${SQL_USER}\`@'%' IDENTIFIED BY '${SQL_PASSWORD}';"
# mariadb -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${SQL_ROOT_PASSWORD}';"
# mariadb -e "FLUSH PRIVILEGES;"

# 1. Creamos la base de datos
mariadb -e "CREATE DATABASE IF NOT EXISTS \`${SQL_DATABASE}\`;"

# 2. Creamos el usuario para CUALQUIER conexión ('%') y le damos permisos
# Esto es lo que usará WordPress para conectar desde su contenedor
mariadb -e "CREATE USER IF NOT EXISTS \`${SQL_USER}\`@'%' IDENTIFIED BY '${SQL_PASSWORD}';"
mariadb -e "GRANT ALL PRIVILEGES ON \`${SQL_DATABASE}\`.* TO \`${SQL_USER}\`@'%';"

# 3. Cambiamos la contraseña de root (usamos 'echo' para evitar errores si ya está cambiada)
mariadb -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${SQL_ROOT_PASSWORD}';"

# 4. Refrescamos y apagamos para reiniciar con 'exec'
mariadb -p${SQL_ROOT_PASSWORD} -e "FLUSH PRIVILEGES;"
mysqladmin -u root -p${SQL_ROOT_PASSWORD} shutdown

# exec consigue que herede el PID1 y mate el shell secundario haciendolo PID1 tambien
# docker solo escucha señales en PID1
# mysqld_safe es el proceso mara para lanzar mariadb. Safe...
# ...para relanzarlo en caso de problema. Ya está definido para que no sea un daemon por defecto.
exec mysqld_safe
