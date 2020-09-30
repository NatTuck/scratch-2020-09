#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"

set*
empty_set()
{
    return 0;
}

static
set*
cons(char* item, set* xs)
{
    set* ys = calloc(1, sizeof(set));
    ys->head = strdup(item);
    ys->tail = xs;    // taking ownership
    ys->refs = 1;
    return ys;
}

void
add_ref(set* xs)
{
    xs->refs += 1;
}

static
int
streq(const char* aa, const char* bb)
{
    return strcmp(aa, bb) == 0;
}

int
contains(set* xs, char* item)
{
    if (xs == 0) {
        return 0;
    }

    if (streq(item, xs->head)) {
        return 1;
    }

    return contains(xs->tail, item);
}

set*
insert(set* xs, char* item)
{
    if (contains(xs, item)) {
        return xs;
    }
    else {
        return cons(item, xs);
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

void
free_set(set* xs)
{
    if (xs) {
        xs->refs -= 1;
        if (xs->refs == 0) {
            free(xs->head);
            free_set(xs->tail);
            free(xs);
        }
    }
}

set*
union_set(set* xs, set* ys)
{
    if (xs) {
        return insert(union_set(xs->tail, ys), xs->head);
    }
    else {
        add_ref(ys);
        return ys;
    }
}
