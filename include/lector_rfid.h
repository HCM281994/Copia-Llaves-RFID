#ifndef LECTOR_RFID_H
#define LECTOR_RFID_H

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

// Definiciones para Arduino Uno
#define RST_PIN 9
#define SS_PIN 10
#define BUZZER_PIN 8
#define RELAY_PIN 7

extern MFRC522 mfrc522; 

void inicializarSistema() {
    SPI.begin();
    mfrc522.PCD_Init();
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);
}

String obtenerUID() {
    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
        return "";
    }
    String uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        uid += (mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
        uid += String(mfrc522.uid.uidByte[i], HEX);
        if (i < mfrc522.uid.size - 1) uid += " ";
    }
    uid.toUpperCase();
    mfrc522.PICC_HaltA();
    return uid;
}

#endif