
The rule is:

When you execute the call instruciton, the stack pointer must be aligned
on a 16-byte boundary. That means (%rsp mod 16 == 0). This is part of the
calling convention for Linux on AMD64.

We tend to enforce a broader rule: we want a 16-byte stack alignment
whenever we're executing a function body.


