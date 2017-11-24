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
        fscanf(fp, "%d %d", &map->positions[i].fst, &map->positions[i].snd);

    for (int i = 0; i < n_edges; i++)
    {
        pair_t pair;
        fscanf(fp, "%d %d", &pair.fst, &pair.snd);
        insert(map->edges, pair);
    }

    return map;
}

int main()
{
    // test load_map
    FILE * fp = fopen("map5x5.txt", "r");
    map_t * map = load_map(fp);

    return 0;
}
