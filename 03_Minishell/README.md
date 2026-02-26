*Este proyecto ha sido realizado como parte del currículo de 42 por mpico-bu y jrollon-.*

<p align="center">
<img width="809" height="393" alt="8552ce661de13bb78434bed06fb6bbcb" src="https://github.com/user-attachments/assets/d689961b-2916-49cc-9c38-d814b9f0b7aa" />
</p>

# 🐚 minishell — As beautiful as a shell

Un intérprete de comandos (shell) minimalista implementado en **C**, basado en el funcionamiento de **Bash**. El proyecto abarca desde el parsing de la entrada del usuario hasta la ejecución de procesos, gestión de señales y redirecciones de archivos.

---

## 📖 Descripción

**minishell** es uno de los proyectos más desafiantes del núcleo de 42. El objetivo es crear nuestra propia shell funcional, lo que implica recrear gran parte de la lógica de un sistema operativo para la gestión de procesos y comunicación entre ellos.

El programa muestra un prompt personalizado (`miniyo$`) y es capaz de:

- **Gestionar el historial** de comandos mediante la librería `readline`.
- **Buscar y ejecutar** ejecutables basados en la variable de entorno `PATH` o mediante rutas relativas/absolutas.
- **Interpretar comillas** simples (`'`) y dobles (`"`) de forma idéntica a Bash.
- **Expandir variables de entorno** (ej: `$USER`, `$HOME`) y el estado de salida del último comando (`$?`).
- **Manejar señales** de forma interactiva:
  - `Ctrl-C`: Muestra un nuevo prompt en una línea vacía.
  - `Ctrl-D`: Finaliza la ejecución de la shell (EOF).
  - `Ctrl-\`: No hace nada (ignora la señal de quit).

### Aspectos Técnicos

- **Parsing y Tokenización**: División de la entrada en comandos, argumentos y operadores.
- **Gestión de Procesos**: Uso de `fork`, `wait`, `waitpid` y `execve`.
- **Pipes y Redirecciones**: Comunicación entre procesos mediante `pipe` y manipulación de descriptores de archivos con `dup2`.
- **Environment**: Gestión propia de las variables de entorno para que persistan y se modifiquen durante la sesión.

---

## ✨ Características

### Comandos Integrados (Built-ins)

Se han implementado los siguientes comandos internos para que funcionen sin necesidad de ejecutables externos:

| Comando | Descripción |
|---------|-------------|
| `echo` | Muestra mensajes en pantalla (soporta la opción `-n`) |
| `cd` | Cambia el directorio de trabajo actual |
| `pwd` | Imprime la ruta del directorio actual |
| `export` | Exporta variables de entorno |
| `unset` | Elimina variables de entorno |
| `env` | Muestra el entorno actual |
| `exit` | Cierra la shell de forma controlada |

### Operadores Soportados

| Operador | Descripción |
|----------|-------------|
| `|` | **Pipes**: Conecta la salida de un comando con la entrada del siguiente |
| `<` | **Redirección de entrada**: Lee desde un archivo |
| `>` | **Redirección de salida**: Escribe en un archivo (sobrescribe) |
| `<<` | **Here-doc**: Lee entrada hasta encontrar un delimitador específico |
| `>>` | **Redirección de salida**: Escribe en un archivo (modo append) |

---

## 🚀 Instalación y Uso

### Requisitos previos

- Compilador `cc` y `make`.
- Librería `readline` instalada en el sistema.

### Compilación

Clona el repositorio y compila el proyecto:

```bash
git clone https://github.com/tu-usuario/42CURSUS.git
cd 42CURSUS/03_Minishell
make
```

### Ejecución

Simplemente inicia el binario generado:

```bash
./minishell
```

---

## 🛠️ Estructura del Proyecto

El código está organizado para separar la lógica de parsing de la de ejecución:

- `src/`: Contiene el código fuente principal (built-ins, lógica de señales, ejecución).
- `inc/`: Archivos de cabecera (`.h`) con las estructuras y prototipos.
- `libft/`: Nuestra librería de funciones auxiliares personalizada.
- `Tester_Japo/`: Scripts de corrección y tests para asegurar el cumplimiento de los requisitos.

```text
miniyo$ echo "Welcome to minishell" | tr 'a-z' 'A-Z'
WELCOME TO MINISHELL
```
