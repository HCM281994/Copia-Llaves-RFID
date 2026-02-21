#include <Arduino.h>
#include "lector_rfid.h"

// ID de tu tarjeta Maestra
const String MASTER_UID = "5B6E884F";

void setup() {
    Serial.begin(9600);
    inicializarSistema();
    Serial.println("SISTEMA DE SEGURIDAD ACTIVADO");
    Serial.println("Esperando tarjeta maestra...");
}

void loop() {
    String uid = obtenerUID();
    
    if (uid != "") {
        Serial.print("UID Detectado: ");
        Serial.println(uid);
        
        if (uid == MASTER_UID) {
            Serial.println("ACCESO CONCEDIDO - Bienvenida, Master Card.");
            tone(BUZZER_PIN, 2000, 500); // Pitido largo de éxito
            
            digitalWrite(RELAY_PIN, HIGH);
            delay(3000); // Mantenemos el relay activo 3 segundos
            digitalWrite(RELAY_PIN, LOW);
        } else {
            Serial.println("ACCESO DENEGADO - Tarjeta no autorizada.");
            // Pitidos cortos de error
            for(int i=0; i<3; i++){
                tone(BUZZER_PIN, 500, 100);
                delay(150);
            }
        }
    }
}