*Este proyecto ha sido realizado como parte del currículo de 42 por jrollon-.*
<p align="center">
<img width="731" height="427" alt="e093e61ce06dbc37a4eea72c73a84b1b" src="https://github.com/user-attachments/assets/4a9d88b5-5ff0-4d54-b485-6d9e4cbd55e7" />
</p>

# 🍝 Philosophers — I think, therefore I eat

Un proyecto sobre la resolución del problema de los **filósofos comensales**, explorando los fundamentos del multi-threading en **C**. El objetivo es crear una simulación donde varios filósofos se sientan a una mesa redonda para comer, dormir y pensar, evitando que mueran por inanición y gestionando los recursos compartidos (tenedores) mediante **mutexes**.

---

## 📖 Descripción

**Philosophers** es una introducción al mundo de la computación concurrente. Cada filósofo es un **hilo (thread)** independiente que compite por recursos limitados (tenedores representados por **mutexes**). El reto principal es evitar condiciones de carrera (*data races*) y bloqueos mutuos (*deadlocks*).

### Las Reglas de la Mesa
1.  Los filósofos se sientan en círculo y solo pueden realizar una acción a la vez: **Comer**, **Dormir** o **Pensar**.
2.  Hay tantos tenedores como filósofos, situados entre cada uno de ellos.
3.  Para comer, un filósofo necesita **dos tenedores** (el de su izquierda y el de su derecha).
4.  Cuando termina de comer, deja los tenedores y empieza a dormir. Al despertar, empieza a pensar.
5.  La simulación se detiene si un filósofo muere de hambre o si todos han comido el número mínimo de veces especificado.

### Aspectos Técnicos
- **Multi-threading**: Implementado con la librería `pthread`. Cada filósofo es un hilo.
- **Sincronización**: Uso de `pthread_mutex` para proteger el acceso a los tenedores y a las variables críticas (estado de muerte, contador de comidas).
- **Gestión del tiempo**: Uso preciso de `gettimeofday` y `usleep` para monitorizar la supervivencia de los filósofos.
- **Monitoreo**: Un hilo adicional (el "juez") supervisa constantemente si algún filósofo ha superado su `time_to_die`.

---

## ✨ Características

- **Prevención de Deadlocks**: Implementación de una estrategia de espera para filósofos con ID impar para evitar que todos cojan un tenedor al mismo tiempo y se bloqueen.
- **Logs en tiempo real**: Registro detallado de cada acción con marca de tiempo precisa en milisegundos.
- **Lista Circular**: Los filósofos están organizados en una estructura de lista circular doblemente enlazada para facilitar la referencia a los tenedores vecinos.
- **Protección de Datos**: Todas las variables compartidas están protegidas por mutexes específicos para evitar *data races*.

---

## 🚀 Instalación y Uso

### Compilación

Clona el repositorio y compila el proyecto mediante el Makefile:

```bash
git clone https://github.com/J4P032/42CURSUS.git
cd 42CURSUS/03_Philosophers/philo
make
```

### Ejecución

El programa acepta los siguientes argumentos:

```bash
./philo [num_philos] [time_to_die] [time_to_eat] [time_to_sleep] [min_meals]
```

- **num_philos**: Número de filósofos y tenedores (ej: `5`).
- **time_to_die**: Tiempo (ms) que un filósofo puede estar sin comer (ej: `800`).
- **time_to_eat**: Tiempo (ms) que tarda un filósofo en comer (ej: `200`).
- **time_to_sleep**: Tiempo (ms) que el filósofo dedica a dormir (ej: `200`).
- **min_meals**: (Opcional) Número de veces que cada filósofo debe comer para terminar la simulación.

#### Ejemplo de éxito:
```bash
./philo 5 800 200 200
```

#### Ejemplo de muerte:
```bash
./philo 4 310 200 100
```

---

## 🛠️ Logs de Simulación

El programa imprime los cambios de estado con el siguiente formato:
- `timestamp_ms [ID] has taken a fork`
- `timestamp_ms [ID] is eating`
- `timestamp_ms [ID] is sleeping`
- `timestamp_ms [ID] is thinking`
- `timestamp_ms [ID] died`

```text
miniyo$ ./philo 2 410 200 200
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 2 has taken a fork
200 2 has taken a fork
200 2 is eating
400 1 is thinking
400 2 is sleeping
400 1 has taken a fork
...
```
