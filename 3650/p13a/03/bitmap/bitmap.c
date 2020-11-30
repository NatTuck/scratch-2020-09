

// 128 bit bitmap
uint64_t map[2];

// Bitmap operations

void bitmap_put(uint64_t*, int, int);
int bitmap_get(uint64_t*, int);

bitmap[4] = 1;   // bitmap_put(map, 4, 1);
bitmap[7] = 0;   // bitmap_put(map, 7, 0);

// bitmap_get(map, 11);
if (bitmap[11]) {
    // bitwise operations:
    //  - shifts <<, >>
    //  - logical &, |, ~
}


uint64_t*
allocate_bitmap(size_t bits)
{
    size_t num_ints = round_up(bits / 64.0);
    return malloc(num_ints * sizeof(uint64_t));
}



