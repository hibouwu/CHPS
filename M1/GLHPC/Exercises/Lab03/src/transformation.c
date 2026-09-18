#include "transformation.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// ------------------------------------------------------- DO NOT EDIT BELOW THIS LINE -------------------------------------------------------

// STBI loads image in an interleaved format (RGB or RGBA)
// Or we need to convert it to planar format (R, G, B as separate channels)
static void convert_interleaved_to_planar(const unsigned char *src, unsigned char *dst[3], int width, int height)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = (y * width + x) * 3;
            dst[0][y * width + x] = src[index];     // R
            dst[1][y * width + x] = src[index + 1]; // G
            dst[2][y * width + x] = src[index + 2]; // B
        }
    }
}

// We need to convert planar format (R, G, B as separate channels) to interleaved format (RGB)
// To save the image through stb_image_write
static void convert_planar_to_interleaved(unsigned char *const *src, unsigned char *dst, int width, int height)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = (y * width + x) * 3;
            dst[index] = src[0][y * width + x];     // R
            dst[index + 1] = src[1][y * width + x]; // G
            dst[index + 2] = src[2][y * width + x]; // B
        }
    }
}

void load_image(Node *node)
{
    int width, height, channels;
    unsigned char *data = stbi_load(node->args, &width, &height, &channels, 3);
    if (!data)
    {
        fprintf(stderr, "Failed to load image: %s\n", stbi_failure_reason());
        exit(EXIT_FAILURE);
    }

    channels = (channels == 4) ? 3 : channels; // Convert RGBA to RGB if needed

    node->output = create_image(width, height, channels);
    if (!node->output)
    {
        fprintf(stderr, "Could not allocate image for load\n");
        free(data);
        return;
    }
    convert_interleaved_to_planar(data, node->output->pixels, width, height);
    free(data);
    printf("Loaded image: %s (%dx%d, %d channels)\n", node->args, width, height, channels);
}

void save_image(Node *node)
{
    if (!node->input || !node->input->pixels[0])
    {
        fprintf(stderr, "Node %zu requested to save an image from node %d, which did not produce an image\n", node->id, node->parent);
        return;
    }

    int channels = node->input->channels;
    unsigned char *data = NULL;
    if (channels == 3)
    {
        data = malloc(node->input->width * node->input->height * channels);
        if (!data)
        {
            fprintf(stderr, "Memory allocation failed for saving image\n");
            exit(EXIT_FAILURE);
        }
        convert_planar_to_interleaved(node->input->pixels, data, node->input->width, node->input->height);
    }
    else
    {
        data = node->input->pixels[0]; // For grayscale, we can use the first channel directly
    }

    if (!stbi_write_bmp(node->args, node->input->width, node->input->height, channels, data))
    {
        fprintf(stderr, "Failed to save image\n");
        exit(EXIT_FAILURE);
    }
}

// ------------------------------------------------------- DO NOT EDIT ABOVE THIS LINE -------------------------------------------------------

/**
 * Rotates the input image 90 degrees clockwise.
 * 
 * @param node Pointer to the Node structure containing the input image.
 */
void rotate_image_90_clockwise(Node *node)
{
    int width = node->input->width;
    int height = node->input->height;
    int c = node->input->channels;

    node->output = create_image(height, width, c); // Create an output image with swapped dimensions

    do // For each channel, rotate the image 90 degrees clockwise
    {
        c = c - 1;
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                node->output->pixels[c][x * height + (height - y - 1)] = node->input->pixels[c][y * width + x];
            }
        }
    } while (c > 0); // Corrected loop condition to ensure all channels are processed
}

/**
 * Converts the input image to grayscale.
 * If the input image is already in grayscale, it simply copies the image.
 * 
 * @param node Pointer to the Node structure containing the input image.
 */
void convert_to_grayscale(Node *node){
    if (!node || !node->input) return;
    const Image *input = node->input;

    //Image est déjà en niveaux de gris
    if (input->channels == 1) {
        node->output = copy_image(input);
        return;
    }
    
    //Image n'est pas en niveaux de gris
    size_t size = input->width * input->height;
    Image *gray = create_image(input->width, input->height, 1);
    if (!gray) {
        return;
    };

    // Conversion en niveaux de gris en utilisant la formule
    for (size_t i = 0; i < size; ++i) {
        unsigned char rin = input->pixels[0][i];
        unsigned char gin = input->pixels[1][i];
        unsigned char bin = input->pixels[2][i];
        gray->pixels[0][i] = (unsigned char)(0.299 * rin + 0.587 * gin + 0.114 * bin);
    }
    node->output = gray;
}

