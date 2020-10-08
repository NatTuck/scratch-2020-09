
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "split.h"

char**
split1(const char* text, /*out*/ long* nn)
{
    return split2(' ', text, nn);
}

char**
split2(char sep, const char* text, /*out*/ long* nn)
{
    if (text[0] == 0) {
        *nn = 0;
        return 0;
    }

    long spaces = 0;
    for (long ii = 0; text[ii]; ++ii) {
        if (text[ii] == sep) {
            spaces += 1;
        }
    }

    *nn = spaces + 1;
    char** ys = calloc(spaces + 1, sizeof(char*));
    
    long kk = 0; // Which word are we outputing to.

    // loop through string
    for (long ii = 0; text[ii]; ++ii) {
        //  - if we have a space, move on to next word
        if (text[ii] == sep) {
            kk += 1;
        }
        //  - if we have a non-space, add it to current word
        else {
            long jj = ii;
            for (; text[jj] && text[jj] != sep; ++jj);
            long wsize = jj - ii;
            ys[kk] = calloc(wsize + 1, sizeof(char));
            memcpy(ys[kk], text + ii, wsize);
            ys[kk][wsize] = 0;

            while (text[ii] && text[ii] != sep) {
                ii++;
            }
            ii--;
        }
    }

    //  - if we hit the end of input, we return the array
    if (ys[kk] == 0) {
        ys[kk] = strdup("");
    }
    return ys;
}

char**
split3(int (*pred)(int), const char* text, /*out*/ long* nn)
{
    if (text[0] == 0) {
        *nn = 0;
        return 0;
    }

    long spaces = 0;
    for (long ii = 0; text[ii]; ++ii) {
        if (pred(text[ii])) {
            spaces += 1;
        }
    }

    *nn = spaces + 1;
    char** ys = calloc(spaces + 1, sizeof(char*));
    
    long kk = 0; // Which word are we outputing to.

    // loop through string
    for (long ii = 0; text[ii]; ++ii) {
        //  - if we have a space, move on to next word
        if (pred(text[ii])) {
            kk += 1;
        }
        //  - if we have a non-space, add it to current word
        else {
            long jj = ii;
            for (; text[jj] && !pred(text[jj]); ++jj);
            long wsize = jj - ii;
            ys[kk] = calloc(wsize + 1, sizeof(char));
            memcpy(ys[kk], text + ii, wsize);
            ys[kk][wsize] = 0;

            while (text[ii] && !pred(text[ii])) {
                ii++;
            }
            ii--;
        }
    }

    //  - if we hit the end of input, we return the array
    for (long kk = 0; kk < *nn; ++kk) {
        if (!ys[kk]) {
            ys[kk] = strdup("");
        }
    }
    return ys;
}


char**
split4(long (*count)(const char*), const char* text, /*out*/ long* nn)
{
    if (text[0] == 0) {
        *nn = 0;
        return 0;
    }

    long spaces = 0;
    for (long ii = 0; text[ii]; ++ii) {
        long cc = count(&(text[ii]));
        if (cc > 0) {
            spaces += 1;
            ii += cc - 1;
        }
    }

    *nn = spaces + 1;
    char** ys = calloc(spaces + 1, sizeof(char*));
    
    long kk = 0; // Which word are we outputing to.

    // loop through string
    for (long ii = 0; text[ii]; ++ii) {
        //  - if we have a space, move on to next word
        long cc = count(text+ii);
        if (cc > 0) {
            kk += 1;
            ii += cc - 1;
        }
        //  - if we have a non-space, add it to current word
        else {
            long jj = ii;
            for (; text[jj] && !count(&(text[jj])); ++jj);
            long wsize = jj - ii;
            ys[kk] = calloc(wsize + 1, sizeof(char));
            memcpy(ys[kk], text + ii, wsize);
            ys[kk][wsize] = 0;

            while (text[ii] && !count(&(text[ii]))) {
                ii++;
            }
            ii--;
        }
    }

    //  - if we hit the end of input, we return the array
    for (long kk = 0; kk < *nn; ++kk) {
        if (!ys[kk]) {
            ys[kk] = strdup("");
        }
    }
    return ys;
}

void
print_items(char** items, long nn)
{
    for (long ii = 0; ii < nn; ++ii) {
        printf(" - [%s]\n", items[ii]);
    }
}

void 
free_items(char** items, long nn)
{
    for (long ii = 0; ii < nn; ++ii) {
        free(items[ii]);
    }
    free(items);
}

