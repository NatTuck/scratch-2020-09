#ifndef SPLIT_H
#define SPLIT_H

char** split1(const char* text, /*out*/ long* nn);
char** split2(const char* text, char sep, /*out*/ long* nn);
char** split3(const char* text, int (*pred)(int), /*out*/ long* nn);
char** split4(const char* text, int (*count)(const char*), /*out*/ long* nn);
char*  join2(char sep, char** text, long nn);
void print_items(char** items, long nn);

#endif
