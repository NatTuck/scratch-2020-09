    .global main
    .text
/*
long
len(char* text)
{
    if (!*text) { return 0 }
    return 1 + len(text+1);
}
    Vars:
        - text - %rsi
        - *text - %dl (low byte of %rdx)
*/

len:
    enter $0, $0
    mov (%rdi), %dl
    cmp $0, %dl
    je return_zero

    inc %rdi
    call len
    inc %rax
    jmp len_done

return_zero:
    mov $0, %rax
len_done:
    leave
    ret

/*
int
main(int argc, char** argv)
{
    printf(
        "len(%s) = %ld\n", 
        argv[1], 
        len(argv[1])
    );
    return 0;
}
Vars:
    - argv - %rsi
    - argv[1] - 0(%rsp)

*/

main:
    enter $16, $0
    mov 8(%rsi), %r10
    mov %r10, 0(%rsp)

    mov %r10, %rdi
    call len

    mov $fmt, %rdi
    mov 0(%rsp), %rsi
    mov %rax, %rdx
    call printf

    mov $0, %rax
    leave
    ret

    .data
fmt: .string "len(%s) = %ld\n"
