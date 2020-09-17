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
    - text[ii] - %r10b
*/

len:
    enter $0, $0

    mov $0, %rax
len_loop_cond:
    // loads 1 byte from (%rdi + 1*%rax)
    mov (%rdi,%rax,1), %r10b
    // loads 8 bytes from (%rdi + 8*%rax)
    //mov (%rdi,%rax,8), %r10
    cmp $0, %r10b
    je len_loop_done

    // do nothing
    inc %rax
    jmp len_loop_cond
len_loop_done:
    // ret val is already in %rax
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
  - argv    - %rsi
  - argv[1] - %r12
*/

main:
    push %r12
    enter $8, $0
    
    mov 8(%rsi), %r12 

    mov %r12, %rdi
    call len

    mov $fmt, %rdi
    mov %r12, %rsi
    mov %rax, %rdx
    mov $0, %al
    call printf

    mov $0, %rax
    leave
    pop %r12
    ret
    .data
fmt: .string "len(%s) = %ld\n"
