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