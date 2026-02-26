*Este proyecto ha sido realizado como parte del currículo de 42 por jrollon-.*

# 🖨️ ft_printf — El arte de formatear

Este proyecto consiste en recrear la famosa función `printf` de la librería estándar de C. Aunque el objetivo principal es manejar las conversiones básicas, este desarrollo ha ido más allá, analizando y replicando comportamientos de "flags" no pedidas para lograr una compatibilidad más cercana al `printf` real.

---

## 📖 Descripción

El reto de **ft_printf** es aprender a manejar funciones con argumentos variables (variádicas) mediante el uso de la macro `va_list`. El programa parsea una cadena de formato y sustituye cada especificador por el valor correspondiente procesado.

### Inventario de Especificadores Implementados

Además de las conversiones obligatorias, se ha realizado un estudio de casos (`Printf_Casos.txt`) para gestionar cómo reacciona la función ante caracteres inesperados tras el `%`.

#### Conversiones Estándar (Mandatory):
- `%c`: Imprime un solo carácter.
- `%s`: Imprime una cadena de caracteres.
- `%p`: Imprime un puntero en formato hexadecimal.
- `%d` / `%i`: Imprime un número entero en base 10.
- `%u`: Imprime un número decimal sin signo.
- `%x` / `%X`: Imprime un número hexadecimal (minúsculas/mayúsculas).
- `%%`: Imprime el símbolo del porcentaje.

#### Flags y Comportamientos "Extra" (Investigación):
Se han categorizado múltiples caracteres para imitar el comportamiento de la glibc:
- **Espacio tras `%`**: Implementado para mimetizar el espaciado antes de números positivos.
- **Detección de "Two-Flags"**: Gestión de caracteres que se imprimen literalmente junto al `%` (ej: `%D`, `%H`, `%U`, etc.).
- **Gestión de errores**: Comportamiento ante `%` solitarios al final de una cadena o especificadores inválidos como `%C`.

---

## 🛠️ Makefiles y Pruebas

El proyecto incluye dos sistemas de compilación para diferentes necesidades:

### 1. Makefile (Producción)
Genera la librería estática necesaria para ser entregada y utilizada en otros proyectos.
```bash
make        # Crea libftprintf.a
```

### 2. Makefile_Test (Desarrollo)
Diseñado específicamente para depuración. Compila la librería junto con un archivo `main.c` de prueba y genera un ejecutable directo.
```bash
make -f Makefile_Test    # Genera el ejecutable 'ft_printf_exe'
./ft_printf_exe          # Ejecuta las pruebas del main
```

---

## 🚀 Detalles de Implementación

- **Modularidad**: Las conversiones estándar se gestionan en `ft_printf_flag_type.c`, mientras que la lógica para las flags adicionales y casos borde se encuentra en `ft_printf_other_flags.c`.
- **Conversión de Bases**: Se utiliza un motor genérico en `ft_putnbr_base.c` para manejar las impresiones hexadecimales y de punteros.
- **Robustez**: Se ha prestado especial atención a la gestión de punteros `NULL` (imprimiendo `(nil)`) y strings nulos.

```text
miniyo$ ./ft_printf_exe
Real: [  42] | Mío: [  42]
Real: [0x7ffee1...] | Mío: [0x7ffee1...]
Real: [Error %!] | Mío: [Error %!]
```

---

## 📋 Documentación de Casos
Para ver el análisis completo de cómo se comporta cada letra del abecedario tras un `%`, consulta el archivo:
📄 [Printf_Casos.txt](02_Printf/Printf_Casos.txt)