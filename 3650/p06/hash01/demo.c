
#include "set.h"

int
main(int _ac, char* _av[])
{
    // Linked list version was immutable.
    // Hash table is more obvious as a mutable type.
    // We could do HAMTs or something, but...

    // Insert now modifies the set.
    // No operation takes a set, returns a set, and doesn't
    // make a logical copy.

    set* pri1 = empty_set();
    insert(pri1, "red");
    insert(pri1, "green");
    insert(pri1, "blue");
    insert(pri1, "green");
    print_set(pri1);

    set* pri2 = empty_set();
    insert(pri2, "red");
    insert(pri2, "yellow");
    insert(pri2, "blue");
    print_set(pri2);

    set* pri3 = empty_set();
    insert(pri3, "cyan");
    insert(pri3, "magenta");
    insert(pri3, "yellow");
    insert(pri3, "black");
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
