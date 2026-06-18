*Este proyecto ha sido realizado como parte del currículo de 42 por jrollon-.*

https://github.com/user-attachments/assets/98d3ef63-2e34-46f5-a36e-e0073af09c60


# 🍒 so_long — Pac-Man Edition

Un juego de plataformas en 2D desarrollado en **C** utilizando la librería gráfica **MiniLibX**. En esta versión, el proyecto recrea la estética y mecánicas del clásico **Pac-Man**, donde el jugador debe recolectar todos los objetos del mapa mientras evita a los enemigos para poder escapar.

---

## 📖 Descripción

**so_long** es el primer proyecto gráfico del currículo de 42. El objetivo es crear un juego sencillo que gestione ventanas, renderizado de imágenes y eventos de teclado. La lógica del juego se basa en un mapa cargado desde un archivo `.ber` que debe ser validado para asegurar que el jugador pueda completar el nivel.

### Mecánicas del Juego

- **El Jugador**: Controlas a Pac-Man (`P`). Tu objetivo es comer todos los puntos (`C`).
- **Coleccionables**: Debes recolectar todos los objetos (`C`) para desbloquear la salida.
- **La Salida**: Una vez recolectado todo, debes llegar a la salida (`E`) para ganar.
- **Enemigos (Exclusivo Bonus)**: Los fantasmas (`G`) patrullan el mapa. Aparecen únicamente al ejecutar la versión **bonus** del juego.
- **Contador de Pasos**: Cada movimiento se contabiliza y se muestra en la terminal (o en la ventana en la versión bonus).

---

## ✨ Características

- **Animaciones**: Pac-Man abre y cierra la boca al moverse y los fantasmas tienen ciclos de animación.
- **Gestión de Sprites**: Uso de transparencia y composición de imágenes para un renderizado fluido.
- **Validación de Mapa**: Algoritmo de *Flood Fill* para verificar que todos los coleccionables y la salida son alcanzables.
- **Eventos**: Cierre limpio de ventana (botón X, tecla ESC) y movimiento fluido con WASD o flechas.

---

## 🚀 Instalación y Compilación

### Requisitos previos (Linux)

Para utilizar la MiniLibX en Linux, necesitas instalar las dependencias de X11:
```bash
sudo apt-get install libx11-dev libxext-dev
```

### 🛠️ Compilación de la MiniLibX

Es común que la carpeta de la MiniLibX venga sin los permisos adecuados o necesite una pre-configuración. Sigue estos pasos para compilarla correctamente dentro de tu proyecto:

1.  Dale **permisos de ejecución** al script de configuración:
    ```bash
    chmod +x minilibx-linux/configure
    ```
2.  **Ejecuta el script** de configuración:
    ```bash
    ./minilibx-linux/configure
    ```
3.  Compila la librería:
    ```bash
    make -C minilibx-linux
    ```
4.  Si no compila y da errores de too few arguments en llamadas a funciones, es por el nuevo gcc 
    que es más restrictivo.. En el Makefile.. en flags hay que poner -std=gnu11 (dos unos) e irá a una version más antigua. Esto hay que hacerlo en los makefile de la minilibx y en el makefile de text. PERO tambien en el makefile del proyecto.

### Compilación del Juego

Una vez compilada la MiniLibX, puedes compilar el juego:

```bash
make          # Genera el ejecutable 'so_long' (versión base)
make bonus    # Genera el ejecutable 'so_long_bonus' (incluye enemigos y animaciones)
```

---

## 🎮 Cómo Jugar

Ejecuta el programa pasando un mapa válido como argumento. Nota la diferencia entre las versiones:

```bash
# Versión estándar (sin enemigos)
./so_long maps/map1.ber

# Versión completa (los fantasmas aparecen aquí)
./so_long_bonus maps/map1.ber
```

### Controles

| Tecla | Acción |
|-------|--------|
| `W` o `↑` | Mover hacia arriba |
| `S` o `↓` | Mover hacia abajo |
| `A` o `←` | Mover hacia la izquierda |
| `D` o `→` | Mover hacia la derecha |
| `ESC` | Salir del juego |

---

## 🗺️ Formato del Mapa (.ber)

El mapa debe ser rectangular y estar rodeado de muros (`1`). Los fantasmas se representan con la letra `G` (solo activos en el bonus).

```text
1111111111111
1P00000000001
1011101110111
101C101C101C1
10000G0000001
1111111111111
```
