    .global main
    .text
main:
    enter $0, $0

    //mov $bar, %r9
    //mov $foo, %r10

    //sub %r10, %r9

    mov $0, %rsi
    mov $bar, %rax

    mov $longfmt, %rdi
    mov 4(%rax), %esi    // bar[1]
    mov $0, %al
    call printf

    leave
    ret

    .data
longfmt:
    .string "%ld\n"
foo:
    .space 24, 0
bar:
    .int 10
baz:
    .int 20
    .int 30
    .int 40
