
Class website: https://ntuck-neu.site

## Design Recipie for Assembly Programs

### Design recipie for a program

 - Figure out at least one function you need 
   to write.
 - Follow the design recipie for a function.
 - That'll probably help you find more funcitons 
   you need.

### Design Recipie for a Function

 1. Signature
 2. Pseudocode (= C Code)
 3. Variable Mappings
 4. Skeleton
 5. Write the body of the function.

### Variable Mappings

For each variable / value in the pseudocode, where do
we put that data in the assembly code?

 - In a register? Which one?
   - Temporary register?
     - Temporary registers can (are assumed to) get
       overwritten if we call a function.
     - %rdi, %rsi, %rcx, %rdx, %r8, %r9
     - %r10, %r11
     - %rax
   - Safe registers?
     - Safe registers will not (appear to be) 
       overwritten if we call a function.
     - If you use a safe register, you first must
       save the old value, then you restore that
       value before returning.
     - %rbx, %r12..%r15 
 - On the stack. Where?
     - We'll allocate some number of slots
       on the stack (with enter $XX, $0).
     - So if we enter $32, 0 - 4 slots
     - Those slots are 0(%rsp), 8(%rsp), 
       16(%rsp), 24(%rsp)
     - May also do %rbp relative positions,
       24(%rsp) is also -8(%rbp).
 - Somewhere else in memory. Where?
   - Most common: At a global label.
   - example last week was "num"

### Skeleton

```
label:
    push %r12
    push %r13
    push %r14 // problem: we've pushed 24 bytes
              // That breaks stack alignment rule
              // stack must be aligned at 16 bytes
    enter $8, $0  // solution: add padding

    // TODO: funtion body 

    leave
    pop %r14
    pop %r13
    pop %r12
    ret
```

Variant 1: Safe registers need to be saved/restored.
 - Example: Variable mapping allocated %r12, %r13, %r14

```
label:
    enter $32, $0 // round up to multiple of 16

    // TODO: funtion body 

    leave
    ret
```

Variant: Allocate variables directly on the stack

 - Example: We want 3 vars on the stack.
 -    At 0(%rsp), 8(%rsp), and 16(%rsp).


## What's this "enter/leave" stuff?

 - Stack grows down.

When we call a function, "call" pushes a return address.

```
enter $XX, $0
    IS
push %ebp
mov %esp, %ebp
sub $XX, %exp
/* waste 8 clock cycles */

leave
    IS
mov %ebp, %rsp
pop %ebp
```



Stack:
    - return addr to main
    - (this is where safe registers would be pushed)
    - old %ebp
    - $XX bytes allocated by enter

```
foo:
    enter $0, $0

    leave
    ret
main:
    ...
    call foo
    (this line is the return addr)
```


