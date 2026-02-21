#include "lector_rfid.h"

// Aquí definimos el objeto que el .h declaró como 'extern'
MFRC522 mfrc522(SS_PIN, RST_PIN);

void inicializarSistema() {
    SPI.begin();
    mfrc522.PCD_Init();
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);
}

String obtenerUID() {
    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
        return "";
    }

    String uidString = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        uidString += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
        uidString += String(mfrc522.uid.uidByte[i], HEX);
    }
    uidString.toUpperCase();
    mfrc522.PICC_HaltA();
    return uidString;
}