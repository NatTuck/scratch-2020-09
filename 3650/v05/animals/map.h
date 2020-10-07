#ifndef MAP_H
#define MAP_H

typedef struct pair {
    char* key;
    char* val;
    struct pair* next;
} pair;

typedef struct map {
    pair** data;    // array of list of pair
    long   size;
    long   capacity;
} map;

typedef struct map_it {
    // these are unowned references
    map* mm;
    long ii;
    pair* item;
} map_it;

map* make_map();
void free_map(map* mm);

// makes an owned copy of key and val
void map_put(map* mm, const char* key, const char* val);

// returns an unowned reference to our copy of the value
char* map_get(map* mm, const char* key);
void map_del(map* mm, const char* key);

map_it iterate(map* mm);
int    has_next(map_it it);
map_it next(map_it it);

#endif
