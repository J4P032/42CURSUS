#!/bin/sh


echo "Iniciando Nginx..."

# daemon off lo lanza en primer plano
# exec consigue que herede el PID1 y mate el shell secundario haciendolo PID1 tambien
# docker solo escucha señales en PID1
# -g para pasarle la configuracion GLOBAL sin editar el nginx.conf
exec nginx -g "daemon off;"

