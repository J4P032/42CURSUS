*Este proyecto ha sido realizado como parte del currículo de 42 por jrollon-.*

# 🔢 push_swap — Because swap_push isn't as catchy

El objetivo de este proyecto es simple: ordenar una pila de números enteros utilizando un conjunto limitado de instrucciones y el menor número de movimientos posible. Para lograrlo, disponemos de dos pilas (**Stack A** y **Stack B**) y un conjunto de operaciones de manipulación.

---

## 📖 Descripción

**push_swap** es un ejercicio de algoritmos y optimización. El reto no es solo ordenar los números, sino hacerlo de la manera más eficiente para cumplir con los límites de movimientos impuestos por la escuela 42 (especialmente crítico para listas de 100 y 500 números).

### El Reto
- **Stack A**: Contiene inicialmente una cantidad aleatoria de números negativos y/o positivos sin duplicados.
- **Stack B**: Está vacía al principio.
- **Objetivo**: Ordenar los números en el **Stack A** de menor a mayor.

### Algoritmos Implementados
- **Sort para grupos pequeños**: Lógica optimizada para 2, 3 y 5 números (fuerza bruta y casos específicos).
- **K-Sort / Chunk Sort**: El motor principal para grandes volúmenes de datos, que divide los números en "chunks" o bloques basados en su índice para facilitar un paso eficiente al Stack B y su posterior reordenación al volver al Stack A.
- **Pre-indexación**: Uso de un `counting_sort` previo para asignar índices a los valores, facilitando la lógica del algoritmo principal.

---

## ✨ Operaciones Permitidas

| Comando | Acción |
|---------|--------|
| `sa` / `sb` | **Swap**: Intercambia los dos primeros elementos de la pila A o B. |
| `ss` | `sa` y `sb` al mismo tiempo. |
| `pa` / `pb` | **Push**: Pasa el primer elemento de una pila a la otra. |
| `ra` / `rb` | **Rotate**: Desplaza hacia arriba todos los elementos (el primero pasa a ser el último). |
| `rr` | `ra` y `rb` al mismo tiempo. |
| `rra` / `rrb` | **Reverse Rotate**: Desplaza hacia abajo todos los elementos (el último pasa a ser el primero). |
| `rrr` | `rra` y `rrb` al mismo tiempo. |

---

## 🚀 Instalación y Uso

### Compilación

Clona el repositorio y compila el proyecto mediante el Makefile:

```bash
git clone https://github.com/J4P032/42CURSUS.git
cd 42CURSUS/03_PushSwap
make
```

### Ejecución

El programa recibe como argumento una lista de enteros y devuelve la secuencia de instrucciones para ordenarlos:

```bash
./push_swap 2 1 3 6 5 8
```

También puedes pasarle una cadena de números entre comillas:

```bash
./push_swap "0 42 2 -2147483648"
```

### Verificación

Para comprobar si la lista de movimientos es correcta (puedes usar el checker de la escuela o uno propio):

```bash
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker_linux $ARG
```

---

## 🛠️ Detalles Técnicos

- **Estructura de Datos**: Implementado mediante una **lista doblemente enlazada** (`t_stack`) para permitir rotaciones eficientes en ambas direcciones.
- **Gestión de Errores**: El programa gestiona entradas no numéricas, números mayores a `INT_MAX` o menores a `INT_MIN`, y duplicados, mostrando `Error` por salida de errores.
- **Optimización**: El algoritmo busca reducir los movimientos calculando distancias al tope y al fondo de la pila para decidir entre `rotate` o `reverse rotate`.

```text
miniyo$ ./push_swap 3 2 1
sa
rra
```