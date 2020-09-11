    .global main

    .data
fmt:
    .string "avg(7, 3) = %ld\n"

    .text

    // Argument registers:
    //   - %rdi, %rsi, %rdx, %rcx, %r8, %r9
    //
    // Return registers:
    //   - %rax

    // avg(x, y) = (x + y) / 2
avg:
    enter $0, $0
    // x is %rdi
    // y is %rsi

    add %rdi, %rsi
    mov %rsi, %rax

    mov $2, %r10

    cqo
    idiv %r10    // idiv divies %rax by its one argument; result in %rax

    // Why does idiv take a 128-bit dividend?

    // Answer: Because 64 bit multiplication produces a 128-bit product.

    leave
    ret


main:
    enter $0, $0

    mov $7, %rdi
    mov $3, %rsi
    call avg

    mov $fmt, %rdi
    mov %rax, %rsi
    mov $0, %al
    call printf

    leave
    ret
