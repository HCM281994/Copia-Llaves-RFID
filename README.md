# 🔑 Sistema de Control de Acceso y Gestión de Llaves RFID

Este repositorio contiene el desarrollo de un sistema de control de acceso inteligente basado en tecnología **RFID (13.56 MHz)**. El proyecto ha sido diseñado bajo estándares de ingeniería de software para sistemas embebidos, utilizando una arquitectura modular y gestión eficiente de memoria no volátil.

---

## 🚀 Descripción General
El sistema permite la lectura, validación y administración de llaves inteligentes (tags RFID). A diferencia de scripts convencionales, este firmware implementa una lógica de estados sólida para la gestión de accesos, feedback visual/sonoro y almacenamiento seguro de identidades autorizadas.

### Puntos Clave del Desarrollo:
* **Arquitectura Modular**: Separación de lógica en capas mediante directorios `src`, `lib` e `include`.
* **Gestión de EEPROM**: Implementación de rutinas para el guardado y recuperación de IDs, asegurando la persistencia de datos ante cortes de energía.
* **Validación I/O**: Control de periféricos (LEDs y botones de salida) con manejo de debouncing y estados claros.

---

## 🛠 Tech Stack
* **Lenguaje**: C++ orientado a objetos para sistemas embebidos.
* **Entorno de Desarrollo**: VS Code + PlatformIO IDE.
* **Framework**: Arduino Core.
* **Hardware**:
    * Microcontrolador Atmel AVR (Arduino Uno R3).
    * Lector RFID-RC522.
    * Tags MIFARE Classic 1K.

---

## 🏗 Estructura del Proyecto
El proyecto sigue una organización industrial para facilitar el mantenimiento y escalabilidad:

* **`src/`**: Lógica principal y bucle de control.
* **`include/`**: Definición de cabeceras, mapas de memoria y configuración de pines.
* **`lib/`**: Controladores específicos para el hardware RFID y gestión de memoria.
* **`test/`**: Ent
