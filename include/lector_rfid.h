#include "lector_rfid.h"

// Inicializamos el objeto aquí si no se hizo en el .h
MFRC522 mfrc522(SS_PIN, RST_PIN);

void inicializarSistema() {
    SPI.begin();
    mfrc522.PCD_Init();
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW); 
    Serial.println("Lector RFID listo...");
}

String obtenerUID() {
    // Si no hay tarjeta nueva o no se puede leer, salimos
    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
        return "";
    }

    String uidString = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        uidString += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
        uidString += String(mfrc522.uid.uidByte[i], HEX);
    }
    uidString.toUpperCase();
    
    mfrc522.PICC_HaltA();      // Detiene lectura de la tarjeta actual
    mfrc522.PCD_StopCrypto1(); // Detiene el cifrado para la siguiente lectura
    
    return uidString;
}