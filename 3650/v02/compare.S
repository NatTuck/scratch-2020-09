
    /*
    main(int argc, char* argv[])

    ./compare 3 5

    argv[0] is "./compare"

    long aa = atol(argv[1])  // 3
	long bb = atol(argv[2])  // 5
    if (aa > bb) {
      print "{aa} > {bb}";
    else
      print "{aa} <= {bb}"
    */

    .global main
    .text
main:
    push %r12 // argv is %r12
    push %r14 // aa is %r14
    push %r15 // bb is %r15
    enter $8, $0
    mov %rsi, %r12

    cmp $3, %rdi
    je main_cmp

    mov $usage, %rdi
    call puts
    mov $1, %rax
    jmp done

main_cmp:

    mov 8(%r12), %rdi
    call atol
    mov %rax, %r14

    mov 16(%r12), %rdi    // argv[2], given that sizeof(char*) == 8
    call atol
    mov %rax, %r15

    cmp %r15, %r14
    jg big
    jmp sml

big:
    mov $gt, %rax
    jmp print

sml:
    mov $le, %rax
    jmp print

print:
    mov $msg, %rdi
    mov %r14, %rsi
    mov %rax, %rdx
    mov %r15, %rcx
    mov $0, %al
    call printf

    mov $0, %rax
done:
    leave
    pop %r15
    pop %r14
    pop %r12
    ret

    .data
msg:    .string "%d %s %d\n"
usage:  .string "Usage: ./compare NN NN"
gt:  .string ">"
le:  .string "<="
