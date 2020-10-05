#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"

set*
empty_set()
{
    set* aa = calloc(1, sizeof(set));
    aa->size = 0;
    aa->capa = 4;
    aa->data = calloc(aa->capa, sizeof(char*));
    return aa;
}

static
int
streq(const char* aa, const char* bb)
{
    return strcmp(aa, bb) == 0;
}

static
long
hash(const char* item)
{
    long yy = 0;
    for (; *item; ++item) {
        yy = (yy * 67) + *item;
    }
    return yy;
}

int
contains(set* xs, char* item)
{
    long ii = hash(item) % xs->capa;
    return (xs->data[ii] != 0) && streq(xs->data[ii], item);
}

void
grow_table(set* aa)
{
    char** old_data = aa->data;
    long   old_capa = aa->capa;

    aa->capa *= 2;
    aa->data = calloc(aa->capa, sizeof(char*));

    for (long ii = 0; ii < old_capa; ++ii) {
        if (old_data[ii]) {
            insert(aa, old_data[ii]);
            free(old_data[ii]);
        }
    }

    free(old_data);
}

void
insert(set* xs, char* item)
{
    long ii = hash(item) % xs->capa;
    if (xs->data[ii]) {
        if (streq(xs->data[ii], item)) {
            return;
        }

        grow_table(xs);
        insert(xs, item);
    }
    else {
        xs->size += 1;
        xs->data[ii] = strdup(item);
    }
}

void
print_set(set* xs)
{
    for (long ii = 0; ii < xs->capa; ++ii) {
        if (xs->data[ii]) {
            printf("%s ", xs->data[ii]);
        }
    }
    printf("\n");
}

void
free_set(set* xs)
{
    for (long ii = 0; ii < xs->capa; ++ii) {
        free(xs->data[ii]);  // free can handle nulls
    }
    free(xs->data);
    free(xs);
}

set*
union_set(set* aa, set* bb)
{
    set* cc = empty_set();
    for (long ii = 0; ii < aa->capa; ++ii) {
        if (aa->data[ii] && !contains(cc, aa->data[ii])) {
            insert(cc, aa->data[ii]);
        }
    }
    for (long ii = 0; ii < bb->capa; ++ii) {
        if (bb->data[ii] && !contains(cc, bb->data[ii])) {
            insert(cc, bb->data[ii]);
        }
    }
    return cc;
}
