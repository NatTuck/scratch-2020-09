

Course website: 
 - http://ntuck-neu.site
 - Late registration? Read the syllabus and
   email me.

## Design Recipie for Assembly

 - A program (in asm or C) is a collectoin of
   functions.
 - To write a program, you figure out at least
   one function you need and write that (e.g.
   "main").
 - That'll discover more functions, when you've
   written all the functoins you're done.

## Designing a Function

 1. Signature
 2. Pseudocode (= C code)
 3. Variable Mappings
 4. Skeleton
 5. Write the function body

### Variable mappings

For each var / value, where does it go?

 1. Registers
   - Temporary Register
     - %rdi, %rsi, %rdx, %rcx, %r8, %r9
     - %rax
     - %r10, %r11
   - Safe Register
     - %r12-%r15, %rbx
 2. The Stack
   - enter $XX, $0
   - Example: enter $16, $0
     That allocates two slots for 64-bit vals.
       0(%rsp), 8(%rsp)
     Also known as:
     -16(%rbp), -8(%rbp)
 3. In memory somewhere else (e.g. a global)
   - Example: the "num" label in the 
              week1 example

When to allocate on stack rather than safe reg?
 - We're out of safe register.
 - If we want to get address of variable.

Example:
    - scanf("%ld", &xx);
      then xx must be allocated on the stack

```
long
foo(long xx, long yy)
{
    long zz = xx + yy;
    long ww = zz + xx;
    bar(&zz, xx);
    return xx + ww;
}

Variable mapping:
    - xx - %rbx
    - yy - %rsi
    - zz - 0(%rsp)
    - ww - %r12

foo:
    push %r12      // 8 bytes
    push %rbx      // 8 bytes
    enter $16, $0   // + 8 = 24, that not aligned
    // 8(%rsp) is unused

    leave
    pop %rbx
    pop %r12
    ret
```




