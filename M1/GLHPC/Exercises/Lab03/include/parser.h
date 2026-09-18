#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include "image.h"

typedef enum
{
    kUnknownTransformationOp = -1,
    kGrayscale,
    kQuantize,
    kInvert,
    kSave,
    kLoad,
    kRotate,
} TransformationOp;

typedef struct
{
    TransformationOp op;
    size_t id;
    int parent; // Parent node ID, -1 if no parent
    char *args;
    const Image *input;
    Image *output;
} Node;

// We consider that nodes are owners of their output images,
// so we need to free them when the node is freed
void free_node(Node *node);

typedef struct
{
    Node *nodes;
    size_t node_count;
    size_t max_nodes;
} Graph;

Graph *parse_graph(const char *filename);
void free_graph(Graph *graph);

int execute_graph(Graph *graph);

#endif // PARSER_H