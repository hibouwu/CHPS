#define _GNU_SOURCE

#include "parser.h"
#include "transformation.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

void check_grayscale()
{
    Image *img = create_image(100, 100, 1);
    if (!img)
    {
        fprintf(stderr, "Allocation Test: Failed to create image\n");
        exit(1);
    }

    if (img->width != 100 || img->height != 100 || img->channels != 1)
    {
        fprintf(stderr, "Allocation Test: Grayscale Image dimensions or channels do not match expected values\n");
        exit(1);
    }

    if (img->pixels[0] == NULL)
    {
        fprintf(stderr, "Allocation Test: Pixel data is NULL\n");
        exit(1);
    }

    if (img->pixels[1] != NULL || img->pixels[2] != NULL)
    {
        fprintf(stderr, "Allocation Test: Unexpected RGB channels present in grayscale image\n");
        exit(1);
    }
    free_image(img);
}

void check_rgb()
{
    Image *img = create_image(100, 100, 3);
    if (!img)
    {
        fprintf(stderr, "Allocation Test: Failed to create image\n");
        exit(1);
    }

    if (img->width != 100 || img->height != 100 || img->channels != 3)
    {
        fprintf(stderr, "Allocation Test: RGB Image dimensions or channels do not match expected values\n");
        exit(1);
    }

    if (img->pixels[0] == NULL || img->pixels[1] == NULL || img->pixels[2] == NULL)
    {
        fprintf(stderr, "Allocation Test: Pixel data for RGB channels is NULL\n");
        exit(1);
    }
    free_image(img);
}

void check_copy()
{
    Image *img = create_image(100, 100, 3);
    for (int i = 0; i < 100 * 100; i++)
    {
        img->pixels[0][i] = i % 256; // Fill with some data
        img->pixels[1][i] = (i + 1) % 256;
        img->pixels[2][i] = (i + 2) % 256;
    }
    Image *copy = copy_image(img);

    if (!copy)
    {
        fprintf(stderr, "Copy Test: Failed to copy image\n");
        exit(1);
    }

    if (copy->width != img->width || copy->height != img->height || copy->channels != img->channels)
    {
        fprintf(stderr, "Copy Test: Dimensions or channels do not match original image\n");
        exit(1);
    }

    if (copy->pixels[0] == NULL || copy->pixels[1] == NULL || copy->pixels[2] == NULL)
    {
        fprintf(stderr, "Copy Test: Pixel data for RGB channels is NULL in copied image\n");
        exit(1);
    }
    for (int i = 0; i < 100 * 100; i++)
    {
        if (copy->pixels[0][i] != img->pixels[0][i] ||
            copy->pixels[1][i] != img->pixels[1][i] ||
            copy->pixels[2][i] != img->pixels[2][i])
        {
            fprintf(stderr, "Copy Test: Pixel data does not match original image\n");
            exit(1);
        }
    }

    free_image(copy);
    free_image(img);

    img = create_image(3000, 3000, 3);

    double total_iops = 0;
    const size_t iop = img->width * img->height * img->channels;

    for (int i = 0; i < 200; i++)
    {
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);

        Image *copy = copy_image(img);
        


        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        double elapsed = (end.tv_sec - start.tv_sec) +
                         (end.tv_nsec - start.tv_nsec) / 1e9;

        total_iops += iop / elapsed;

        free_image(copy);
    }

    double average_iops = total_iops / 200.0;
    double bytes_copied = (double)iop * sizeof(unsigned char);
    double gb_per_copy = bytes_copied / 1e9;
    double average_time = (double)(1.0 / (average_iops / iop));
    double gbps = gb_per_copy / average_time;

    printf("Copy Test: %zux%zux%zu image -> %.2f MIOPS, %.2f GB/s\n",
        img->width, img->height, img->channels,
        average_iops / 1e6, gbps);
    free_image(img);
}

void memory_check()
{
    check_grayscale();
    check_rgb();
    printf("Memory Allocations tests completed successfully.\n");

    check_copy();
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s --memory-check | <graph_file>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "--memory-check") == 0)
    {
        memory_check();
        return 0;
    }

    Graph *graph = parse_graph(argv[1]);
    if (!graph)
    {
        fprintf(stderr, "Failed to parse graph from file: %s\n", argv[1]);
        return 1;
    }
    int result = execute_graph(graph);

    free_graph(graph);

    if (result != 0)
    {
        fprintf(stderr, "Graph execution failed with error code: %d\n", result);
        return result;
    }

    return result;
}