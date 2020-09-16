Recipie for Assembly Programs:

 - A program is a collection of functions.
 - Design it one function at a time.
 - Start from "main".

Recipe for a Function:

 1. Signature
 2. Pseudocode (= C code)
 3. Variable Mappings   <- HW's ask for
 4. Skeleton            <- HW's ask for
 5. Write function body

## Variable Mappings

Where can we put a value?

 1. Registers
    - Temporary
      - %rdi, %rsi, %rdx, %rcx, %r8, %r9
      - %rax
      - %r10, %r11
    - Safe 
      - %r12-15, %rbx
 2. The Stack
      - enter $16, $0
        allocates 16 bytes of "stack frame"
        two slots for variables:
        0(%rsp), 8(%rsp)
        same slots are:
        -16(%rbp), -8(%rbp)
 3. Elsewhere in memory
      - e.g. a global label


# Other topic: Example Problem








