
#include "set.h"

int
main(int _ac, char* _av[])
{
    set* pri1 = empty_set();
    pri1 = insert(pri1, "red");
    pri1 = insert(pri1, "green");
    pri1 = insert(pri1, "blue");
    pri1 = insert(pri1, "green");
    print_set(pri1);

    set* pri2 = empty_set();
    pri2 = insert(pri2, "red");
    pri2 = insert(pri2, "yellow");
    pri2 = insert(pri2, "blue");
    print_set(pri2);

    set* pri3 = empty_set();
    pri3 = insert(pri3, "cyan");
    pri3 = insert(pri3, "magenta");
    pri3 = insert(pri3, "yellow");
    pri3 = insert(pri3, "black");
    print_set(pri3);

    set* colors1 = union_set(pri1, pri2);
    set* colors2 = union_set(colors1, pri3);
    free_set(colors1);

    free_set(pri1);
    free_set(pri2);
    free_set(pri3);

    print_set(colors2);
    free_set(colors2);
    return 0;
}
