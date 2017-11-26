#include "map.h"

#include<stdlib.h>


map_t * load_map(FILE * fp)
{
    int n_nodes, n_edges;
    map_t * map = (map_t *) malloc(sizeof(map_t));
    fscanf(fp, "%d %d", &n_nodes, &n_edges);

    map->positions = (pair_t *)malloc(sizeof(pair_t) * n_edges);
    map->edges = make_table(n_nodes);

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
        fscanf(fp, "%ud %ud", &pair.fst, &pair.snd);
        insert(map->edges, pair);
    }

    return map;
}

uint32_t search(map_t * map, pair_t stops)
{
    uint32_t start = stops.fst;
    uint32_t stop = stops.snd;
    queue_t * open_nodes = new_queue(map->n_nodes);
    qadd(open_nodes, (pair_t){start, 0});
    while(open_nodes->locations[stop] == -1)
    {
        //uint32_t closest = qremove(open_nodes);
        
    }   
    return 12;
}

#ifdef TEST_MAP
int main()
{
    // test load_map
    FILE * fp = fopen("sample/map5x5.txt", "r");
    map_t * map = load_map(fp);
    printf("Loaded map at %p\n", (void*)map);
    return 0;
}
#endif
