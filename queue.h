#ifndef QUEUE_H
#define QUEUE_H

#include "hash.h"

#define SWAP(x,y) do {__typeof__(*(x)) temp; temp = *(x); *(x) = *(y); *(y) = temp;} while(0);
#define PARENT(child) ((uint32_t)((child - 1) / 2))
#define LEFT(parent) ((uint32_t)parent * 2 + 1)
#define RIGHT(parent) ((uint32_t)parent * 2 + 2)

#include<stdint.h>


typedef struct {
    pair_t * heap;
    int size;
    int load;
} queue_t;

queue_t * new_queue(int);
void qadd(queue_t *, pair_t);
uint32_t qremove(queue_t *);

#endif
