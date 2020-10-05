#ifndef SET_H
#define SET_H

// Collisions aren't allowed.
// If we would have a collision, we grow the table.
//  - Each growth gives a 50% chance of making space
//    for the new item.
//  - If the hashes are actually equal, we'll run out
//    of RAM and crash.
typedef struct set {
  char** data;
  long   size;
  long   capa;
} set;

set* empty_set();
void insert(set* xs, char* item);
void print_set(set* xs);
//void add_ref(set* xs);
void free_set(set* xs);
set* union_set(set* xs, set* ys);

#endif
