#include "unity.h"
#include "buffer.h"

#define BUFSIZE sizeof(uint64_t)
uint8_t buf[BUFSIZE] = {0};


void setUp(void) {

}

void tearDown(void) {}

void Test_buffer_insert_exanple() {
    buffer_insert(buf, 12, 6, 24);
    uint8_t expected[BUFSIZE] = {0, 128, 1, 0, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, buf, BUFSIZE);
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

    // RUN_TEST(Test_buffer_insert_64bit);
    // RUN_TEST(Test_buffer_extract_64bit);

    // RUN_TEST(Test_buffer_insert_wrongLen);

    return UNITY_END();
}
