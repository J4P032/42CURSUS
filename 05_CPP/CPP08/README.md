# CPP Module 08 - 42 Cursus

## 📝 Descripción
Este módulo se centra en la **Standard Template Library (STL)** de C++. El objetivo es aprender a utilizar de manera eficiente los contenedores (como `vector`, `list`, `map`), los iteradores y los algoritmos (`std::for_each`, `std::find`, etc.) para escribir código potente y reutilizable.

## 🛠️ Contenido del Módulo

### [Ex 00: Easy find](./ex00/)
Implementación de una plantilla de función `easyfind`.
- La función recibe un tipo `T` (que debe ser un contenedor de enteros) y un `int`.
- Busca la primera ocurrencia del entero en el contenedor.
- Si no lo encuentra, lanza una excepción o devuelve un error (según la lógica de la STL, suele usarse `std::find`).
- **Aprendizaje**: Uso de iteradores básicos y algoritmos de búsqueda.

### [Ex 01: Span](./ex01/)
Desarrollo de una clase `Span` que puede almacenar un máximo de `N` enteros.
- **Funciones clave**:
    - `addNumber(int)`: Añade un solo número.
    - `shortestSpan()`: Calcula la distancia más corta entre dos números del contenedor.
    - `longestSpan()`: Calcula la distancia más larga entre el número más pequeño y el más grande.
- **Optimización**: Implementación de una función para añadir un rango de números de una sola vez (usando iteradores) para evitar múltiples llamadas a `addNumber`.
- **Excepciones**: Control de errores cuando el contenedor está lleno o cuando no hay suficientes números para calcular un "span".

### [Ex 02: Mutated abomination](./ex02/)
Creación de un contenedor `MutantStack`.
- El `std::stack` de la STL es genial, pero tiene un problema: **no es iterable**.
- Este ejercicio consiste en heredar de `std::stack` y "mutarlo" para añadirle iteradores.
- **Técnica**: Exponer los iteradores del contenedor subyacente (por defecto `std::deque`) para que el `stack` pueda ser recorrido con un `for` o algoritmos.

## 🚀 Conceptos de STL
- **Contenedores**: Secuenciales (`vector`, `list`, `deque`) y Asociativos (`map`, `set`).
- **Iteradores**: El "pegamento" entre contenedores y algoritmos.
- **Algoritmos**: Funciones genéricas que operan sobre rangos de elementos.

## 💻 Instalación y Compilación
Compila cada ejercicio con su propio `Makefile`:

```bash
make
```

## 🧪 Notas de Implementación
- He priorizado el uso de algoritmos de la cabecera `<algorithm>` para evitar bucles manuales siempre que ha sido posible.
- En el **Ex 02**, la clave es entender que `std::stack` tiene un objeto interno llamado `c` (container) que ya tiene los iteradores que necesitamos.

---
*42 Madrid - Common Core - C++ STL*