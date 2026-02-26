*Este proyecto ha sido realizado como parte del currículo de 42 por jrollon-.*

# 📚 libft — Mi primera librería de C

**libft** es el proyecto fundacional de 42. Consiste en recrear funciones estándar de la librería de C (libc) y añadir funciones de utilidad adicionales que me servirán para todos los proyectos futuros del currículo.

---

## 📖 Inventario de Funciones

La librería se divide en tres partes principales:

### 1. Funciones de la Libc
Reimplementaciones de funciones clásicas como `ft_strlen`, `ft_memcpy`, `ft_strchr`, `ft_atoi`, entre otras, para entender su funcionamiento interno y no depender de librerías externas.

### 2. Funciones Adicionales
Funciones que no están en la libc pero que son extremadamente útiles:
- `ft_substr`: Extrae una parte de una cadena.
- `ft_strjoin`: Concatena dos cadenas en una nueva.
- `ft_split`: Divide una cadena en un array de strings usando un delimitador.
- `ft_itoa`: Convierte un entero a una cadena de caracteres.

### 3. Funciones de Listas (Bonus)
Manipulación de listas enlazadas simples mediante la estructura `t_list`:
- `ft_lstnew`, `ft_lstadd_back`, `ft_lstsize`, `ft_lstmap`, etc.

---

## 🛠️ Cómo incluir Libft en tus proyectos

Para usar esta librería en otros proyectos, lo más eficiente es compilarla como una librería estática `.a` e incluirla en tu `Makefile`.

### Ejemplo de Makefile de un proyecto externo:

```makefile
NAME    = mi_programa
LIBFT   = ./libft/libft.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

# Regla para compilar tu programa vinculando la libft
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -o $(NAME)

# Regla para compilar la libft llamando a su propio Makefile
$(LIBFT):
	make -C ./libft

clean:
	rm -f $(OBJS)
	make clean -C ./libft
```

### Ejemplo de uso en código C:

```c
#include "libft.h"

int main(void)
{
    char *str = ft_strdup("Hola mundo");
    ft_putstr_fd(str, 1);
    free(str);
    return (0);
}
```

---

## 🚀 Compilación de la Librería

Dentro de la carpeta `01_libft`, puedes usar los siguientes comandos:

- `make`: Compila las funciones base.
- `make bonus`: Compila las funciones base más las de listas enlazadas.
- `make -f Makefile_Tests`: Compila un ejecutable de prueba con mi propio `main.c` de tests.