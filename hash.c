#include "hash.h"

#include<stdlib.h>
#include<math.h>
#include<string.h>

table_t make_table(uint32_t n_edges)
{
    // Allocate twice the necessary space
    record_t * data = (record_t *) malloc(n_edges * 2 * sizeof(record_t));
    for (int i = 0; i < n_edges * 2; i++)
        data[i].active = false;
    table_t table;
    table.data = data;
    table.size = n_edges * 2;
    
    return table;
}

void insert_hash(table_t table, pair_t record, uint32_t hash)
{
    uint32_t i = 0;
    while (table.data[hash + OFFSET(i)].active)
        i++;
    table.data[hash + OFFSET(i)].value = record;
}

void insert(table_t table, pair_t record)
{
    insert_hash(table, record, record.fst);
    insert_hash(table, record, record.snd);
}


bool exists_hash(table_t table, pair_t record, uint32_t hash)
{
    uint32_t i = 0;
    while(table.data[hash + OFFSET(i)].active)
        i++;
    return memcmp(&table.data[hash + OFFSET(i)].value, &record, sizeof(pair_t));
}
bool exists(table_t table, pair_t record)
{
    return exists_hash(table, record, record.fst) ||
            exists_hash(table, record, record.snd);
}

uint32_t lookup(table_t table, pair_t record, pair_t * locations)
{
    if (exists(table, record))
    {
        pair_t p1 = locations[record.fst];
        pair_t p2 = locations[record.snd];

        uint32_t dx = abs((int)p1.fst - (int)p2.fst);
        uint32_t dy = abs((int)p1.snd - (int)p2.snd);
        // return the L1 distance (faster)
        return dx + dy;
    }
    return -1;
}
