#ifndef IMAGE_H
#define IMAGE_H
#include <stddef.h>

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