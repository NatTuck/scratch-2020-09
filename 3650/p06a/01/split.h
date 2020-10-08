#ifndef SPLIT_H
#define SPLIT_H

char** split1(const char* text, /*out*/ long* nn);
char** split2(char sep, const char* text, /*out*/ long* nn);
char** split3(int (*pred)(int), const char* text, /*out*/ long* nn);
char** split4(long (*count)(const char*), const char* text, /*out*/ long* nn);
void print_items(char** items, long nn);
void free_items(char** items, long nn);

#endif
