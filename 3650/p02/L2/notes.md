

```
    mov $7, %rax
    //mov $'c, %rax
    mov $'c, %al
    
    movq $7, 16(%rsp)


    mov $8, %rax
    //mov 1024(%rax), %rbx
    lea 1024(%rax), %rbx  // %rbx = 1024 + 8 = 1032

    // lea tends to be used to translate "&" operator


    // Common case for arithmetic instructions
    add %rax, %rbx // %rbx = %rax + %rbx

    add rbx, rax  // intel syntax

    // Weird case
    imul %rdi   // %rdx:%rax = %rdi * %rax
```



```
label:
    enter $0, $0

    leave
    ret
```

```
enter $XX, $0
    IS
push %ebp
mov %esp, %ebp
sub $XX, %esp
/* waste 8 clock cycles*/

leave
    IS
mov %ebp, %esp
pop %ebp
```


```
foo:
    enter $0, $0
    
    ... body

    leave
    ret

main:
    ....
    call foo
ret_addr_here:
    // do something else
```

Stack:
    - return address to main
    - old base pointer
         (base pointer)
    - XX bytes of stack frame allocated
         (stack pointer) 




## Design Recipie for Assembly

 - You figure out at least one function you need.
 - You apply the design recipie for a function to it.
 - That'll generate more functions you need to do.
 - When you're out of functions, you're done.

## Design Recipie for a function

 1. Signature
 2. Pseudocode (= C code)
 3. Variable Mappings
 4. Skeleton
 5. Fill in the function body

### Variable Mappings

Where can we put values?

 - In a register
   - Temporary
     - If you call a function, all your temporary 
       registers (are assumed to) get overwritten.
     - %rdi, %rsi, %rdx, %rcx, %r8, %r9
     - %r10, %r11
     - %rax
   - Safe
     - If you call a function, that won't change
       the value in any safe regisers.
     - If we use a safe register, we must save
       and restore it's old value.
     - %rbx, %r12..%r15
 - On the stack
     - enter $32, $0
     - That gives us 4 slots to store stuff:
       0(%rsp), 8(%rsp), 16(%rsp), 24(%rsp)
     - 24(%rsp) = -8(%rbp)
 - Elsewhere in memory
     - Usually a global label


```
    Our Stack Frame:
      function return address
      old %rbp                  <--- %rbp
    - 24(%rsp) or -8(%rbp)
    - 16(%rsp) or -16(%rbp)
    - 8(%rsp) or -24(%rbp)
    - 0(%rsp) or -32(%rbp)      <--- %rsp
```



