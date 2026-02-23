#include <Arduino.h>
#include <EEPROM.h>
#include "lector_rfid.h"

// Definiciones adicionales de pines
#define PIN_LED_VERDE 5
#define PIN_LED_ROJO 6
#define PIN_BOTON_SALIDA 4

const String MASTER_UID = "5B6E884F";
String tarjetaAutorizada;

void setup() {
    Serial.begin(9600);
    inicializarSistema();
    
    // Configuración de nuevos pines
    pinMode(PIN_LED_VERDE, OUTPUT);
    pinMode(PIN_LED_ROJO, OUTPUT);
    pinMode(PIN_BOTON_SALIDA, INPUT_PULLUP); // Resistencia interna activa

    // Cargar tarjeta desde memoria
    char datos[9];
    for (int i = 0; i < 8; i++) datos[i] = EEPROM.read(i);
    datos[8] = '\0';
    tarjetaAutorizada = String(datos);
    
    Serial.println("Sistema Profesional Listo.");
}

void abrirPuerta() {
    Serial.println("Abriendo puerta...");
    digitalWrite(PIN_LED_VERDE, HIGH);
    digitalWrite(RELAY_PIN, HIGH);
    delay(3000);
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(PIN_LED_VERDE, LOW);
}

void loop() {
    // 1. Revisar si alguien presionó el botón de salida
    if (digitalRead(PIN_BOTON_SALIDA) == LOW) {
        Serial.println("Botón de salida presionado");
        abrirPuerta();
    }

    // 2. Revisar si hay una tarjeta
    String uid = obtenerUID();
    if (uid != "") {
        if (uid == MASTER_UID) {
            Serial.println("Modo Programación: Esperando nueva tarjeta...");
            digitalWrite(PIN_LED_ROJO, HIGH); // Luz roja indica espera
            tone(BUZZER_PIN, 1500, 500);
            
            String nuevaUID = "";
            while(nuevaUID == "") {
                nuevaUID = obtenerUID();
                delay(100);
            }
            
            for (int i = 0; i < 8; i++) EEPROM.write(i, nuevaUID[i]);
            tarjetaAutorizada = nuevaUID;
            
            digitalWrite(PIN_LED_ROJO, LOW);
            tone(BUZZER_PIN, 2000, 200);
            Serial.println("Nueva tarjeta autorizada.");
            
        } else if (uid == tarjetaAutorizada) {
            abrirPuerta();
        } else {
            Serial.println("Acceso Denegado");
            digitalWrite(PIN_LED_ROJO, HIGH);
            tone(BUZZER_PIN, 400, 500);
            delay(1000);
            digitalWrite(PIN_LED_ROJO, LOW);
        }
    }
}