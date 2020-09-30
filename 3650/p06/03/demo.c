
#include "set.h"

int
main(int _ac, char* _av[])
{
    set* pri = empty_set();
    pri = insert(pri, "red");
    pri = insert(pri, "blue");
    pri = insert(pri, "green");
    print_set(pri);
    free_set(pri);

    set* pri2 = empty_set();
    pri2 = insert(pri2, "red");
    pri2 = insert(pri2, "blue");
    pri2 = insert(pri2, "yellow");
    print_set(pri2);

    set* ink = empty_set();
    ink = insert(ink, "cyan");
    ink = insert(ink, "magenta");
    ink = insert(ink, "yellow");
    ink = insert(ink, "black");
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

