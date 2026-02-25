#include <Arduino.h>
#include <unity.h>

// Aquí incluimos el header que contiene la lógica que queremos probar
// Asegúrate de que este archivo exista en include/ o src/
#include "lector_rfid.h" 

void setUp(void) {
    // Se ejecuta ANTES de cada test (opcional)
}

void tearDown(void) {
    // Se ejecuta DESPUÉS de cada test (opcional)
}

// CASO DE PRUEBA 1: Verificar comparación de UIDs
void test_comparacion_uid_valido(void) {
    uint8_t uid_guardado[] = {0x12, 0x34, 0x56, 0x78};
    uint8_t uid_leido[]    = {0x12, 0x34, 0x56, 0x78};
    
    // Suponiendo que tienes una función que retorna bool
    // TEST_ASSERT_TRUE(compararUID(uid_leido, uid_guardado));
}

// CASO DE PRUEBA 2: Verificar denegación de acceso
void test_comparacion_uid_invalido(void) {
    uint8_t uid_maestro[] = {0xAA, 0xBB, 0xCC, 0xDD};
    uint8_t uid_ajeno[]   = {0x11, 0x22, 0x33, 0x44};
    
    // TEST_ASSERT_FALSE(compararUID(uid_ajeno, uid_maestro));
}

void setup() {
    // Espera para que el monitor serial se estabilice
    delay(2000);

    UNITY_BEGIN(); // Inicia el framework de pruebas
    
    RUN_TEST(test_comparacion_uid_valido);
    RUN_TEST(test_comparacion_uid_invalido);
    
    UNITY_END(); // Finaliza las pruebas
}

void loop() {
    // En pruebas unitarias, el loop se deja vacío
}