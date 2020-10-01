
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"

set*
empty_set()
{
    return 0;
}

void
free_set(set* xs)
{
    if (xs) {
        if (xs->refs > 1) {
            //printf("dec refs for %s\n", xs->head);
            xs->refs -= 1;
            return;
        }

        free(xs->head);
        free_set(xs->tail);
        free(xs);
    }
}

void
add_ref(set* xs)
{
    //printf("inc refs for %s\n", xs->head);
    xs->refs += 1;
}

set*
cons(const char* item, set* xs)
{
    set* ys = calloc(1, sizeof(set));
    ys->head = strdup(item);
    ys->tail = xs;
    ys->refs = 1;
    return ys;
}

int
streq(const char* aa, const char* bb)
{
    return strcmp(aa, bb) == 0;
}

int
contains(set* xs, const char* item)
{
    for (; xs; xs = xs->tail) {
        if (streq(xs->head, item)) {
            return 1;
        }
    }
    return 0;
}

set*
insert(set* xs, const char* item)
{
    if (contains(xs, item)) {
        return xs;
    }
    else {
        return cons(item, xs);
    }
}

set*
union_set(set* xs, set* ys)
{
    if (xs == 0) {
        add_ref(ys);
        return ys;
    }
    else {
        return insert(union_set(xs->tail, ys), xs->head);
    }
}

void
print_set(set* xs)
{
    for (; xs; xs = xs->tail) {
        printf("%s ", xs->head);
    }
    printf("\n");
}
