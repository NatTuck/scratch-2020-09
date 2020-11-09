
# Page Tables

32-bit virtual address space

 = 2^32 bytes
 = 2^12 = 4096 byte pages
 = 2^32 / 2^12 = 2^20 pages

Page table translates virtual page # into a physical page # + metadata.

A page # is 20 bits.

20 bits * 2^20 pages = minimum 2^25 bits of RAM = 2^22 bytes = 4 megs

An early i386 computer shipped with 2MB.

Multi-level page tables are compression: don't waste space on unused
virtual page #'s.

With multi-level page tables we can do

 - 2^10 rows in top level table
   - row can point to another table or be null

Example:

 0000 0001 00 ; 0000 0000 00 ; 0000 0000 0000
      4               0                -

 - In the top level table, look at row 4.
   - That'll tell us where to find the second level table.
 - In the second level table, row 0.
 - Within the physical page, byte 0.






