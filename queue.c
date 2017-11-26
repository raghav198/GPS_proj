#include "queue.h"

#include<stdlib.h>
#include<stdio.h>

void sink(queue_t * q, int size, int root)
{
    pair_t * heap = q->heap;
    pair_t top = heap[root];
    if (LEFT(root) < size && heap[LEFT(root)].snd  < top.snd)
    {
        SWAP(&heap[root], &heap[LEFT(root)]);
        SWAP(&(q->locations[heap[root].fst]), &(q->locations[heap[LEFT(root)].fst]));
        sink(q, size, LEFT(root));
    }
    else if (RIGHT(root) < size && heap[RIGHT(root)].snd < top.snd)
    {
        SWAP(&heap[root], &heap[RIGHT(root)]);
        SWAP(&(q->locations[heap[root].fst]), &(q->locations[heap[RIGHT(root)].fst]));
        sink(q, size, RIGHT(root));
    }

}

void heapify(queue_t * q, int size)
{
    for (int i = size / 2; i >= 0; i--)
        sink(q, size, i);
}

queue_t * new_queue(int size)
{
    queue_t * q = (queue_t *) malloc(sizeof(queue_t));
    q->heap = (pair_t *) malloc(sizeof(pair_t) * size);
    q->locations = (int *) malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
        q->locations[i] = -1;
    q->size = size;
    q->load = 0;

    return q;
}

void qadd(queue_t * q, pair_t element)
{
    if (q->load < q->size)
    {
        q->heap[q->load] = element;
        q->locations[element.fst] = q->load;
        heapify(q, ++q->load);
    }
}


pair_t qremove(queue_t * q)
{
    SWAP(&q->heap[0], &q->heap[q->load - 1]);
    return q->heap[--q->load];
}

#ifdef TEST_QUEUE
int main()
{

    // pair_t heap[10] = {{0, 5}, {1, 1}, {2, 7}, {3, 12}, {4, 6}, {5, 23}, {6, 10}, {7, 8}, {8, 11}, {9, 0}};
    // heapify(heap, 10);
    queue_t * q = new_queue(10);
    
    qadd(q, (pair_t){0, 5});
    qadd(q, (pair_t){1, 1});
    qadd(q, (pair_t){2, 7});
    qadd(q, (pair_t){3, 12});
    qadd(q, (pair_t){4, 6});
    qadd(q, (pair_t){5, 23});
    qadd(q, (pair_t){6, 10});
    qadd(q, (pair_t){7, 8});
    qadd(q, (pair_t){8, 11});
    qadd(q, (pair_t){9, 0});



}
#endif
