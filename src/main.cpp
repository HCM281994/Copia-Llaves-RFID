#include <Arduino.h>
#include <EEPROM.h>
#include "lector_rfid.h"

const String MASTER_UID = "5B6E884F";
String tarjetaAutorizada;

void setup() {
    Serial.begin(9600);
    inicializarSistema();
    
    // Leer la tarjeta guardada en EEPROM (si existe)
    char datos[9];
    for (int i = 0; i < 8; i++) {
        datos[i] = EEPROM.read(i);
    }
    datos[8] = '\0';
    tarjetaAutorizada = String(datos);
    
    Serial.println("Sistema Listo. Master: " + MASTER_UID);
    Serial.println("Autorizada actual: " + tarjetaAutorizada);
}

void loop() {
    String uid = obtenerUID();
    
    if (uid != "") {
        if (uid == MASTER_UID) {
            Serial.println("¡Modo Programación Activado! Pase la nueva tarjeta...");
            tone(BUZZER_PIN, 1500, 1000); // Pitido largo de aviso
            
            // Esperar a la nueva tarjeta
            String nuevaUID = "";
            while(nuevaUID == "") {
                nuevaUID = obtenerUID();
                delay(100);
            }
            
            // Guardar en EEPROM
            for (int i = 0; i < 8; i++) {
                EEPROM.write(i, nuevaUID[i]);
            }
            tarjetaAutorizada = nuevaUID;
            Serial.println("Nueva tarjeta guardada: " + nuevaUID);
            tone(BUZZER_PIN, 2000, 500);
            
        } else if (uid == tarjetaAutorizada) {
            Serial.println("Acceso Concedido");
            digitalWrite(RELAY_PIN, HIGH);
            delay(3000);
            digitalWrite(RELAY_PIN, LOW);
        } else {
            Serial.println("Acceso Denegado");
            tone(BUZZER_PIN, 400, 500);
        }
    }
}