    .global main
    .text

    // This is why we distinguish
    //   Temporaries vs. Safe Registers
    // and save their values in relation to
    // function calls.

    // fact(1) = 1
    // fact(x) = x * fact(x-1)

    // 0(%rsp) is x
fact:
    enter $16, $0
    mov %rdi, 0(%rsp)

    mov $1, %rax
    cmp $1, 0(%rsp)
    jle fact_done

    // return x * fact(x-1)
    mov 0(%rsp), %rdi
    dec %rdi   
    call fact
    imulq 0(%rsp)
 
fact_done:
    leave
    ret

main:
    enter $0, $0

    mov 8(%rsi), %rdi
    call atol 

    mov %rax, %rdi
    call fact
   
    mov $fmt, %rdi
    mov %rax, %rsi
    mov $0, %al
    call printf

    leave
    ret

    .data
fmt:
    .string "%ld\n"
