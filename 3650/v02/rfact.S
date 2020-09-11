    .global main

    .data
scanfmt: .string "%ld"
printfmt: .string "fact(%ld) = %ld\n"

    .text

    /* Pseudocode:

    main() {
      long x
      scanf("%ld", &x)
      long y = fact(x)
      printf("fact(%ld) = %ld\n", x, y)
    }

    fact(int x) {
      if (x <= 1) return 1
      return x * fact(x-1)
    }
    */

fact:
    // Plan A: Use a safe register
    // x is %r12
    push %r12    // Unalign stack
    enter $8, $0 // Align stack

    mov $1, %rax
    cmp $1, %rdi
    jle fact_done

    mov %rdi, %r12

    dec %rdi
    call fact

    imul %r12

fact_done:
    leave
    pop %r12
    ret

main:
    enter $16, $0

    mov $scanfmt, %rdi
    lea 0(%rsp), %rsi
    mov $0, %al
    call scanf

    mov 0(%rsp), %rdi
    call fact

    mov $printfmt, %rdi
    mov 0(%rsp), %rsi
    mov %rax, %rdx
    mov $0, %al
    call printf

    mov $0, %rax
    leave
    ret
