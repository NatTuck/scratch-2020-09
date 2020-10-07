#ifndef LIST_H
#define LIST_H

// An empty list is a null pointer.
typedef struct list {
    char* head;   // owned copy
    struct list* tail;  // takes ownership
} list;

list* cons(char* xx, list* xs);
void free_list(list* xs);
void print_list(list* xs);
long length(list* xs);
list* reverse(list* xs);
list* rev_free(list* xs);

#endif
