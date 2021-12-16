#include "unity.h"
#include "buffer.h"

#define BUFSIZE sizeof(uint64_t)
uint8_t buf[BUFSIZE] = {0};



void setUp(void) {}

void tearDown(void) {}

void buffer_reset() {
      for (int i = 0; i < BUFSIZE; i++) 
        buf[i] = 0;
}

void buffer_print() {
    for (int i = 0; i < BUFSIZE; i++) 
        printf("%u ", buf[i]);
    puts("");
}

void Test_fail() {
    TEST_FAIL_MESSAGE("Failure test");
}

void Test_buffer_reset() {
    buffer_insert(buf, 0, 64, 0x5555555555555555);
    TEST_ASSERT_EQUAL_UINT64(0x5555555555555555, buffer_extract(buf, 0, 64));    
       
    buffer_reset();

    uint8_t expected[BUFSIZE] = {0, 0, 0, 0, 0, 0, 0, 0, };
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, buf, BUFSIZE);
}

void Test_buffer_insert_exanple() {
    buffer_reset();
    buffer_insert(buf, 12, 6, 24);
    uint8_t expected[BUFSIZE] = {0, 128, 1, 0, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, buf, BUFSIZE);
}

void Test_buffer_extract_example() {
    TEST_ASSERT_EQUAL_UINT64(24, buffer_extract(buf, 12, 6));    
}

void Test_buffer_insert_64bit() { 
    buffer_reset();
    buffer_insert(buf, 0, 64, UINT64_MAX);
    uint8_t expected[BUFSIZE] = {255, 255, 255, 255, 255, 255, 255, 255};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, buf, BUFSIZE);
}

void Test_buffer_extract_64bit() { 
    TEST_ASSERT_EQUAL_UINT64(UINT64_MAX, buffer_extract(buf, 0, 64));    
}

void Test_buffer_insert_striped() { 
    buffer_reset();
    buffer_insert(buf, 0, 64, 0x5555555555555555);
    uint8_t expected[BUFSIZE] = {85, 85, 85, 85, 85, 85, 85, 85};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, buf, BUFSIZE);
}

void Test_buffer_extract_striped() { 
    TEST_ASSERT_EQUAL_UINT64(0x5555555555555555, buffer_extract(buf, 0, 64));    
}

void Test_buffer_insert_invertstriped() { 
    buffer_reset();
    buffer_insert(buf, 0, 64, 0xaaaaaaaaaaaaaaaa);
    uint8_t expected[BUFSIZE] = {170, 170, 170, 170, 170, 170, 170, 170};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, buf, BUFSIZE);
}

void Test_buffer_extract_invertstriped() { 
    TEST_ASSERT_EQUAL_UINT64(0xaaaaaaaaaaaaaaaa, buffer_extract(buf, 0, 64));    
}


void Test_buffer_insert_wrongLen() { 
    buffer_reset();
    buffer_insert(buf, 8, 16, UINT64_MAX);
    uint8_t expected[BUFSIZE] = {0, 255, 255, 0, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, buf, BUFSIZE);
}

void Test_buffer_extract_wronglen() { 
    TEST_ASSERT_EQUAL_UINT64(UINT16_MAX, buffer_extract(buf, 8, 16));    
}

void Test_buffer_insert_multiple() {
    buffer_reset();

    buffer_insert(buf, 12, 6, 42);
    uint8_t expected1[BUFSIZE] = {0, 160, 2, 0, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected1, buf, BUFSIZE);

    buffer_insert(buf, 22, 8, 242);
    uint8_t expected2[BUFSIZE] = {0, 160, 130, 60, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected2, buf, BUFSIZE);
    
    buffer_insert(buf, 38, 12, 2429);
    uint8_t expected3[BUFSIZE] = {0, 160, 130, 60, 64, 95, 2, 0};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected3, buf, BUFSIZE);
} 

void Test_buffer_extract_multiple() {
    TEST_ASSERT_EQUAL_UINT64(42, buffer_extract(buf, 12, 6));    
    TEST_ASSERT_EQUAL_UINT64(242, buffer_extract(buf, 22, 8));    
    TEST_ASSERT_EQUAL_UINT64(2429, buffer_extract(buf, 38, 12));    
} 

void Test_buffer_overwrite() {
    buffer_reset();

    buffer_insert(buf, 22, 8, 242);
    uint8_t expected1[BUFSIZE] = {0, 0, 128, 60, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected1, buf, BUFSIZE);
    TEST_ASSERT_EQUAL_UINT64(242, buffer_extract(buf, 22, 8));    
    
    buffer_insert(buf, 22, 8, 189);
     uint8_t expected2[BUFSIZE] = {0, 0, 64, 47, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected2, buf, BUFSIZE);
    TEST_ASSERT_EQUAL_UINT64(189, buffer_extract(buf, 22, 8));    
}


int main(void)
{
    UNITY_BEGIN();
    // RUN_TEST(Test_fail);

    RUN_TEST(Test_buffer_reset);
    puts("");
    RUN_TEST(Test_buffer_insert_exanple); 
    RUN_TEST(Test_buffer_extract_example);
    puts("");
    RUN_TEST(Test_buffer_insert_64bit);
    RUN_TEST(Test_buffer_extract_64bit);
    puts("");
    RUN_TEST(Test_buffer_insert_striped);
    RUN_TEST(Test_buffer_extract_striped);
    puts("");
    RUN_TEST(Test_buffer_insert_invertstriped);
    RUN_TEST(Test_buffer_extract_invertstriped);
    puts("");
    RUN_TEST(Test_buffer_insert_wrongLen);
    RUN_TEST(Test_buffer_extract_wronglen);
    puts("");
    RUN_TEST(Test_buffer_insert_multiple);
    RUN_TEST(Test_buffer_extract_multiple);
    puts("");
    RUN_TEST(Test_buffer_overwrite);

    return UNITY_END();
}
