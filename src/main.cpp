#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

// Definición de pines para el RC522 (19)
#define RST_PIN 9
#define SS_PIN 10
// Pin para el Buzzer Activo (9)
#define BUZZER_PIN 8 

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Pitido inicial: Indica que el sistema en Ubuntu arrancó bien
  digitalWrite(BUZZER_PIN, HIGH);
  delay(200);
  digitalWrite(BUZZER_PIN, LOW);
  
  Serial.println("--- SISTEMA DE LECTURA DE LLAVES PROFESIONAL ---");
  Serial.println("Acerque la llave al modulo RC522...");

  // Añade esto en el setup
pinMode(7, OUTPUT);
digitalWrite(7, LOW); // Relay apagado al inicio
}

void loop() {
  // 1. Detectar tarjeta
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // 2. Convertir el ID a String para poder compararlo
  String uidLeido = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uidLeido += (mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    uidLeido += String(mfrc522.uid.uidByte[i], HEX);
    if (i < mfrc522.uid.size - 1) uidLeido += " "; // Añade espacio entre bytes
  }
  uidLeido.toUpperCase();

  // 3. Mostrar en monitor serial
  Serial.print("ID detectado: [");
  Serial.print(uidLeido);
  Serial.println("]");

  // 4. Lógica de comparación (Monetización: Acceso VIP)
  // REEMPLAZA "A1 B2 C3 D4" por el ID que anotaste de tu tarjeta azul
  if (uidLeido == "5B 6E 88 4F") { 
    Serial.println(">>> ACCESO CONCEDIDO: Llave Maestra <<<");
    // Añade esto dentro del "if" cuando la llave es correcta
digitalWrite(7, HIGH); // Activa el relay (se escuchará un "clic")
Serial.println(">>> RELAY ACTIVADO - PUERTA ABIERTA <<<");
delay(3000);           // Mantiene abierto por 3 segundos
digitalWrite(7, LOW);  // Cierra el relay

    // Sonido de éxito (dos pitidos rápidos)
    tone(BUZZER_PIN, 2000); delay(100); noTone(BUZZER_PIN);
    delay(50);
    tone(BUZZER_PIN, 2500); delay(100); noTone(BUZZER_PIN);
  } 
  else {
    Serial.println(">>> AVISO: Llave no registrada en sistema <<<");
    // Sonido de error (un pitido largo grave)
    tone(BUZZER_PIN, 500); delay(500); noTone(BUZZER_PIN);
  }

  mfrc522.PICC_HaltA();
  delay(1000); // Pausa de 1 segundo para no saturar el monitor
}