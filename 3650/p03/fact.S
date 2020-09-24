    .global main
    .text

    // fact(1) = 1
    // fact(x) = x * fact(x-1)

    // Vars:
    //  - x is 0(%rsp)
    //  - alt: x is %r12
    //  - alt: x is %rdi but use caller-save
fact:
    enter $16, $0
    mov %rdi, 0(%rsp)

    mov $1, %rax
    cmp $1, %rdi // still ok
    jle fact_done

    // y = fact(x-1)
    mov 0(%rsp), %rdi
    dec %rdi
    call fact

    //return x * y
    imulq 0(%rsp)

fact_done:
    leave
    ret

main:
    enter $0, $0

    // atol(argv[1])    
    mov 8(%rsi), %rdi
    call atol

    // long x = fact(argv[1]);
    // x is %rax
    mov %rax, %rdi
    call fact
  
    // printf("%ld\n", x) ;
    mov $fmt, %rdi 
    mov %rax, %rsi
    mov $0, %al
    call printf

    // return 0;
    mov $0, %rax
    leave
    ret

.data
fmt:    .string "%ld\n"
