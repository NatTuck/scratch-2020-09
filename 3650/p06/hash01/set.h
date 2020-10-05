#ifndef SET_H
#define SET_H

// sets are logically immutable
// this allows shared structure

// Collisions:
//  - None allowed, always grow to avoid.
//  - This is a bad strategy.
typedef struct set {
    char** data;        // array of Maybe[String]
    long size;          // number of items in set
    long capa;          // number of slots in array
} set;

set* empty_set(); // caller must free result

void free_set(set* xs);
//void add_ref(set* xs);

// Makes an owned copy of item
// Mutates the set xs
void insert(set* xs, const char* item);

void print_set(set* xs);

// caller must free result
// does not take responsiblity for either input
set* union_set(set* xs, set* ys);

#endif
