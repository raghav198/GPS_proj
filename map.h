#ifndef MAP_H
#define MAP_H

#include<stdio.h>

#include "queue.h"

typedef struct {
    pair_t * positions;
    table_t edges;
    uint32_t n_nodes;
    uint32_t n_edges;
} map_t;

map_t * load_map(FILE *);
uint32_t search(map_t *, pair_t);
#endif
