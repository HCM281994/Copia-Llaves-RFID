# Arquitectura del Proyecto: Control de Acceso RFID

Este proyecto implementa un sistema de control de acceso modular basado en la plataforma Arduino y el framework PlatformIO. La arquitectura ha sido diseñada bajo principios de separación de responsabilidades para facilitar el mantenimiento y la escalabilidad.

## Estructura de Archivos

### 1. platformio.ini (Configuración de Entorno)
Archivo de manifiesto que define la configuración del hardware, la velocidad de comunicación del puerto serial y las dependencias de librerías externas (MFRC522). Permite la portabilidad del proyecto a diferentes placas de desarrollo.

### 2. include/lector_rfid.h (Interfaz de Usuario/Contrato)
Contiene las definiciones de hardware (pines), constantes del sistema y las declaraciones de funciones. Actúa como el "plano" del módulo RFID, permitiendo que otros archivos conozcan las capacidades del sensor sin necesidad de conocer su implementación interna.

### 3. src/lector_rfid.cpp (Implementación de Bajo Nivel)
Desarrolla la lógica del controlador (driver) del sensor MFRC522. Gestiona la comunicación SPI, el formateo del UID de las tarjetas y la detención de lecturas redundantes. Encapsula la complejidad técnica del sensor.

### 4. src/main.cpp (Lógica de Negocio y Orquestación)
Es el núcleo del sistema. Coordina la interacción entre las entradas (lector RFID, botón de salida) y las salidas (Relay, LEDs, Buzzer). Implementa la gestión de permisos mediante la comparación de UIDs y la persistencia de datos en la memoria EEPROM.


## Flujo de Datos
1. **Captura**: El sensor detecta un campo magnético y extrae el UID.
2. **Procesamiento**: El módulo `lector_rfid` formatea el UID como un String hexadecimal.
3. **Validación**: `main.cpp` compara el UID con la Master Card o con los datos en la EEPROM.
4. **Acción**: Se activan las salidas digitales (Relay/LEDs) según el resultado de la validación.

## 🔄 Diagrama de Flujo de la Lógica de Control

```mermaid
graph TD
    A[Inicio: Power On] --> B[Inicializar Hardware: RFID, LEDs, Buzzer]
    B --> C[Cargar IDs Autorizados desde EEPROM]
    C --> D{¿Tarjeta Detectada?}
    D -- No --> D
    D -- Sí --> E[Leer UID de la Tarjeta]
    E --> F{¿UID coincide con Maestro?}
    
    F -- Sí --> G[Modo Programación: Añadir/Borrar]
    F -- No --> H{¿UID en Lista Autorizados?}
    
    H -- Sí --> I[ACCESO CONCEDIDO: Activar Relé]
    H -- No --> J[ACCESO DENEGADO: Alerta]
    
    I --> K[Resetear Estado]
    J --> K
    G --> K
    K --> D

    Descripción Técnica de los Estados:
Inicialización: El sistema verifica la integridad del bus SPI para el lector MFRC522 y recupera los punteros de memoria de la carpeta lib/ para gestionar la EEPROM.

Ciclo de Escaneo (Polling): El microcontrolador se mantiene en un bucle de baja carga hasta que se detecta un cambio de campo en la antena RFID.

Validación de Identidad: Se realiza una comparación bit a bit del UID leído contra el array de IDs cargado en el arranque. Esta lógica modular reside en los archivos de la carpeta src/.

Gestión de Acceso:

Acceso Concedido: Se dispara una interrupción o delay no bloqueante para el actuador.

Acceso Denegado: El sistema ignora lecturas consecutivas de la misma tarjeta durante un breve periodo para evitar spam en el log serial.

💾 Mapa de Memoria EEPROM
Para garantizar la persistencia de las identidades autorizadas, el sistema utiliza un esquema de direccionamiento estático en la EEPROM del microcontrolador. La estructura está diseñada para minimizar los ciclos de escritura y maximizar la vida útil de la memoria.

## 💾 Mapa de Distribución de Memoria EEPROM

Para asegurar la persistencia de los datos y la eficiencia en la lectura, se ha definido el siguiente mapa de memoria en la EEPROM del microcontrolador:

| Dirección (Hex) | Tamaño (Bytes) | Campo Técnico         | Función del Sistema                                     |
| :---           | :---           | :---                  | :---                                                    |
| **0x00** | 1              | `MAGIC_BYTE`          | Firma de validación (Indica si la EEPROM fue inicializada). |
| **0x01** | 1              | `KEY_COUNT`           | Contador total de llaves registradas en el sistema.     |
| **0x02** | 4              | `MASTER_UID`          | UID de la llave maestra con permisos de programación.   |
| **0x06** | 4              | `SLOT_01_UID`         | Primer identificador de acceso autorizado.               |
| **0x0A** | 4              | `SLOT_02_UID`         | Segundo identificador de acceso autorizado.              |
| **0x0E** | 4              | `SLOT_03_UID`         | Tercer identificador de acceso autorizado.               |
| **...** | 4              | `SLOT_N_UID`          | Espacio reservado para llaves adicionales (Slots 04-99). |

Lógica de Gestión de Memoria:
Lectura en el Arranque: Durante la fase de inicialización (localizada en src/), el sistema lee el Magic Byte. Si es válido, carga los UIDs en un array en la memoria RAM para una validación de acceso instantánea.

Escritura Protegida: Solo la Master Key puede activar el modo de programación para escribir en nuevos offsets de memoria, evitando modificaciones accidentales.

Integridad de Datos: Se implementa una validación simple para asegurar que no se guarden UIDs duplicados o incompletos.
