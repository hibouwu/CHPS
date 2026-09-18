#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <time.h>
#include <stdio.h>
#include "unity.h"
#include "transformation.h"
#include <stdlib.h>
#include <stdint.h>

void test_grayscale_image_creation(void){
    printf("Testing grayscale image creation...\n");
    Image *img = create_image(100, 100, 1);
    TEST_ASSERT_NOT_NULL(img);
    TEST_ASSERT_EQUAL(100, img->width);
    TEST_ASSERT_EQUAL(100, img->height);
    TEST_ASSERT_EQUAL(1, img->channels);
    TEST_ASSERT_NOT_NULL(img->pixels[0]);
    TEST_ASSERT_NULL(img->pixels[1]);
    TEST_ASSERT_NULL(img->pixels[2]);
    free_image(img);
}

void test_rgb_image_creation(void){
    printf("Testing RGB image creation...\n");
    Image *img = create_image(100, 100, 3);
    TEST_ASSERT_NOT_NULL(img);
    TEST_ASSERT_EQUAL(100, img->width);
    TEST_ASSERT_EQUAL(100, img->height);
    TEST_ASSERT_EQUAL(3, img->channels);
    TEST_ASSERT_NOT_NULL(img->pixels[0]);
    TEST_ASSERT_NOT_NULL(img->pixels[1]);
    TEST_ASSERT_NOT_NULL(img->pixels[2]);
    free_image(img);
}

void test_image_copy(void){
    printf("Testing image copy...\n");
    Image *img = create_image(100, 100, 3);
    TEST_ASSERT_NOT_NULL(img);

    for (int i = 0; i < 100 * 100; i++)
    {
        img->pixels[0][i] = i % 256;
        img->pixels[1][i] = (i + 1) % 256;
        img->pixels[2][i] = (i + 2) % 256;
    }

    Image *copy = copy_image(img);
    TEST_ASSERT_NOT_NULL(copy);

    TEST_ASSERT_EQUAL(img->width, copy->width);
    TEST_ASSERT_EQUAL(img->height, copy->height);
    TEST_ASSERT_EQUAL(img->channels, copy->channels);

    TEST_ASSERT_NOT_NULL(copy->pixels[0]);
    TEST_ASSERT_NOT_NULL(copy->pixels[1]);
    TEST_ASSERT_NOT_NULL(copy->pixels[2]);

    for (int i = 0; i < 100 * 100; i++)
    {
        TEST_ASSERT_EQUAL(img->pixels[0][i], copy->pixels[0][i]);
        TEST_ASSERT_EQUAL(img->pixels[1][i], copy->pixels[1][i]);
        TEST_ASSERT_EQUAL(img->pixels[2][i], copy->pixels[2][i]);
    }

    free_image(copy);
    free_image(img);
}

void test_image_copy_performance(void){
    printf("Testing image copy performance...\n");
    Image *img = create_image(3000, 3000, 3);
    TEST_ASSERT_NOT_NULL(img);

    double total_iops = 0;
    const size_t iop = img->width * img->height * img->channels;
    const int iterations = 200;

    for (int i = 0; i < iterations; i++){
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        
        Image *copy = copy_image(img);
        TEST_ASSERT_NOT_NULL(copy);
        
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        double elapsed = (end.tv_sec - start.tv_sec) +
                         (end.tv_nsec - start.tv_nsec) / 1e9;
        
        total_iops += iop / elapsed;
        
        free_image(copy);
    }
    
    double average_iops = total_iops / (double)iterations;
    double bytes_copied = (double)iop * sizeof(unsigned char);
    double gb_per_copy = bytes_copied / 1e9;
    double average_time = (double)(1.0 / (average_iops / iop));
    double gbps = gb_per_copy / average_time;
    
    printf("\nCopy Performance Test: %zux%zux%zu image -> %.2f MIOPS, %.2f GB/s\n",
           img->width, img->height, img->channels,
           average_iops / 1e6, gbps);
    
    // Basic performance assertion - should be faster than 1 second per copy
    TEST_ASSERT_GREATER_THAN(0.0, average_iops);
    TEST_ASSERT_LESS_THAN(1.0, average_time);
    
    free_image(img);
}
