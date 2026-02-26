*Este proyecto ha sido realizado como parte del currículo de 42 por marcoga2 y jrollon-.*

# 🎮 cub3D — Motor de Raycasting

Un motor gráfico en primera persona implementado en **C**, inspirado en el mítico **Wolfenstein 3D**. El proyecto utiliza la técnica de **raycasting** para renderizar un entorno 3D a partir de un mapa bidimensional, gestionando texturas, eventos de teclado y ratón mediante la librería **MiniLibX**.

---

## 📖 Descripción

**cub3D** es un proyecto de la escuela 42 que tiene como objetivo profundizar en los conceptos de matemáticas aplicadas a la computación gráfica y el manejo de ventanas/eventos. El motor permite al usuario navegar por un laberinto con una perspectiva realista, calculando la distancia a las paredes en tiempo real para proyectar su altura en pantalla.

El programa interpreta archivos de configuración con extensión **.cub** que definen:

- **Texturas específicas** para cada orientación de muro (Norte, Sur, Este y Oeste).
- **Colores personalizados** para el suelo y el techo en formato RGB.
- **Diseño del mapa**, validando que el espacio esté completamente cerrado por muros y contenga una posición de inicio válida.

### Aspectos Técnicos

- Implementación del algoritmo **DDA (Digital Differential Analyzer)** para un raycasting eficiente.
- Gestión de ventanas y renderizado de frames utilizando un **buffer de imagen** para evitar el parpadeo.
- Manejo de eventos de entrada (teclado y ratón) para el movimiento y la rotación de la cámara.
- Parsing robusto de archivos de configuración y gestión de errores detallada.
- Gestión de memoria optimizada para evitar *leaks* en el cierre del programa.

---

## ✨ Características

### Controles del Juego

| Tecla / Acción | Función |
|----------------|-----------|
| `W`, `A`, `S`, `D` | Movimiento del jugador (Adelante, Izquierda, Atrás, Derecha) |
| `←` / `→` | Rotación de la cámara |
| `Ratón` | Rotación de la cámara (Bonus) |
| `ESPACIO` | Salto / Acción (Bonus) |
| `ESC` | Cerrar el programa |

### Funcionalidades Extra (Bonus)

El proyecto incluye mejoras significativas respecto a la versión base:

- **Minimapa**: Una representación 2D en tiempo real de la posición del jugador.
- **Sprites**: Objetos y enemigos renderizados en el entorno 3D.
- **Puertas**: Elementos interactivos que se pueden abrir y cerrar.
- **Animaciones**: Ciclos de movimiento para sprites y elementos del entorno.
- **Rotación con ratón**: Control fluido de la cámara mediante el movimiento del puntero.

---

## 🚀 Instalación y Uso

### Requisitos previos

- Sistema operativo Linux (o macOS con los ajustes correspondientes de MLX).
- Compilador `cc` (o `gcc`) y `make`.
- Librerías de X11 instaladas (`libx11-dev`, `libxext-dev`).

### Compilación

Clona el repositorio y compila el proyecto:

```bash
git clone https://github.com/tu-usuario/42CURSUS.git
cd 42CURSUS/04_Cub3D
make
```

Para incluir los bonus:

```bash
make bonus
```

### Ejecución

Lanza el programa pasando como argumento una ruta a un archivo de mapa válido:

```bash
./cub3D maps/map4.cub
```

---

## 🗺️ Formato del Mapa (.cub)

Un ejemplo de configuración válida incluye las rutas a los archivos `.xpm` y la definición del mapa:

```text
NO ./textures/NO_256.xpm
SO ./textures/SO_256.xpm
WE ./textures/WE_256.xpm
EA ./textures/EA_256.xpm

F 220,100,0
C 225,30,0

1111111
1100N11
1111111
```