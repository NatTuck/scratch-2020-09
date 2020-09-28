    .global main
    .text

    /*
int
main(int _argc, char* _argv[])
{
    long xs[] = {1, 2, 3, 4};
    long nn = 4;

    long sum = 0;
    for (long ii = 0; ii < nn; ++ii) {
        sum += xs[ii];
    }

    printf("%ld\n", sum);

    return 0;
}
    */

main:
    enter $0, $0
    sub $32, %rsp
    mov %rsp, %r8     // xs is %r8

    movq $1, 0(%r8)
    movq $2, 8(%r8)
    movq $3, 16(%r8)
    movq $4, 24(%r8)

    mov $4, %r10       // nn is %r10
    mov $0, %r11       // sum is %r11
    mov $0, %rcx       // ii is %rcx
loop_cond:
    cmp %r10, %rcx
    jge loop_done

    //add (%rdx,%rcx,8), %rax
    mov %rcx, %rax
    mov $8, %r9
    imul %r9
    add %r8, %rax
    add (%rax), %r11

    inc %rcx
    jmp loop_cond
loop_done:

    mov $fmt, %rdi
    mov %r11, %rsi
    mov $0, %al
    call printf

    mov $0, %rax
    leave
    ret


    .data
fmt:    .string "%ld\n"
