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
    xx - %rbx
*/

countdown:
    push %rbx
    enter $8, $0
    mov %rdi, %rbx
    
    mov $long_fmt, %rdi
    mov %rbx, %rsi
    mov $0, %al
    call printf

    cmp $0, %rbx
    jle countdown_done

    mov %rbx, %rdi
    dec %rdi
    call countdown
    
countdown_done:
    leave
    pop %rbx
    ret



/*
int
main(int argc, char* argv[])
{
    if (argc != 2) {
        puts("bad usgae");
        return 1;
    }

    long xx = atol(argv[1]);
    countdown(xx);
    return 0;
}

    - argc - %rdi
    - argv - %rsi
    - xx - %rdi
*/

main:
    enter $0, $0

    cmp $2, %rdi
    je skip_usage

    mov $usage_msg, %rdi
    call puts
    mov $1, %rax
    jmp done

skip_usage:
    // mov argv[1], %rdi
    mov 8(%rsi), %rdi
    call atol 
    mov %rax, %rdi

    call countdown
    mov $0, %rax 

done:
    leave
    ret


    .data
usage_msg: .string "bad usage"
long_fmt: .string "%ld\n"
