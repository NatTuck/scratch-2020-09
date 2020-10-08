
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "split.h"

char*
read_file(const char* path)
{
    char* temp = malloc(1024);

    FILE* fh = fopen(path, "r");
    long len = fread(temp, 1, 1023, fh);
    fclose(fh);
    temp[len] = 0;

    char* yy = strdup(temp);
    free(temp);
    return yy;
}

long
count_spaces(const char* text)
    // how many spaces appear at the start of the string?
{
    long yy = 0;
    while (text[yy] && isspace(text[yy])) {
        yy++;
    }
    return yy;
}

int
main(int _ac, char* _av[])
{
    puts("\n== words0:");
    long size0;
    char** words0 = split1("", &size0);
    print_items(words0, size0);
    free_items(words0, size0);

    puts("\n== words1:");
    char* msg1 = "the quick brown fox jumps over the lazy dog";
    long size1;
    char** words1 = split1(msg1, &size1); // split into an array of words, so split on ' ' 
    print_items(words1, size1);
    free_items(words1, size1);

    puts("\n== words2:");
    char* text2 = read_file("words.txt");
    long size2;
    char** words2 = split2('\n', text2, &size2);
    print_items(words2, size2);
    free_items(words2, size2);

    puts("\n== words3:");
    char* text3 = read_file("words2.txt");
    long size3;
    char** words3 = split3(isspace, text3, &size3);
    print_items(words3, size3);
    free_items(words3, size3);
    
    puts("\n== words4:");
    long size4;
    char** words4 = split4(count_spaces, text3, &size4);
    print_items(words4, size4);
    free_items(words4, size4);

    return 0;
}
