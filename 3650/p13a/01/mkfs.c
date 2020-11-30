
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "pages.h"
#include "inode.h"
#include "directory.h"

int
allocate_block()
{
    for (int ii = 1; ii < 256; ++ii) {
        uint8_t* used = pages_get_page(ii);
        if (!*used) {
            *used = 1;
            return ii;
        }
    }

    return -1;
}

int
main(int argc, char* argv[])
{
    assert(argc == 2);
    const char* image_file = argv[1];
    pages_init(image_file);

    // Page 0 is inodes
    inode* nodes = (inode*) pages_get_page(0);

    // Inode 0 is root directory
    inode* root_node = &(nodes[0]);
    root_node->refs = 1;
    root_node->mode = 040755;
    root_node->size = 0;
    int root_data_block = allocate_block();
    root_node->ptrs[0] = root_data_block;

    // Create two initial files
    dirent* dir = (dirent*) pages_get_page(root_data_block);

    dirent* f1 = &(dir[0]);
    strcpy(f1->name, "one.txt");
    f1->inum = 1;
    inode* n1 = &(nodes[f1->inum]);
    n1->refs = 1;
    n1->mode = 010644;
    n1->size = 16;
    n1->ptrs[0] = allocate_block();
    char* b1 = pages_get_page(n1->ptrs[0]);
    strcpy(b1 + 1, "this is file #1");
    
    dirent* f2 = &(dir[1]);
    strcpy(f2->name, "two.txt");
    f2->inum = 2;
    inode* n2 = &(nodes[f2->inum]);
    n2->refs = 1;
    n2->mode = 010644;
    n2->size = 11;
    n2->ptrs[0] = allocate_block();
    char* b2 = pages_get_page(n1->ptrs[0]);
    strcpy(b2 + 1, "other file");

    return 0;
}


