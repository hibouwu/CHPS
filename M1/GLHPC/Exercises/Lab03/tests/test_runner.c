#include "unity.h"

extern void test_grayscale_image_creation(void);
extern void test_rgb_image_creation(void);
extern void test_image_copy(void);
extern void test_image_copy_performance(void);

extern void test_rotate_90_clockwise_basic(void);
extern void test_rotate_90_clockwise_original_crash_size(void);

void setUp(void) {}
void tearDown(void) {}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_grayscale_image_creation);
    RUN_TEST(test_rgb_image_creation);
    RUN_TEST(test_image_copy);
    RUN_TEST(test_image_copy_performance);

    printf("\n=== Rotation Non-Regression Tests ===\n");
    RUN_TEST(test_rotate_90_clockwise_basic);
    RUN_TEST(test_rotate_90_clockwise_original_crash_size);
    
    return UNITY_END();
}
