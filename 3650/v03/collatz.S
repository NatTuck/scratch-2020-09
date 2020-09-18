    .global main
    .text
/*
long
iterate(long xx)
{
    if (xx % 2 == 0) {
        return xx/2;
    }
    else {
        return xx*3 + 1;
    }
}
    xx - %rdi
    tmp - %r10
*/
iterate:
    enter $0, $0

    mov %rdi, %rax
    mov $2, %r10
    cqo
    idiv %r10
    cmp $0, %rdx
    je iterate_then
    jmp iterate_else

iterate_then:
    // do nothing, ret val already in %rax
    jmp iterate_done

iterate_else:
    mov %rdi, %rax
    mov $3, %r10
    imul %r10
    inc %rax

iterate_done:
    leave
    ret

/*
int
main(int argc, char* argv[])
{
    long xx = atol(argv[1]);
    long ii = 0;

    while (xx > 1) {
        printf("%ld\n", xx);
        xx = iterate(xx);
        ii++;
    }

    printf("ii = %ld\n", ii);
    return 0;
}

Variable mapping:
    - argv - %rsi
    - xx   - %r12
    - ii   - %r13
*/

main:
    push %r12
    push %r13
    enter $0, $0

    mov 8(%rsi), %rdi
    call atol
    mov %rax, %r12 // init xx

    mov $0, %r13   // init ii

main_loop_cond:
    cmp $1, %r12
    jle main_loop_done

    mov $long_fmt1, %rdi
    mov %r12, %rsi
    mov $0, %al
    call printf

    mov %r12, %rdi
    call iterate
    mov %rax, %r12

    inc %r13
    jmp main_loop_cond
main_loop_done:

    mov $long_fmt2, %rdi
    mov %r13, %rsi
    mov $0, %al
    call printf

    mov $0, %rax
main_done:
    leave
    pop %r13
    pop %r12
    ret

    .data
long_fmt1:  .string "%ld\n"
long_fmt2:  .string "ii = %ld\n"
