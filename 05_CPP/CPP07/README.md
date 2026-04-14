# CPP Module 07 - 42 Cursus

## 📝 Descripción
Este módulo introduce el concepto de **Programación Genérica** en C++ mediante el uso de **Templates** (plantillas). El objetivo es escribir código que sea independiente del tipo de datos, permitiendo que una misma función o clase trabaje con `int`, `float`, `std::string` o incluso clases personalizadas.

## 🛠️ Contenido del Módulo

### [Ex 00: Start with a few functions](./ex00/)
Implementación de plantillas de funciones básicas:
- **swap**: Intercambia los valores de dos argumentos.
- **min**: Compara dos valores y devuelve el menor (si son iguales, devuelve el segundo).
- **max**: Compara dos valores y devuelve el mayor (si son iguales, devuelve el segundo).
- Requisito: Los argumentos deben tener el mismo tipo y soportar los operadores de comparación.

### [Ex 01: Iter](./ex01/)
Implementación de la función de plantilla `iter`:
- Recibe tres parámetros: la dirección de un array, su longitud y una función que se llamará para cada elemento del array.
- Demuestra cómo pasar funciones (o punteros a funciones) como argumentos de una plantilla.

### [Ex 02: Array](./ex02/)
Creación de una **Plantilla de Clase** llamada `Array`:
- Permite contener elementos de cualquier tipo `T`.
- **Gestión de Memoria**: Uso de `new[]` para reservar memoria dinámica.
- **深 (Deep Copy)**: Implementación correcta del constructor de copia y el operador de asignación para evitar problemas de doble liberación de memoria.
- **Operador `[]`**: Sobrecarga del operador de acceso para permitir el uso de `array[i]`, incluyendo el lanzamiento de una excepción `std::out_of_range` si el índice es inválido.
- Función miembro `size()` que devuelve el número de elementos.

## 🚀 Conceptos de Plantillas
- **Template Parameter**: El uso de `<typename T>` o `<class T>`.
- **Instanciación**: Cómo el compilador genera el código específico para cada tipo cuando se usa la plantilla.
- **Especialización**: (Concepto teórico importante en este módulo) la capacidad de definir un comportamiento diferente para un tipo específico.

## 💻 Instalación y Compilación
Cada ejercicio incluye su propio `Makefile`. Compila con:

```bash
make
```

## 🧪 Notas de Implementación
- Las plantillas **deben definirse en los archivos de cabecera (`.hpp`)**, ya que el compilador necesita conocer la definición completa para instanciar el código en tiempo de compilación. No se suelen separar en `.cpp`.
- En el **Ex 02**, asegúrate de que tu clase `Array` maneje correctamente los arrays vacíos (tamaño 0).

---
*42 Madrid - La práctica hace al maestro.*