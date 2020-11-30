// based on cs3650 starter code

#ifndef DIRECTORY_H
#define DIRECTORY_H

#define DIR_NAME 48

#include "pages.h"
#include "inode.h"

typedef struct dirent {
    char name[DIR_NAME];
    int  inum;
    char _reserved[12];
} dirent;

void directory_init();
int directory_lookup(inode* dd, const char* name);
int tree_lookup(const char* path);
int directory_put(inode* dd, const char* name, int inum);
int directory_delete(inode* dd, const char* name);
void print_directory(inode* dd);

#endif

