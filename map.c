#include "map.h"

#include<stdlib.h>


map_t * load_map(FILE * fp)
{
    int n_nodes, n_edges;
    map_t * map = (map_t *) malloc(sizeof(map_t));
    fscanf(fp, "%d %d", &n_nodes, &n_edges);

    map->positions = (pair_t *)malloc(sizeof(pair_t) * n_edges);
    map->edges = make_table(n_nodes);
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

int main()
{
    // test load_map
    FILE * fp = fopen("sample/map5x5.txt", "r");
    map_t * map = load_map(fp);
    printf("Loaded map at %p\n", (void*)map);
    return 0;
}
