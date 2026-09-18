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

void convert_to_grayscale(Node *node){
    if (!node || !node->input) return;
    printf("Converting image to grayscale\n");
    const Image *input = node->input;
    printf("Converting to grayscale: %zux%zu, %zu channels\n", input->width, input->height, input->channels);

    //Image est déjà en niveaux de gris
    if (input->channels == 1) {
        node->output = copy_image(input);
        return;
    }
    
    //Image n'est pas en niveaux de gris
    size_t size = input->width * input->height;
    Image *gray = create_image(input->width, input->height, 1);
    if (!gray) {
        printf("Allocation Failed\n");
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

void quantize_image_lut(Node *node){
    if (!node || !node->input) return;
    printf("Quantizing image using LUT method\n");
    const Image *input = node->input;
    printf("Quantizing image: %zux%zu, %zu channels\n", input->width, input->height, input->channels);
    int levels = 16;
    if (node->args) {
        printf("Pipeline requested quantize level: %s\n", node->args);
        levels = atoi(node->args);
        if (levels < 2) levels = 2;
        if (levels > 256) levels = 256;
    } else {
        printf("Pipeline did not specify quantize level, using default 16.\n");
    }
    printf("Actual quantize level used: %d\n", levels);
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

void quantize_image(Node *node)
{
    quantize_image_naive(node);
}

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
    case kSave:
        save_image(node);
        break;
    default:
        fprintf(stderr, "Unknown operation %d for node %zu\n", node->op, node->id);
        exit(EXIT_FAILURE);
        break;
    }
}