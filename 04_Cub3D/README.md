*Este proyecto ha sido realizado como parte del currículo de 42 por marcoga2 y jrollon-.*


https://github.com/user-attachments/assets/8f99ddc9-7a3f-4bfc-82e1-77f3313709a6


# 🎮 cub3D — Motor de Raycasting

Un motor gráfico en primera persona implementado en **C**, inspirado en el mítico **Wolfenstein 3D**. El proyecto utiliza la técnica de **raycasting** para renderizar un entorno 3D a partir de un mapa bidimensional, gestionando texturas, eventos de teclado y ratón mediante la librería **MiniLibX**.

---

## 📖 Descripción

**cub3D** es un proyecto de la escuela 42 que tiene como objetivo profundizar en los conceptos de matemáticas aplicadas a la computación gráfica y el manejo de ventanas/eventos. El motor permite al usuario navegar por un laberinto con una perspectiva realista, calculando la distancia a las paredes en tiempo real para proyectar su altura en pantalla.

El programa interpreta archivos de configuración con extensión **.cub** que definen texturas específicas para cada muro, colores para suelo/techo y el diseño del mapa.

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

- **Minimapa**: Representación 2D en tiempo real.
- **Sprites**: Objetos y enemigos renderizados en 3D.
- **Puertas**: Elementos interactivos.
- **Animaciones**: Ciclos de movimiento.
- **Rotación con ratón**: Control fluido de la cámara.

---

## 🚀 Instalación y Uso

### Requisitos previos

Asegúrate de tener instaladas las dependencias de X11 en tu sistema Linux:
```bash
sudo apt-get install libx11-dev libxext-dev libbsd-dev
```

### 🛠️ Compilación de la MiniLibX

Antes de compilar el proyecto principal, es necesario preparar y compilar la librería gráfica **minilibx-linux**. Sigue estos pasos:

1.  Dale permisos de ejecución al script de configuración:
    ```bash
    chmod +x minilibx-linux/configure
    ```
2.  Compila la librería:
    ```bash
    make -C minilibx-linux
    ```

### Compilación del Proyecto

Una vez lista la MiniLibX, puedes compilar el juego:

```bash
make          # Compila la versión base
make bonus    # Compila la versión con extras
```

### Ejecución

Lanza el programa pasando un archivo de mapa válido:

```bash
./cub3D maps/map4.cub
```

---

## 🗺️ Formato del Mapa (.cub)

Ejemplo de configuración de texturas y colores:

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
