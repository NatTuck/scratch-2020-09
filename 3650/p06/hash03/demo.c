
#include "set.h"

int
main(int _ac, char* _av[])
{
    set* pri = empty_set();
    insert(pri, "red");
    insert(pri, "blue");
    insert(pri, "green");
    print_set(pri);

    set* pri2 = empty_set();
    insert(pri2, "red");
    insert(pri2, "blue");
    insert(pri2, "yellow");
    print_set(pri2);

    set* ink = empty_set();
    insert(ink, "cyan");
    insert(ink, "magenta");
    insert(ink, "yellow");
    insert(ink, "black");
    print_set(ink);

    set* all1 = union_set(pri, pri2);
    set* all = union_set(all1, ink);
    free_set(all1);

    free_set(pri);
    free_set(pri2);
    free_set(ink);

    print_set(all);
    free_set(all);
    return 0;
}

