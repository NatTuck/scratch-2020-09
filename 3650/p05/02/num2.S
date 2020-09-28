    .global main
    .data
scanfmt: .string "%d"

    .text

/*
void
bad_read_int(int* xp)
{
    scanf("%d", xp);
    *xp += 4;
}
Vars:
    - x is in the calling function
    - xp is %rbx
*/

bad_read_int:
    push %rbx
    enter $8, $0
    mov %rdi, %rbx

    mov $scanfmt, %rdi
    mov %rbx, %rsi
    mov $0, %al // This is part of the calling convention
                // for a variable argument function. See the ABI docs.
    call scanf 

    addl $4, (%rbx)
    leave
    pop %rbx
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
    enter $16, $0
    mov $prompt, %rdi
    call puts

    lea 0(%rsp), %rdi
    call bad_read_int

    mov $fmt, %rdi
    mov 0(%rsp), %esi
    mov $0, %al
    call printf

    mov $0, %rax
    leave
    ret

    .data
prompt: .string "enter a number"
fmt: .string "we got: %d\n"
