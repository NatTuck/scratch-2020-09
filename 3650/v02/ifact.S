    .global main

    .data
scanfmt:
    .string "%ld"
printfmt:
    .string "fact(%ld) = %ld\n"

    .text

    /*
    long x
    scanf("%ld", &x)
    long y = 1
    for (int ii = x; ii > 0; ii--) {
      y = y * ii
    }

    printf("fact(%ld) = %ld\n", x, y)
    */

    /*
    Where are we putting our values?

     - x  on the stack:
       - it's the 8 bytes starting at %rsp
       - 0(%rsp)
     - y  is %rax
     - ii is %rcx
    */

main:
    // first argument to enter is number of bytes
    // to allocate on the stack for this function call

    // can't just allocate 8!
    // need to maintain alignment invariant:
    //    When we call a function, the value in %rsp
    //    must be divisible by 16.
    enter $16, $0

    mov $scanfmt, %rdi
    //mov %rsp, %rsi     // this does the right thing
    //mov 0(%rsp), %rsi  // this moves the value, not the address
    //mov 8(%rsp), %rsi  // this moves the value, not the address
    lea 0(%rsp), %rsi  // this calculates the memory address as if were were
                      // accessing memory - the address is the result
    mov $0, %al
    call scanf

    mov $1, %rax
    mov 0(%rsp), %rcx
loop_cond:
    cmp $0, %rcx
    jle loop_done

    imul %rcx   // y = y * ii

    dec %rcx
    jmp loop_cond
loop_done:

    mov $printfmt, %rdi
    mov 0(%rsp), %rsi
    mov %rax, %rdx
    mov $0, %al
    call printf

    mov $0, %rax
    leave
    ret
