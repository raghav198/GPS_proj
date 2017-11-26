#ifndef MAP_H
#define MAP_H

#include<stdio.h>
#include<stdbool.h>

#include "queue.h"

typedef struct {
    pair_t * positions;
    pair_t * edges;
    table_t edgesTable;
    uint32_t n_nodes;
    uint32_t n_edges;
} map_t;

map_t * load_map(FILE *);
uint32_t search(map_t *, pair_t);

int edge_exists(map_t *, pair_t);

#endif
