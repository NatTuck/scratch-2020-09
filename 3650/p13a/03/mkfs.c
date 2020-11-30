
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "pages.h"
#include "directory.h"
#include "inode.h"

int
alloc_data_block()
{
    for (int ii = 1; ii < 256; ++ii) {
        uint8_t* data = pages_get_page(ii);
        if (*data == 0) {
            *data = 1;
            return ii;
        }
    }
    return -1;
}

int
main(int argc, char* argv[])
{
    assert(argc == 2);
    const char* disk_image_file = argv[1];

    pages_init(disk_image_file);

    // Page 0 is 10 inodes.
    inode* nodes = (inode*) pages_get_page(0);
    
    // Inode 0 is the root directory.
    inode* root_node = &(nodes[0]);
    root_node->refs = 1;
    root_node->mode = 040755;
    root_node->size = 0;
    root_node->ptrs[0] = alloc_data_block();

    dirent* ents = pages_get_page(root_node->ptrs[0]) + 1;

    dirent* e1 = &(ents[0]);
    strcpy(e1->name, "one.txt");
    e1->inum = 1;
    inode* n1 = &(nodes[e1->inum]);
    n1->refs = 1;
    n1->mode = 0100644;
    const char* t1 = "the quick brown fox jumps over the lazy dog";
    n1->size = strlen(t1);
    n1->ptrs[0] = alloc_data_block();
    char* d1 = pages_get_page(n1->ptrs[0]) + 1;
    strcpy(d1, t1);

    dirent* e2 = &(ents[1]);
    strcpy(e2->name, "two.txt");
    e2->inum = 2;
    inode* n2 = &(nodes[e2->inum]);
    n2->refs = 1;
    n2->mode = 0100644;
    const char* t2 = "hello, two";
    n2->size = strlen(t2);
    n2->ptrs[0] = alloc_data_block();
    char* d2 = pages_get_page(n2->ptrs[0]) + 1;
    strcpy(d2, t2);

    return 0;
}
