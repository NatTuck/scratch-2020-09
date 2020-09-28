    .global main
    .data
scanfmt: .string "%d"

    .text

/*
int
bad_read_int()
{
    int x;
    scanf("%d", &x);
    return x + 4;
}
Vars:
    - x is on the stack, 0(%rsp)
*/

bad_read_int:
    enter $16, $0

    // int x
    // scanf(&x)
    mov $scanfmt, %rdi
    lea 0(%rsp), %rsi  
    mov $0, %al // This is part of the calling convention
                // for a variable argument function. See the ABI docs.
    call scanf 

    // return x + 4
    mov 0(%rsp), %eax    // return an int, so "e" register
    add $4, %eax
    leave
    ret

/*
int
main(int _ac, char* _av)
{
    puts("Enter a number");
    printf("We got: %d\n", bad_read_int());
}
*/
main:
    enter $0, $0
    mov $prompt, %rdi
    call puts

    call bad_read_int

    mov $fmt, %rdi
    mov %rax, %rsi
    mov $0, %al
    call printf

    mov $0, %rax
    leave
    ret

    .data
prompt: .string "enter a number"
fmt: .string "we got: %d\n"
