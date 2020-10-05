
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

void
free_set(set* aa)
{
    for (long ii = 0; ii < aa->capa; ++ii) {
        free(aa->data[ii]); // free is guaranteed to not break on null
    } 
    free(aa->data);
    free(aa);
}

int
streq(const char* aa, const char* bb)
{
    return strcmp(aa, bb) == 0;
}

long
hash(const char* item)
{
    long yy = 0;
    for (; *item; ++item) {
        yy += *item + 67 * yy;
    }
    return yy;
}

int
contains(set* aa, const char* item)
{
    long ii = hash(item) % aa->capa;
    return (aa->data[ii] != 0) && streq(aa->data[ii], item);
}

void
grow_table(set* aa)
{
    char** old_data = aa->data;
    long   old_capa = aa->capa;

    aa->capa = aa->capa * 2;
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
insert(set* aa, const char* item)
{
    long ii = hash(item) % aa->capa;
    if (aa->data[ii]) {
        if (streq(aa->data[ii], item)) {
            return;
        }

        // Now we have a collison, must grow.
        grow_table(aa);
        // That had a 50/50 chance of avoiding
        // the collision. 

        // This doesn't actually work, if we have
        // a complete hash collision it'll recurse
        // forever.
        insert(aa, item);
    }
    else {
        // Maximum load factor
        // - Linear probing = 0.5
        //
        // Here we (maybe?) don't need to worry
        // about load factor, because there's no scanning
        // step.
        // Can't get over 1.0 anyway.

        aa->size++;
        aa->data[ii] = strdup(item);
    }
}

set*
union_set(set* aa, set* bb)
{
    set* cc = empty_set();
    for (long ii = 0; ii < aa->capa; ++ii) {
        if (aa->data[ii]) {
            insert(cc, aa->data[ii]);
        }
    }
    for (long ii = 0; ii < bb->capa; ++ii) {
        if (bb->data[ii]) {
            insert(cc, bb->data[ii]);
        }
    }
    return cc;
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
