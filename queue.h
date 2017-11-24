#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
    uint32_t * heap;
    int size;
} queue_t;

queue_t * new_queue(int);
void insert(queue_t *, uint32_t, uint32_t);
uint32_t remove(queue_t *);

#endif
