#ifndef MAP_H
#define MAP_H

#include<stdio.h>

#include "hash.h"

typedef struct {
    pair_t * positions;
    table_t edges;
} map_t;

map_t * load_map(FILE *);
uint32_t search(map_t *, pair_t);
#endif
