
# IMPORTANTE!!! IMPORTANT:

    Muchos de estos proyectos compilan sin problema a veces, pero si tienes instalado una version más moderna de GCC está será más restrictiva, por que no deja llamar a funciones sin parametros (). Asi que para forzar una versión antigua, hay que añadir en los Makefile el flag: -std=gnu11 (dos unos) ya con ello lo hará bien.

    Some of these projects compile fine on older setups, but newer GCC versions are more restrictive and disallow function declarations with empty parameters (). To fix this and force an older standard, simply add the -std=gnu11 flag to your Makefiles