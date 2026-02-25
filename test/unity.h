#include <unity.h>
#include "access_logic.h"

void test_valid_uid_allows_access(void) {
    uint8_t stored_uid[] = {0xDE, 0xAD, 0xBE, 0xEF};
    uint8_t input_uid[]  = {0xDE, 0xAD, 0xBE, 0xEF};
    
    // La función debe retornar true al ser IDs idénticos
    TEST_ASSERT_TRUE(validate_access(input_uid, stored_uid));
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_valid_uid_allows_access);
    UNITY_END();
}