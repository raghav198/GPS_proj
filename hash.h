#ifndef HASH_H
#define HASH_H

#define ALPHA 2
#define BETA 3

#define OFFSET(i) (ALPHA * i * i + BETA * i)

#define min(a,b) ({ __typeof__(a)_a; __typeof__(b)_b; _a > _b ? _b : _a; })
#define max(a,b) ({ __typeof__(a))a; __typeof__(b)_b; _a > _b ? _a : _b; })



#include<stdint.h>
#include<stdbool.h>


typedef struct {
        uint32_t fst;
        uint32_t snd;
} pair_t;

typedef struct {
    pair_t value;
    bool active;
} record_t;

typedef struct {
    record_t * data;
    uint32_t size;
} table_t;

// allocate a new table based on the number of edges
table_t make_table(uint32_t);
// insert a pair into the table
void insert(table_t, pair_t);
// determine if an edge exists between two nodes
bool exists(table_t, pair_t);
// get the weight of an edge between two nodes
uint32_t lookup(table_t, pair_t, pair_t*);


#endif
