# CPP Module 05 - 42 Cursus

## 📝 Descripción
Este módulo de la jerarquía de C++ está diseñado para introducir y profundizar en el concepto de **Excepciones**. A diferencia del manejo de errores tradicional (códigos de retorno), las excepciones permiten separar la lógica del programa del manejo de errores, haciendo el código más robusto y legible.

## 🛠️ Contenido del Módulo

El proyecto se divide en varios ejercicios que incrementan la complejidad:

### [Ex 00: Mommy, when I grow up, I want to be a bureaucrat!](./ex00/)
Introducción a la clase `Bureaucant`.
- Implementación de excepciones personalizadas heredando de `std::exception`.
- Control de rangos de grado (1 a 150).
- Uso de bloques `try { ... } catch (std::exception &e) { ... }`.

### [Ex 01: Form up, maggots!](./ex01/)
Introducción a la clase `Form`.
- Interacción entre clases: Un `Bureaucrat` intenta firmar un `Form`.
- Validación de requerimientos de grado para firma.

### [Ex 02: No, you need form 28B, not 28C...](./ex02/)
Clases abstractas y formularios específicos:
- **ShrubberyCreationForm**: Crea un archivo con árboles ASCII.
- **RobotomyRequestForm**: Simula una robotomía con 50% de éxito.
- **PresidentialPardonForm**: Otorga un perdón presidencial.
- Requisito: El formulario debe estar firmado para ser ejecutado.

### [Ex 03: At least this way we could finish the job...](./ex03/)
La clase `Intern` (Becario).
- Implementación del patrón de diseño **Factory**.
- Creación de formularios mediante un nombre pasado por string, evitando largas estructuras `if-else` mediante punteros a funciones miembro.

## 🚀 Conceptos Clave
- **std::exception**: La clase base para todas las excepciones estándar.
- **Throwing**: Lanzar una excepción cuando ocurre un error inesperado.
- **Catching**: Capturar la excepción para manejar el error sin que el programa aborte bruscamente.
- **Polimorfismo en Excepciones**: Capturar por referencia para evitar el "object slicing".

## 💻 Instalación y Compilación
Cada ejercicio incluye su propio `Makefile`. Para compilar, entra en la carpeta del ejercicio y ejecuta:

```bash
make
```

Para ejecutar el programa:
```bash
./bureaucrat  # (O el nombre del binario correspondiente)
```

## 🧪 Pruebas
Los archivos `main.cpp` incluyen pruebas de casos límite:
- Intentar crear un burócrata con grado 0 o 151.
- Intentar firmar un formulario sin tener el grado suficiente.
- Intentar ejecutar un formulario que no ha sido firmado previamente.

---
*Este proyecto forma parte del common core de 42 Madrid.*