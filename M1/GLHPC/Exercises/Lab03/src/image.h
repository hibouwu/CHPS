#ifndef IMAGE_H
#define IMAGE_H
#include <stddef.h>

/**
 * Structure to hold image data.
 * - width: Width of the image.
 * - height: Height of the image.
 * - channels: Number of channels (1 for grayscale, 3 for RGB).
 * - pixels: Array of pointers to pixel data for each channel.
 */
typedef struct {
    unsigned char* pixels[3];
    size_t width;
    size_t height;
    size_t channels; // 1 for grayscale, 3 for RGB
} Image;

Image* create_image(size_t width, size_t height, size_t channels);
Image* copy_image(const Image* image);
void free_image(Image* image);

#endif