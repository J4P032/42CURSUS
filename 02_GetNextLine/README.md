*Este proyecto ha sido realizado como parte del currículo de 42 por jrollon-.*

# 📜 GetNextLine — El desafío de la Norminette

Este proyecto consiste en programar una función que devuelva una línea leída desde un descriptor de archivo (fd). Aunque parece sencillo, ha sido **el proyecto más problemático y complejo** debido a las severas restricciones impuestas y al momento del aprendizaje en el que se realizó.

---

## 📖 El "Infierno" del Desarrollo

**GetNextLine** fue una verdadera prueba de resistencia. Las limitaciones de la **Norminette** obligaron a estrujar el código hasta límites insospechados:

- **Espacio mínimo**: Solo se permiten **2 archivos .c**.
- **Regla de 25**: Máximo **25 líneas por función**.
- **Límite de funciones**: Máximo **5 funciones por archivo**.
- **Variables restringidas**: Solo **4 variables por función** y un máximo de **5 variables por ámbito**.

### El desafío de la lógica
En el momento de realizarlo, aún no dominaba el uso de estructuras para pasar múltiples variables de forma limpia. Como solución, opté por una **lista enlazada** (`t_list`) para gestionar el búfer y el contenido leído. Esto, sumado a las restricciones anteriores, convirtió el desarrollo en un rompecabezas de lógica y gestión de memoria.

---

## ✨ Trucos y Optimizaciones

Para cumplir con las 25 líneas sin sacrificar la funcionalidad, tuve que recurrir a diversos "trucos" de programación:
- **Líneas multi-acción**: Uso de comas y asignaciones dentro de condiciones para realizar varias tareas en una sola línea de código.
- **Funciones multi-opción**: Creación de funciones como `findn` o `give_me_rest` que realizan acciones distintas según un parámetro `option`, ahorrando así el número total de funciones permitidas.
- **Hacks de retorno**: Retornos complejos que liberan memoria y asignan valores simultáneamente (ej: `return (free(aux), NULL)`).

---

## 🛠️ Detalles Técnicos

- **Variable Estática**: Uso de una variable estática para recordar qué se leyó pero no se devolvió en la llamada anterior (el "rest").
- **Buffer Dinámico**: El programa debe funcionar correctamente con cualquier `BUFFER_SIZE`, desde 1 hasta 9999.
- **Gestión de Memoria**: Liberación exhaustiva de cada nodo de la lista y de los búfers internos para asegurar **0 leaks**.

---

## 🚀 Cómo usarlo

### Integración

Para usar esta función en tus proyectos, incluye el header y compila los archivos `.c`:

```c
#include "get_next_line.h"

int main()
{
    int fd = open("archivo.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Compilación

Define el tamaño del búfer al compilar para probar el rendimiento:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

---

## 📋 Conclusión

Este proyecto no solo trata de leer archivos; trata de **aprender a escribir código ultra-compacto** y a gestionar la memoria de forma impecable bajo presión. Fue frustrante, pero sent�� las bases para entender la importancia de la eficiencia y el orden en C.