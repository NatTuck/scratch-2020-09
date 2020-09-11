


## AMD64 SystemV Calling Convention: Registers

16 total registers:

    %rdi, %rsi, %rcx, %rdx, %rax, %rbx, %rbp, %rsp
    %r8, %r9, %r10, %r11, %r12, %r13, %r14, %r15
    
Split into two categories:

## Temporary

 - %rdi, %rsi, %rdx, %rcx, %r8, %r9, %rax, %r10, %r11

The rule: 

 - If you call a function (or a system call), these registers are
   assumed to be overwritten.
 - To preserve a value across a call, you must save it.
 - "Caller save"

## Safe Registers

 - %r12, %r3, %r14, %r15, %rbx

The rule:

 - If you call a function or system call, these registers will look
   like they were not overwritten; the value is preserved.
 - If you use these registers, you must save the previous value and
   restore it before returning.
 - "Callee-save"
 
## (special registers)

 - %rbp, %rsp
