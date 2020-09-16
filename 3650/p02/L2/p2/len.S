    .global main
    .text
/*
long
len(char* text)
{
    long ii = 0;
    for (; text[ii]; ++ii) {
        // do nothing
    }
    return ii;
}
    Vars:
        - text - %rdi
        - ii - %rax
        - tmp - %r9
*/

len:
    enter $0, $0

    mov $0, %rax
len_for_cond:
    mov (%rdi,%rax,1), %r9b
    cmp $0, %r9b
    je len_for_done

    // do nothing

    inc %rax
    jmp len_for_cond
len_for_done:

    // return rax
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
