    .global main
    .text
   /* 
void
countdown(long xx)
{
    printf("%ld\n", xx);

    if (xx > 0) {
        countdown(xx - 1);
    }
}
    xx - %r12
    */

countdown:
    push %r12
    enter $8, $0
    mov %rdi, %r12
  
    mov $long_fmt, %rdi
    mov %r12, %rsi
    mov $0, %al
    call printf

    cmp $0, %r12
    jle countdown_else 

    mov %r12, %rdi
    dec %rdi
    call countdown

countdown_else:
 
    leave
    pop %r12
    ret 

    /*
int
main(int argc, char* argv[])
{
    if (argc != 2) {
        puts("bad usage");
        return 1;
    }

    long xx = atol(argv[1]);
    countdown(xx);
    return 0;
}

    argc - %rdi (before atol)
    argv - %rsi
    xx - %rdi (after atol)
    */

main:
    enter $0, $0

    cmp $2, %rdi
    jne usage

    // mov argv[1], %rdi
    mov 8(%rsi), %rdi
    call atol
    mov %rax, %rdi

    call countdown
    mov $0, %rax
    jmp done

usage:
    mov $bad_usage, %rdi
    call puts
    mov $1, %rax
    jmp done

done:
    leave
    ret

    .data
bad_usage: .string "bad usage"
long_fmt: .string "%ld\n"
