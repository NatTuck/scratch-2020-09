#ifndef SET_H
#define SET_H

// An empty set is represetented by the null pointer.
typedef struct set {
    char* head;          // a list cell owns its copy of the string
    struct set* tail;    // a list cell owns its tail
                         // this ends up being a complication
    int refs;            // how many pointers reference this object
} set;

set* empty_set();
set* insert(set* xs, char* item);
void print_set(set* xs);
void add_ref(set* xs);
void free_set(set* xs);
set* union_set(set* xs, set* ys);

#endif
