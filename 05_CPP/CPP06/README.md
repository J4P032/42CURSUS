# CPP Module 06 - 42 Cursus

## 📝 Descripción
Este módulo se centra en la introducción de los diferentes tipos de **Casts** en C++. El objetivo es aprender a realizar conversiones de tipos de datos de manera explícita y segura, dejando atrás los casts al estilo de C (`(int)f`) en favor de los operadores de conversión específicos de C++.

## 🛠️ Contenido del Módulo

El proyecto explora los cuatro operadores de casting principales:

### [Ex 00: Conversion of scalar types](./ex00/)
Implementación de una clase `ScalarConverter`.
- Conversión de una cadena de caracteres (literal) a tipos escalares: `char`, `int`, `float` y `double`.
- Manejo de valores especiales como `nan`, `inf`, `+inf` y `-inf`.
- Uso de `static_cast` para conversiones seguras entre tipos numéricos.
- Detección de desbordamientos (overflow) y casos imposibles de convertir.

### [Ex 01: Serialization](./ex01/)
Introducción a la **Serialización**.
- Implementación de una clase `Serializer`.
- Uso de `reinterpret_cast`: Este cast se utiliza para convertir un puntero a un tipo de dato entero (`uintptr_t`) y viceversa.
- El objetivo es demostrar que podemos transformar una estructura de datos en un formato que pueda ser almacenado o transmitido, y luego reconstruirla exactamente igual.

### [Ex 02: Identify real type](./ex02/)
Identificación de tipos en tiempo de ejecución (**RTTI**).
- Uso de `dynamic_cast`: El cast más seguro para navegar en jerarquías de clases con polimorfismo.
- Implementación de una clase base `Base` (con destructor virtual) y tres clases derivadas `A`, `B` y `C`.
- Funciones para identificar el tipo real de un objeto:
    - **Por puntero**: Devuelve `NULL` si el cast falla.
    - **Por referencia**: Lanza una excepción (`std::bad_cast`) si el cast falla (manejo con `try-catch`).

## 🚀 Conceptos Clave de Casting
1. **static_cast**: Conversiones entre tipos relacionados (ej. de `int` a `float`). Se comprueba en tiempo de compilación.
2. **dynamic_cast**: Se usa con punteros/referencias a clases con funciones virtuales. Comprueba la validez en tiempo de ejecución.
3. **reinterpret_cast**: Conversiones de bajo nivel. Trata los bits como si fueran de otro tipo. Muy potente pero peligroso.
4. **const_cast**: Se utiliza exclusivamente para añadir o quitar el calificador `const` a una variable.

## 💻 Instalación y Compilación
Cada ejercicio incluye su propio `Makefile`. Para compilar, entra en la carpeta del ejercicio y ejecuta:

```bash
make
```

## 🧪 Notas de Implementación
- En el **Ex 00**, desde la versión C++11 en adelante, algunas funciones han cambiado, pero para 42 seguimos el estándar **C++98**.
- En el **Ex 02**, recuerda que la identificación por referencia requiere capturar la excepción, ya que no existe la "referencia nula".

---
*Progreso de 42 Madrid - Common Core.*