#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static TransformationOp parse_op_name(const char *name)
{
    if (strcmp(name, "load") == 0)
        return kLoad;
    if (strcmp(name, "grayscale") == 0)
        return kGrayscale;
    if (strcmp(name, "invert") == 0)
        return kInvert;
    if (strcmp(name, "quantize") == 0)
        return kQuantize;
    if (strcmp(name, "save") == 0)
        return kSave;
    fprintf(stderr, "Unknown operation: %s\n", name);
    return kUnknownTransformationOp;
}

static void add_node_to_graph(Graph* graph, size_t id, const char* op_name, const char* args, int parent)
{
    if (graph->node_count >= graph->max_nodes)
    {
        graph->max_nodes *= 2;
        graph->nodes = realloc(graph->nodes, sizeof(Node) * graph->max_nodes);
        if (!graph->nodes)
        {
            fprintf(stderr, "Memory allocation failed for nodes\n");
            exit(EXIT_FAILURE);
        }
    }

    Node* node = &graph->nodes[graph->node_count++];
    node->id = id;
    node->op = parse_op_name(op_name);
    if (node->op == kUnknownTransformationOp)
    {
        fprintf(stderr, "Failed to parse operation: %s\n", op_name);
        exit(EXIT_FAILURE);
    }

    size_t len = strlen(args);
    node->args = malloc(len + 1);
    if (!node->args)
    {
        fprintf(stderr, "Memory allocation failed for node args\n");
        exit(EXIT_FAILURE);
    }
    strcpy(node->args, args);


    node->input = NULL;
    node->output = NULL;
    node->parent = parent;
}

static void parse_node(char* line, size_t expected_id, Graph* graph) {
    unsigned int id;
    int parent;
    char op[125], arg[256] = {0};
    int n = sscanf(line, "%d %d %124s %255[^\n]", &id, &parent, op, arg);

    if (n < 3)
    {
        fprintf(stderr, "Invalid line: %s\n", line);
        exit(EXIT_FAILURE);
    }

    if (id != expected_id)
    {
        fprintf(stderr, "Parsed Node with ID {%d}, should be {%zu}.\n"
            "Note that the parser does not support non-sequential IDs.\n", id, expected_id);
        exit(EXIT_FAILURE);
    }

    add_node_to_graph(graph, id, op, arg, parent);
}

static void parse_file(Graph* graph, const char *filename)
{
    if (!graph)
    {
        fprintf(stderr, "Graph is NULL\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Could not open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[1024];
    size_t expected_id = 0;
    while (fgets(line, sizeof(line), file))
    {
        if (line[0] == '#' || strlen(line) < 3)
            continue; // Skip comments and empty lines

        parse_node(line, expected_id, graph);
        expected_id++;
    }
    fclose(file);
}

Graph* init_graph() {
    Graph *graph = malloc(sizeof(Graph));
    if (!graph)
    {
        fprintf(stderr, "Memory allocation failed for Graph\n");
        return NULL;
    }
    graph->node_count = 0;
    
    // We reserve spaces for 10 nodes initially
    graph->max_nodes = 10;
    graph->nodes = malloc(sizeof(Node) * graph->max_nodes);
    if (!graph->nodes)
    {
        fprintf(stderr, "Memory allocation failed for nodes\n");
        free(graph);
        return NULL;
    }

    return graph;
}

Graph *parse_graph(const char *filename)
{
    Graph *res = init_graph();
    parse_file(res, filename);
    return res;
}

void free_node(Node* node) {
    if (node->output)
        free_image(node->output);
    // We shall not free node->input, because it will always point to another node's output
    free(node->args);
}

void free_graph(Graph* graph) {
    for (size_t i = 0; i < graph->node_count; i++)
    {
        free_node(&graph->nodes[i]);
    }

    free(graph->nodes);
    free(graph);
}

// This function will be implemented by the students
// Not the cleanest thing to have it declared like so
// But it allows decoupling of the execution logic
extern void execute_node(Node *node);

int execute_graph(Graph *graph)
{
    bool *done = calloc(graph->node_count, sizeof(bool));

    // Very naive execution strategy:
    // Just bruteforce through all nodes until we find a node we can execute.
    // Stop when no nodes has been executed in the past iteration.
    bool has_changes = true;
    while (has_changes)
    {
        has_changes = false;
        for (size_t i = 0; i < graph->node_count; i++)
        {
            Node *node = &graph->nodes[i];
            if (done[i])
                continue; // Skip already executed nodes

            if (node->parent != -1 && !done[node->parent])
                continue;

            if (node->op != kLoad && node->parent != -1)
                node->input = graph->nodes[node->parent].output; // Set the input to the output of the parent node

            // Else, we found a node that we can execute
            execute_node(node);
            done[i] = true;
            has_changes = true;
        }
    }

    for (int i = 0; i < graph->node_count; i++) {
        if (!done[i]) {
            fprintf(stderr, "Warning: Node %u was not executed (possible cyclic dependency or missing parent)\n", i);
        }
    }

    free(done);
    return 0;
}