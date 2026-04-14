# CPP Module 09 - 42 Cursus

## 📝 Descripción
Este módulo es el desafío final de la serie de C++. Se centra en la resolución de problemas algorítmicos complejos utilizando la **STL (Standard Template Library)**. El objetivo principal es aprender a elegir el contenedor adecuado (`vector`, `list`, `deque`, `map`, `stack`) basándose en la eficiencia de tiempo y memoria (Complejidad Big O).

## 🛠️ Contenido del Módulo

### [Ex 00: Bitcoin Exchange](./ex00/)
Programa que calcula el valor de una cantidad de Bitcoin en una fecha específica.
- **Base de Datos**: Lee un archivo `.csv` con el histórico de precios.
- **Entrada**: Procesa un segundo archivo con fechas y cantidades.
- **Lógica**: Para cada fecha, busca el precio más cercano (hacia atrás) en la base de datos.
- **Contenedor Elegido**: `std::map<std::string, float>` por su capacidad de búsqueda rápida y ordenación automática de claves (fechas).
- **Funciones clave**: Uso de `std::map::lower_bound` para encontrar la fecha anterior más próxima.

### [Ex 01: Reverse Polish Notation (RPN)](./ex01/)
Calculadora de expresiones matemáticas en **Notación Polaca Inversa**.
- **Entrada**: Una cadena con números y operadores (ej: `"3 4 + 2 *"`).
- **Lógica**: Los números se apilan y, al encontrar un operador, se desapilan los dos últimos para realizar la operación.
- **Contenedor Elegido**: `std::stack<int>` (o un contenedor que actúe como pila).
- **Restricción**: Solo procesa números menores de 10.

### [Ex 02: PmergeMe](./ex02/)
Implementación del algoritmo de ordenación **Merge-Insertion Sort** (también conocido como algoritmo de **Ford-Johnson**).
- **Desafío**: Ordenar una secuencia de números positivos usando dos contenedores diferentes.
- **Contenedores Elegidos**: Típicamente `std::vector` y `std::deque` (o `std::list`).
- **Objetivo**: Comparar el tiempo de ejecución entre ambos contenedores.
- **Algoritmo**: 
    1. Agrupar elementos en pares.
    2. Ordenar los pares por el elemento mayor.
    3. Insertar recursivamente los elementos menores usando **búsqueda binaria**.

## 🚀 Conceptos Clave
- **Elección de Contenedores**: ¿Por qué `std::map` para Bitcoin y no `std::vector`?
- **Eficiencia Algorítmica**: Análisis de tiempos de ejecución (microsegundos).
- **Manejo de Errores**: Validación estricta de formatos de fecha, valores negativos y desbordamientos.

## 💻 Instalación y Compilación
Como siempre, compila cada ejercicio con:

```bash
make
```

## 🧪 Notas de Implementación
- En el **Ex 00**, el formato de fecha debe ser estrictamente `YYYY-MM-DD`.
- En el **Ex 02**, la implementación del algoritmo Ford-Johnson es el mayor reto técnico del módulo debido a su naturaleza recursiva y la inserción optimizada.

---
*42 Madrid - Fin del camino de C++*