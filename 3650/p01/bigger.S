    .global main
    .data
prompt:
    .string "number?"
long_fmt:
    .string "%ld"    
num:
    .string "01234567"
not_less_msg:
    .string "not less"
its_less_msg:
    .string "its less"

    .text
main:
    enter $0, $0

    mov $prompt, %rdi
    call puts

    mov $long_fmt, %rdi
    mov $num, %rsi
    mov $0, %al
    call scanf

    mov num, %rax

    // google "gdb tutorial"

    // if (%rax <= 10)
    cmp $10, %rax
    jle less_than_or_eq
not_less:
    mov $not_less_msg, %rdi
    jmp print_answer

less_than_or_eq:
    mov $its_less_msg, %rdi

print_answer:
    call puts

    mov $0, %rax
    leave 
    ret
