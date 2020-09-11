    .global main
    .data
prompt:
    .string "number?"
long_fmt:
    .string "%ld"
long_print:
    .string "%ld\n"
num:
    .string "12345678"
notless:
    .string "not less"
less:
    .string "less"
    .text
main:
    enter $0, $0

    mov $prompt, %rdi
    call puts

    mov $long_fmt, %rdi
    mov $num, %rsi
    mov $0, %al
    call scanf

    //mov $long_print, %rdi
    mov num, %rax
    //mov $0, %al
    //call printf

    // if (%rax <= 10)
    cmp $10, %rax
    jle less_than
not_less_than:
    mov $notless, %rdi
    call puts
    jmp done

less_than:
    mov $less, %rdi
    call puts
    jmp done

done:
    leave
    ret
