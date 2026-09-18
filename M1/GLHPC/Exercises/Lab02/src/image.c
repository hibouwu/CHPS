#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Crée une nouvelle image avec les dimensions et le nombre de canaux spécifiés.
 * Alloue de la mémoire pour les pixels de l'image.
 * @param width Largeur de l'image.
 * @param height Hauteur de l'image.
 * @param channels Nombre de canaux (1 pour niveaux de gris, 3 pour RGB).
 * @return Pointeur vers la nouvelle image créée.
 */
Image* create_image(size_t width, size_t height, size_t channels) {
    if (channels != 1 && channels != 3) {
        perror("Channels must be 1 (grayscale) or 3 (RGB)");
        exit(EXIT_FAILURE);
    }

    Image* img = (Image*)malloc(sizeof(Image));

    if (!img) {
        perror("Failed to allocate memory for Image");
        exit(EXIT_FAILURE);
    };

    img->width = width;
    img->height = height;
    img->channels = channels;

    // Allouer de la mémoire pour chaque canal
    for (size_t c = 0; c < channels; c++) {
        img->pixels[c] = (unsigned char*)malloc(width * height * sizeof(unsigned char));
        if (!img->pixels[c]) {
            perror("Failed to allocate memory for image pixels");
            exit(EXIT_FAILURE);
        }
    }
    return img;
}
/**
 * Crée une copie de l'image donnée.
 * @param image Pointeur vers l'image à copier.
 * @return Pointeur vers la nouvelle image copiée.
 */
Image* copy_image(const Image* image) {
    if (!image) {
        perror("Cannot copy a NULL image");
        exit(EXIT_FAILURE);
    };
    Image* copy = create_image(image->width, image->height, image->channels);
    if (!copy)
    {
        perror("Failed to allocate memory for image copy");
        exit(EXIT_FAILURE);
    };

    
    // Implémenter 3 boucles : 1 pour chaque channel, 2 pour width et 3 pour height.
    // Ordre 1 : channel -> height -> width
    /*
    for (size_t c = 0; c < image->channels; c++) {
        for (size_t y = 0; y < image->height; y++) {
            for (size_t x = 0; x < image->width; x++) {
                size_t idx = y * image->width + x;
                copy->pixels[c][idx] = image->pixels[c][idx];
            }
        }
    }
    */

    // Ordre 2 : height -> width -> channel
    /*
    for (size_t y = 0; y < image->height; y++) {
        for (size_t x = 0; x < image->width; x++) {
            size_t idx = y * image->width + x;
            for (size_t c = 0; c < image->channels; c++) {
                copy->pixels[c][idx] = image->pixels[c][idx];
            }
        }
    }
    */

    /*
    // Ordre 3 : width -> channel -> height
    for (size_t x = 0; x < image->width; x++) {
        for (size_t c = 0; c < image->channels; c++) {
            for (size_t y = 0; y < image->height; y++) {
                size_t idx = y * image->width + x;
                copy->pixels[c][idx] = image->pixels[c][idx];
            }
        }
    }
    */

    
    // Implémenter deux boucles : la boucle supérieure itère sur les channels, la boucle intérieure sur chaque pixel.
    size_t size = image->width * image->height;
    for (size_t c = 0; c < image->channels; c++) {
        for (size_t i = 0; i < size; i++) {
            copy->pixels[c][i] = image->pixels[c][i];
        }
    }

    /*
    // Implémenter une boucle : itérer uniquement sur les pixels, copier RGB dans une seule boucle.
    size_t size = image->channels * image->width * image->height;
    for (size_t i = 0; i < size; i++) {
        size_t c = i / (image->width * image->height);
        size_t idx = i % (image->width * image->height);
        copy->pixels[c][idx] = image->pixels[c][idx];
    }
    */

    // 1 boucle : moins de boucles mais plus de calculs, il faut calculer c et idx à chaque itération
    // 2 boucles : nombre moyen de boucles et de calculs, cela devrait être le plus rapide
    // 3 boucles : plus de boucles mais moins de calculs
    //          Ordre 1 : channel -> height -> width, la mémoire est continue par channel, donc il ne faut pas sauter de mémoire, il vaut mieux faire channel en premier
    //          Ordre 2 : height -> width -> channel
    //          Ordre 3 : width -> channel -> height

    return copy;
}

/**
 * Libère la mémoire allouée pour l'image.
 * @param image Pointeur vers l'image à libérer.
 */
void free_image(Image* image)
{
    if (!image) return;
    for (size_t c = 0; c < image->channels; c++) {
        free(image->pixels[c]);
    }
    free(image);
}