#ifndef LECTOR_RFID_H
#define LECTOR_RFID_H

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

// Definiciones de Hardware
#define RST_PIN 9
#define SS_PIN 10x  
#define BUZZER_PIN 8
#define RELAY_PIN 7

// Declaración de objetos y funciones
extern MFRC522 mfrc522;

void inicializarSistema();
String obtenerUID();

#endif