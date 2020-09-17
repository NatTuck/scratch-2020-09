    .global main
    .text
/*
long
len(char* text)
{
    if (!*text) { return 0; }
    return 1+len(text+1);
}
Vars:
    - text  - %rdi
    - *text - %r10b
*/

len:
    enter $0, $0
    mov $0, %rax
    mov (%rdi), %r10b
    cmp $0, %r10b
    je len_done

    inc %rdi
    call len
    inc %rax 

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
