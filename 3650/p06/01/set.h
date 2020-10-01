#ifndef SET_H
#define SET_H

// sets are logically immutable
// this allows shared structure

// An empty list is a null pointer.
typedef struct set {
    char* head;         // owned copy
    struct set* tail;   // owned, takes ownership
    int refs;           // how many owning pointers reference this cell
} set;

set* empty_set(); // caller must free result

void free_set(set* xs);
void add_ref(set* xs);

// takes responsibility for xs
// caller must free result
set* insert(set* xs, const char* item);

void print_set(set* xs);

// caller must free result
// does not take responsiblity for either input
set* union_set(set* xs, set* ys);

#endif
