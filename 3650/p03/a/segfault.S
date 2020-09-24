    .global main
    .text

none:
    mov $347, %r10
    mov %r10, %rax // %rax = 347
    mov (%r10), %rax // %rax = (value in mem @ 347)
    lea (%r10), %rax // %rax = 347

main:
    enter $0, $0

    mov $347, %r10
    mov (%r10), %rsi 

    mov $fmt, %rdi
    mov $0, %al
    call printf

    leave
    ret

    .data
fmt:
    .string "%ld\n"
