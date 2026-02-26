*Este proyecto ha sido realizado como parte del currículo de 42 por jrollon-.*

# 📡 minitalk — Comunicación mediante Señales UNIX

Un sistema de comunicación cliente-servidor implementado en **C** que utiliza únicamente señales **SIGUSR1** y **SIGUSR2** para transmitir datos. A diferencia de las implementaciones estándar, este proyecto incluye un robusto protocolo de verificación y soporte para múltiples clientes.

---

## 📖 Descripción

**minitalk** tiene como objetivo transmitir mensajes de texto entre dos procesos independientes. La dificultad reside en que solo disponemos de dos "banderas" (las señales) para enviar información binaria bit a bit.

### Gestión Multicliente Simultánea

El servidor está diseñado con una estructura de lista enlazada (`t_client`) que le permite **gestionar varios clientes al mismo tiempo**. 
- El servidor mantiene un registro de cada cliente (basado en su PID).
- Es capaz de recibir fragmentos de mensajes de diferentes fuentes sin mezclar la información.
- Mantiene estados independientes para cada conexión activa.

---

## 🛡️ Protocolo de Verificación (Estilo TCP)

Para garantizar que el mensaje llegue íntegro y sin errores de sincronización (muy comunes en el uso de señales), se ha implementado un protocolo de control:

1.  **Fórmula de Verificación**: Antes de enviar el mensaje, el cliente calcula una "fórmula" (una suma incremental de los caracteres del string).
2.  **Transmisión del Header**: El cliente envía primero el tamaño del mensaje y el resultado de su fórmula.
3.  **Comparación en Servidor**: Una vez recibido el mensaje completo, el servidor calcula su propia suma de los caracteres recibidos.
4.  **Confirmación / Reintento**:
    - **Si coinciden**: El servidor imprime el mensaje y envía una señal de confirmación (`B_1`) al cliente.
    - **Si NO coinciden**: El servidor detecta la corrupción de datos, envía una señal de error (`B_0`) y fuerza al cliente a reiniciar la transmisión desde el principio.

---

## ✨ Características Técnicas

- **Bit-masking**: Uso de máscaras de bits para extraer y enviar cada bit de los caracteres.
- **Sigaction**: Uso de `sigaction` con `SA_SIGINFO` para capturar el PID del emisor y permitir la comunicación bidireccional.
- **Estructura Global**: Uso de una variable global mínima y controlada para el acceso desde los manejadores de señales.

---

## 🚀 Instalación y Uso

### Compilación

Compila tanto el servidor como el cliente:

```bash
make
```

### Ejecución

1.  **Inicia el servidor** en una terminal:
    ```bash
    ./server
    ```
    El servidor imprimirá su **PID** (ej: `PID: 12345`).

2.  **Inicia el cliente** en otra terminal, pasando el PID del servidor y el mensaje:
    ```bash
    ./client 12345 "Hola mundo brutal"
    ```

---

## 🛠️ Estructura del Mensaje

El flujo de envío sigue este orden binario:
1.  **Header**: Número de bytes del mensaje.
2.  **Fórmula**: Suma de verificación (Checksum).
3.  **Cuerpo**: El mensaje bit a bit (8 bits por carácter).

```text
miniyo$ ./server
PID: 4242
4243: Hola desde cliente 1
4244: Hola desde cliente 2 simultáneo
```