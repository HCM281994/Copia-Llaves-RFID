#include <Arduino.h>
#include "lector_rfid.h"

void setup() {
    Serial.begin(9600);
    inicializarSistema(); 
    Serial.println("Sistema Iniciado - Esperando Tarjeta...");
}

void loop() {
    String uid = obtenerUID();
    
    if (uid != "") {
        Serial.print("Tarjeta detectada: ");
        Serial.println(uid);
        
        // Feedback sonoro rápido
        tone(BUZZER_PIN, 1500, 200);
        
        // Prueba de Relay
        digitalWrite(RELAY_PIN, HIGH);
        delay(1000);
        digitalWrite(RELAY_PIN, LOW);
    }
}