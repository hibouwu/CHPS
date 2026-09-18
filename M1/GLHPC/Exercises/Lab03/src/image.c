#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Creates an empty image with width, height, and number of channels.
 * 
 * @param width Width of the image.
 * @param height Height of the image.
 * @param channels Number of channels (1 for grayscale, 3 for RGB).
 * @return Pointer to the created Image structure.
 */
Image* create_image(size_t width, size_t height, size_t channels) {
    Image* image = malloc(sizeof(Image));
    if (!image) {
        fprintf(stderr, "Memory allocation failed for Image\n");
        exit(EXIT_FAILURE);
    }
    image->width = width;
    image->height = height;
    image->channels = channels;

    for (size_t i = 0; i < channels; i++)
    {
        image->pixels[i] = malloc(width * height * sizeof(unsigned char));
        if (!image->pixels[i]){
            fprintf(stderr, "Memory allocation failed for pixel channel %zu\n", i);
            exit(EXIT_FAILURE);
        }
    }
    return image;
}

/**
 * Creates a copy of the given image.
 * 
 * @param image Pointer to the Image structure to be copied.
 * @return Pointer to the newly created copy of the Image structure.
 */
Image* copy_image(const Image* image) {
    Image* res = create_image(image->width, image->height, image->channels);
    for (size_t i = 0; i < image->channels; i++)
    {
        memcpy(res->pixels[i], image->pixels[i], image->width * image->height * sizeof(unsigned char));
    }
    return res;
}

/**
 * Frees the memory allocated for the given image.
 * 
 * @param image Pointer to the Image structure to be freed.
 */
void free_image(Image* image)
{
    if (!image)
        return;
    for (size_t i = 0; i < image->channels; i++)
    {
        free(image->pixels[i]);
    }
    free(image);
}