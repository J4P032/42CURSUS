*Este bloque de proyectos ha sido realizado como parte del currículo de 42 por jrollon-.*

# 💻 04_CPP — El camino hacia la Programación Orientada a Objetos

Este repositorio contiene la serie de módulos de **C++** de la escuela 42. El objetivo principal es la transición del paradigma imperativo de C hacia la **Programación Orientada a Objetos (POO)**, siguiendo el estándar **C++98**.

---

## 📖 Resumen de Módulos

A lo largo de estos módulos, se exploran conceptos fundamentales como la gestión de memoria, el polimorfismo, la herencia y el uso de plantillas (templates).

### [Módulo 00: Conceptos Básicos](04_CPP/CPP00/)
Introducción a la sintaxis básica de C++, clases, funciones miembro, *std::iostream* y el uso de *namespaces*.
- **PhoneBook**: Una agenda de contactos simple para entender la estructura de una clase.
- **Account**: Implementación de un sistema de registro bancario para practicar con métodos estáticos y logs.

### [Módulo 01: Memoria y Referencias](04_CPP/CPP01/)
Uso de la memoria dinámica, punteros a funciones miembro y la diferencia entre punteros y referencias.
- **Zombies**: Gestión de memoria con `new` y `delete`.
- **Harl 2.0**: Uso de punteros a funciones miembro para automatizar quejas según el nivel de severidad.
- **Sed is for losers**: Manipulación de archivos y reemplazo de strings mediante flujos de entrada/salida.

### [Módulo 02: Polimorfismo Ad-hoc](04_CPP/CPP02/)
Introducción a la **Forma Canónica de Ortodoxa** y la sobrecarga de operadores.
- **Fixed-point numbers**: Creación de una clase para números de punto fijo, explorando la representación binaria y la sobrecarga de operadores aritméticos y de comparación.

### [Módulo 03: Herencia](04_CPP/CPP03/)
Exploración de la jerarquía de clases y la reutilización de código mediante la herencia.
- **ClapTrap, ScavTrap & FragTrap**: Implementación de robots con diferentes capacidades que heredan de una base común.
- **DiamondTrap**: Resolución del problema del "Diamante" en la herencia múltiple.

### [Módulo 04: Subtipado y Polimorfismo](04_CPP/CPP04/)
Dominio del polimorfismo mediante funciones virtuales, clases abstractas e interfaces.
- **Animales y Cerebros**: Gestión de copias profundas (*deep copy*) frente a copias superficiales (*shallow copy*).
- **Materia**: Implementación de un sistema de inventario y magia utilizando interfaces puras.

---

## ✨ Estándares y Reglas

- **Lenguaje**: C++ (Estándar C++98).
- **Compilador**: `c++` con flags `-Wall -Wextra -Werror -std=c++98`.
- **Forma Canónica de Ortodoxa**: Todas las clases incluyen:
    1. Constructor por defecto.
    2. Constructor de copia.
    3. Operador de asignación.
    4. Destructor (virtual si hay herencia).

---

## 🚀 Cómo compilar y probar

Cada ejercicio dentro de los módulos contiene su propio **Makefile**. Para probar un ejercicio específico (por ejemplo, el DiamondTrap):

```bash
cd 04_CPP/CPP03/ex03
make
./diamondtrap
```

---

## 🛠️ Temas Clave Aprendidos

- **Encapsulamiento**: Protección de datos mediante `private` y `protected`.
- **Memoria Dinámica**: Gestión segura para evitar *memory leaks*.
- **Polimorfismo Dinámico**: Uso de `virtual` para asegurar que se llame al método correcto en tiempo de ejecución.
- **Abstracción**: Uso de interfaces para definir contratos de comportamiento.