
inidx = 4
outidx = 2     // inidx - outidx <= 8
itemsem = 3
spacesem = 5   // itemsem + spacesem = 8

What happens when qii or qjj integers overflow?

Max value of unsigned int?

Range is 0..2^32 - 1

Consider the 16-bit int case:

 - Max value is 65535
 - 65535 % 8 = 7
 - (65535 + 1) % 8 = 0
 - ((65535 + 1) % 65536) % 8 = 0

Size of queue must be a factor of the maximum int size, so a power of two.


HW07: You can build the barrier with:

  - mutexes
  - cond vars



