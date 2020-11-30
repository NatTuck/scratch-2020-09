
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "pages.h"
#include "inode.h"
#include "directory.h"

int
main(int argc, char* argv[])
{
    assert(argc == 2);
    const char* disk_image_file = argv[1];

    // BUG: Creates disk image if doesn't exist.
    pages_init(disk_image_file);

    printf("== inodes ==\n");
    inode* nodes = pages_get_page(0);
    for (int ii = 0; ii < 10; ++ii) {
        if (nodes[ii].mode == 0) {
            continue;
        }
        printf(
            "node #%d: {refs: %d, mode: %04o, size: %d, ptr: %d}\n",
            ii, nodes[ii].refs, nodes[ii].mode, nodes[ii].size, nodes[ii].ptrs[0]
        );
    }
    
    printf("== files ==\n");
    inode* dir_node = &(nodes[0]);
    dirent* ents = pages_get_page(dir_node->ptrs[0]) + 1;
    for (int ii = 0; ii < 10; ++ii) {
        if (ents[ii].inum == 0) {
            continue;
        }

        int inum = ents[ii].inum;
        inode* nn = &(nodes[inum]);
        char* data = pages_get_page(nn->ptrs[0]) + 1;
        printf("file #%d: '%s' => (%d) '%s'\n", ii, ents[ii].name, inum, data);
    }

    return 0;
}
