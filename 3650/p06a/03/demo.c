
// split: String, Char => Array of String

#include <stdio.h>
#include <alloca.h>
#include <ctype.h>

#include "split.h"

int
count_spaces(const char* text)
{
    int yy = 0;
    while (isspace(text[yy])) {
        ++yy;
    }
    return yy;
}

int
main(int _ac, char* _av[])
{
    char* text1 = "the quick brown fox jumps over the lazy dog";
    long  size1;

    char** words1 = split1(text1, &size1); // initially, separate on space
    //print_items(words1, size1);

    char* text2 = alloca(1024);
    FILE* data1 = fopen("sample.txt", "r");
    long dsz = fread(text2, 1, 1024, data1);
    text2[dsz] = 0;
    fclose(data1);

    long size2;
    char** words2 = split2(text2, '\n', &size2);
    //print_items(words2, size2);

    char* text2a = join2(',', words2, size2);
    //puts(text2a);
 
    char* text3 = alloca(1024);
    FILE* data3 = fopen("sample2.txt", "r");
    long dsz3 = fread(text3, 1, 1024, data3);
    text3[dsz3] = 0;
    fclose(data3);

    long size3;
    char** words3 = split3(text3, isspace, &size3);
    //print_items(words3, size3);
    
    long size4;
    char** words4 = split4(text3, count_spaces, &size4);
    print_items(words4, size4);

    return 0;
}

