
Two kinds of struct:

 - Arrays
 - Structs

Most languages provide some standard library structures.

Two very common structures are:

 - A variable-size sequence (e.g. List, ArrayList, Vector, etc)
 - Key-Value Map (e.g. Dictionaries, map, TreeMap, HashMap, etc) 

What we want:

 - Normal array functionality: put / get by index
 - A "push back" operation which appends an element to the end of
   the array.
   - Example: push_back([1,2,3,4], 5) => [1,2,3,4,5]
 - Arrays must remain contiguous in memory so loops work normally.

What that means:

 - We can start with a normal array.
 - When we push_back, we need to allocate new space, copy the items over,
   and then free the old space.

Problem: Filling an array of n items takes n^2 time.

 - To add N items, that's N reallocation.
 - Each reallocation takes O(N) copying.

Solution: We allocate more space than we need.

 - Instead of allocating an empty array, allocate a small array - maybe
   four slots.
 - Push back doesn't reallocate if we have empty slots.
 - When we run out of empty slots, we double our allocated space.
 - To do this, we need to track both size and capacity for our data
   structure.
 - Inserting N items now takes N time.

Empty array, Initial capacity = 4, push_back 10 items.

 - push_back 1..4 => 4 operations
 - push_back 5 doubles capacity to 10, so 4+1 = 5
 - push_back 6..8 => 3 operations
 - push_back 9 doubles capacity to 16, so 8+1 = 9
 - push_back 10 is => 1 operaton
 - total = 24, or about 2*n

Empty array, Initial capacity = 4, push_back 100 items.

 - double at 5, 9, 17, 33, 65
 - 100 inserts, 124 copies = 224

Interesting fact: Inserting *an* item may still take O(n) time.

A Variable Length Array (C++ vector, Java ArrayList) is:

 - A struct
 - Three fields:
   - data - pointer to an array of elements
   - size - number of elements in the array
   - capacity - size of the data array (always >= size)
 - Non-resizing operations can access the data array elements directly.
 - To append, insert into free space.
 - If there are no free slots, we call "realloc" (see "man 3 realloc")
   to resize the array to double the current capacity. 

In order to get the performance benefit, any multiplicative factor will work
for resizing. I suggest 2 because it's simple, but C++ might use (e.g.) 1.5


 

