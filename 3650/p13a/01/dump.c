
#include <assert.h>

#include "pages.h"
#include "inode.h"
#include "directory.h"

int
main(int argc, char* argv[])
{
    assert(argc == 2);
    const char* image_file = argv[1];

    // BUG: This creates the disk image.
    pages_init(image_file);

    // Page 0 is inodes
    inode* nodes = (inode*) pages_get_page(0);

    printf("== nodes ==\n");
    for (int ii = 0; ii < 10; ++ii) {
        inode* nn = &(nodes[ii]);
        if (nn->mode != 0) {
            printf("node #%d: ", ii);
            print_inode(nn);
        }
    }
    printf("\n");

    printf("== files ==\n");
    inode* dir_node = &(nodes[0]);
    dirent* dir = pages_get_page(dir_node->ptrs[0]);
    for (int ii = 0; ii < 10; ++ii) {
        if (dir[ii].inum == 0) {
            continue;
        }

        inode* node = &(nodes[dir[ii].inum]);
        char* data = pages_get_page(node->ptrs[0]);
        if (data[0]) {
            printf("file #%d: '%s' => {%s}\n", ii, dir[ii].name, data + 1);
        }
    }

    return 0;
}

void
print_inode(inode* nn)
{
    printf(
        "refs: %d, mode: %06o, size: %d, ptr: %d\n",
        nn->refs, nn->mode, nn->size, nn->ptrs[0]
    );
}
