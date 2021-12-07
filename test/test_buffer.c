#include "unity.h"
#include "buffer.h"

uint8_t buf[8] = {0};


void setUp(void) {

}

void tearDown(void) {}

void Test_buffer_insert_exanple() {
    buffer_insert(buf, 12, 6, 24);
}

void Test_buffer_extract_example() {
    TEST_ASSERT_EQUAL_UINT64(24, buffer_extract(buf, 12, 6));    


}

// void Test_buffer_insert_() { }
// void Test_buffer_extract_() { }

void Test_buffer_insert_64bit() { }
void Test_buffer_extract_64bit() { }

void Test_buffer_insert_wrongLen() { }



int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(Test_buffer_insert_exanple);
    RUN_TEST(Test_buffer_extract_example);

    RUN_TEST(Test_buffer_insert_64bit);
    RUN_TEST(Test_buffer_extract_64bit);

    RUN_TEST(Test_buffer_insert_wrongLen);

    return UNITY_END();
}
