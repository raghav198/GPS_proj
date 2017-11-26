#include "map.h"
#include<stdlib.h>


int compair(const void * a, const void * b)
{
    pair_t pair1 = *(pair_t*)a;
    pair_t pair2 = *(pair_t*)b;

    if (pair1.fst == pair2.fst)
        return pair1.snd - pair2.snd;
    return pair1.fst - pair2.fst;
}

map_t * load_map(FILE * fp)
{
    int n_nodes, n_edges;
    map_t * map = (map_t *) malloc(sizeof(map_t));
    fscanf(fp, "%d %d", &n_nodes, &n_edges);

    map->positions = (pair_t *)malloc(sizeof(pair_t) * n_nodes);
    map->edges = (pair_t *)malloc(sizeof(pair_t) * n_edges * 2);

    map->n_nodes = n_nodes;
    map->n_edges = n_edges;

    for (int i = 0; i < n_nodes; i++)
    {
        int n, x, y;
        fscanf(fp, "%d %d %d", &n, &x, &y);
        map->positions[i].fst = x;
        map->positions[i].snd = y;
    }
    for (int i = 0; i < n_edges; i++)
    {
        pair_t pair;
        int f, s;
        fscanf(fp, "%d %d", &f, &s);
        pair.fst = f;
        pair.snd = s;
        map->edges[2 * i] = pair;
        pair.snd = f;
        pair.fst = s;
        map->edges[2 * i + 1] = pair;
    }

    qsort(map->edges, map->n_edges * 2, sizeof(pair_t), &compair);

    return map;
}

int binsearch(pair_t * edges, uint32_t target, int start, int stop)
{
    if (stop < start) return -1;
    int mid = start + (stop - start) / 2;
    if (edges[mid].fst == target)
    {
        while(mid > 0 && edges[mid - 1].fst == target) mid--;
        return mid;
    }

    if (target < edges[mid].fst)
        return binsearch(edges, target, start, mid);
    else if (target > edges[mid].fst)
        return binsearch(edges, target, mid, stop);

    return -1;
}


/*int edge_exists(map_t * map, pair_t edge)
{
    pair_t reverse = (pair_t){edge.snd, edge.fst};
    return binsearch(map->edges, edge.fst, 0, map->n_edges - 1);
}*/



uint32_t search(map_t * map, pair_t stops)
{

    uint32_t * paths = (uint32_t *)malloc(sizeof(uint32_t) * map->n_nodes);

    uint32_t start = stops.fst;
    uint32_t stop = stops.snd;
    queue_t * open_nodes = new_queue(map->n_nodes);
    qadd(open_nodes, (pair_t){start, 0});
    while(open_nodes->locations[stop] == -1 && open_nodes->load < open_nodes->size)
    {
        pair_t cur_node = qremove(open_nodes);
        uint32_t closest = cur_node.fst;
        uint32_t dist = cur_node.snd;

        int loc = binsearch(map->edges, closest, 0, map->n_edges * 2 - 1);
        if (loc == -1) continue;

        pair_t edge;
        while((edge = map->edges[loc++]).fst == closest)
        {


            pair_t cur_pos = map->positions[edge.fst];
            pair_t nbr_pos = map->positions[edge.snd];

            uint32_t dx = abs((int)cur_pos.fst - (int)nbr_pos.fst);
            uint32_t dy = abs((int)cur_pos.snd - (int)nbr_pos.snd);
            if (open_nodes->locations[edge.snd] == -1)
            {
                qadd(open_nodes, (pair_t){edge.snd, dx + dy + dist});
                paths[edge.snd] = edge.fst;
            }
            else if (dx + dy + dist < open_nodes->heap[open_nodes->locations[edge.snd]].snd)
            {
                open_nodes->heap[open_nodes->locations[edge.snd]].snd = dx + dy + dist;
                heapify(open_nodes, open_nodes->load);
                paths[edge.snd] = edge.fst;
            }
        }

        // qadd(open_nodes, cur_node);
        
    }   
    if (open_nodes->locations[stop] == -1) return -1;


    //for (uint32_t back = stop; back != start; back = paths[back])
    //    printf("%ud ", back);
    //printf("\n");
    return open_nodes->heap[open_nodes->locations[stop]].snd;


}

#ifdef TEST_MAP
int main()
{
    // test load_map
    FILE * fp = fopen("sample/map5x5.txt", "r");
    map_t * map = load_map(fp);
    printf("Loaded map at %p\n", (void*)map);

    printf("%d\n", search(map, (pair_t){6, 23}));

    return 0;
}
#endif