/**
 * This function reduces the number of colors in the image by mapping pixel values
 * to the nearest quantization level using a precomputed lookup table (LUT).
 * 
 * @param node Pointer to the Node structure containing the input image and arguments.
 */
void quantize_image_lut(Node *node){
    if (!node || !node->input) return;
    const Image *input = node->input;
    int levels = 16;
    if (node->args) {
        levels = atoi(node->args);
        if (levels < 2) levels = 2;
        if (levels > 256) levels = 256;
    }
    float step = 255.0f / (levels - 1);
    unsigned char LUT[256];
    for (int v = 0; v < 256; ++v) {
        float qf = v / step;
        int quant = step * roundf(qf);
        if (quant > 255) quant = 255;
        LUT[v] = (unsigned char)quant;
    }
    Image *out = create_image(input->width, input->height, input->channels);
    if (!out) return;
    size_t size = input->width * input->height;
    for (size_t c = 0; c < input->channels; ++c) {
        for (size_t i = 0; i < size; ++i) {
            out->pixels[c][i] = LUT[input->pixels[c][i]];
        }
    }
    node->output = out;
}

/**
 * This function reduces the number of colors in the image by mapping pixel values
 * to the nearest quantization level.
 * 
 * @param node Pointer to the Node structure containing the input image and arguments.
 */
void quantize_image_naive(Node *node){
    if (!node || !node->input) return;
    printf("Quantizing image using naive method\n");
    const Image *input = node->input;
    printf("Quantizing image: %zux%zu, %zu channels\n", input->width, input->height, input->channels);
    int levels = 16;
    if (node->args) {
        levels = atoi(node->args);
        if (levels < 2) levels = 2;
        if (levels > 256) levels = 256;
    }
    float step = 255.0f / (levels - 1);
    Image *out = create_image(input->width, input->height, input->channels);
    if (!out) return;
    size_t size = input->width * input->height;
    for (size_t c = 0; c < input->channels; ++c) {
        for (size_t i = 0; i < size; ++i) {
            float v = input->pixels[c][i] / step;
            unsigned char quant = roundf(v) * step;
            out->pixels[c][i] = quant;
        }
    }
    node->output = out;
}

/**
 * Using function quantize_image_lut
 * 
 * @param node Pointer to the Node structure containing the input image and arguments.
 */
void quantize_image(Node *node)
{
    quantize_image_lut(node);
}

/**
 * Inverts the colors of the input image.
 * 
 * @param node Pointer to the Node structure containing the input image.
 */
void invert_image(Node *node){
    if (!node || !node->input) return;
    printf("Inverting image colors\n");
    const Image *input = node->input;
    printf("Inverting image: %zux%zu, %zu channels\n", input->width, input->height, input->channels);
    Image *out = create_image(input->width, input->height, input->channels);
    if (!out) return;
    size_t size = input->width * input->height;
    for (size_t c = 0; c < input->channels; ++c) {
        for (size_t i = 0; i < size; ++i) {
            out->pixels[c][i] = 255 - input->pixels[c][i];
        }
    }
    node->output = out;
}

/**
 * Executes the operation specified in the node.
 * This function is called after ensuring that the node's input is ready.
 * It handles different operations like load, save, grayscale conversion, and more.
 */
void execute_node(Node *node)
{
    switch (node->op)
    {
    case kLoad:
        load_image(node);
        break;
    case kGrayscale:
        convert_to_grayscale(node);
        break;
    case kQuantize:
        quantize_image(node);
        break;
    case kInvert:
        invert_image(node);
        break;
    case kRotate:
        rotate_image_90_clockwise(node);
        break;
    case kSave:
        save_image(node);
        break;
    default:
        fprintf(stderr, "Unknown operation %d for node %zu\n", node->op, node->id);
        exit(EXIT_FAILURE);
        break;
    }
}
