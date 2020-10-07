#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "split.h"

char**
split1(const char* text, /*out*/ long* nn)
{
    return split2(text, ' ', nn);
}

void
chomp(char* text)   // aka "trim_right"
{
    // remove a trailing newline
}



char**
split2(const char* text, char sep, /*out*/ long* nn)
{
    *nn = 0;
    long size = strlen(text);

    if (size == 0) {
        return 0;
    }

    // Not zero length, so there's a first item before the first space.
    *nn += 1;

    // First find the number of split points.
    for (long ii = 0; ii < size; ++ii) {
        if (text[ii] == sep) {
            *nn += 1;
        }
    }

    // Second, actually split the string.
    char** ys = calloc(*nn, sizeof(char*));
    long ii = 0; // first position in string
    long kk = 0; // position in output array
    long jj = 0;
    for (; jj < size; ++jj) {
        if (text[jj] == sep) {
            long item_size = jj - ii;
            ys[kk] = calloc(item_size + 1, sizeof(char));
            memcpy(ys[kk], text + ii, item_size);
            // calloc already zeroed the final byte, so we're null terminated

            ii = jj + 1;
            kk += 1;
        }
    }

    // get the last item
    long item_size = jj - ii;
    ys[kk] = calloc(item_size + 1, sizeof(char));
    memcpy(ys[kk], text + ii, item_size);
    // calloc already zeroed the final byte, so we're null terminated
 
    return ys;
}


char**
split3(const char* text, int (*pred)(int), /*out*/ long* nn)
{
    *nn = 0;
    long size = strlen(text);

    if (size == 0) {
        return 0;
    }

    // Not zero length, so there's a first item before the first space.
    *nn += 1;

    // First find the number of split points.
    for (long ii = 0; ii < size; ++ii) {
        if (pred(text[ii])) {
            *nn += 1;
        }
    }

    // Second, actually split the string.
    char** ys = calloc(*nn, sizeof(char*));
    long ii = 0; // first position in string
    long kk = 0; // position in output array
    long jj = 0;
    for (; jj < size; ++jj) {
        if (pred(text[jj])) {
            long item_size = jj - ii;
            ys[kk] = calloc(item_size + 1, sizeof(char));
            memcpy(ys[kk], text + ii, item_size);
            // calloc already zeroed the final byte, so we're null terminated

            ii = jj + 1;
            kk += 1;
        }
    }

    // get the last item
    long item_size = jj - ii;
    ys[kk] = calloc(item_size + 1, sizeof(char));
    memcpy(ys[kk], text + ii, item_size);
    // calloc already zeroed the final byte, so we're null terminated
 
    return ys;
}

char**
split4(const char* text, int (*count)(const char*), /*out*/ long* nn)
{
    *nn = 0;
    long size = strlen(text);

    if (size == 0) {
        return 0;
    }

    // Not zero length, so there's a first item before the first space.
    *nn += 1;

    // First find the number of split points.
    for (long ii = 0; ii < size; ++ii) {
        int mm = count(text + ii);
        if (mm > 0) {
            *nn += 1;
            ii += mm - 1;
        }
    }

    // Second, actually split the string.
    char** ys = calloc(*nn, sizeof(char*));
    long ii = 0; // first position in string
    long kk = 0; // position in output array
    long jj = 0;
    for (; jj < size; ++jj) {
        int mm = count(text + jj);
        if (mm > 0) {
            long item_size = jj - ii;
            ys[kk] = calloc(item_size + 1, sizeof(char));
            memcpy(ys[kk], text + ii, item_size);
            // calloc already zeroed the final byte, so we're null terminated

            jj += mm - 1;

            ii = jj + 1;
            kk += 1;
        }
    }

    // get the last item
    long item_size = jj - ii;
    ys[kk] = calloc(item_size + 1, sizeof(char));
    memcpy(ys[kk], text + ii, item_size);
    // calloc already zeroed the final byte, so we're null terminated
 
    return ys;
}



char*
join2(char sep, char** items, long nn)
{
    // start total length at zero
    long size = 0;
    // loop through array, sum up sizes
    for (long ii = 0; ii < nn; ++ii) {
        size += strlen(items[ii]);
    }
    size += nn - 1; // only put separators between items
    size += 1;      // space for null terminator

    // allocate output string
    char* yy = calloc(size, sizeof(char));

    // loop thorough input and copy to output, put in separators
    long ii = 0; // current item index
    long jj = 0; // current position in output
    for (; ii < nn; ++ii) {
        long item_len = strlen(items[ii]);
        memcpy(yy + jj, items[ii], item_len);
        jj += item_len;
        yy[jj] = sep;
        jj++;
    }
    yy[jj-1] = 0;
    return yy;
}

void
print_items(char** items, long nn)
{
    for (long ii = 0; ii < nn; ++ii) {
        printf(" - [%s]\n", items[ii]);
    }
}

