#include "parser.h"
#include "transformation.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <graph_file>\n", argv[0]);
        return 1;
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