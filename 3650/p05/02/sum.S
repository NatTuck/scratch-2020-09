    .global main
    .data
//int DATA[] = {1,2,3,4,5,6};
DATA:
    .int 1,2,3,4,5,6
//int SIZE = 6;
SIZE:
    .int 6
debug:
    .string "sum_array(%p,%d)\n"

/*
int
sum_array(int* xs, int nn)
{
    if (nn == 0) {
        return 0;
    }

    if (nn == 1) {
        return xs[0];   // array[index] => *(array + index)
    }

    int mid = nn / 2;
    int y0 = sum_array(xs, mid);
    int y1 = sum_array(xs + mid, nn - mid);
    return y0 + y1;
}
Vars: xs - %r12, nn - %r13, mid - %r14, y0 - %r15, y1 - %rax
*/
    .text
sum_array:
    push %r12
    push %r13
    push %r14
    push %r15
    enter $0, $0
    mov %rdi, %r12
    mov %rsi, %r13

    mov $debug, %rdi
    mov %r12, %rsi
    mov %r13, %rdx
    mov $0, %al
    call printf
    
    mov $0, %rax
    cmp $0, %r13
    je sum_array_done

    mov 0(%r12), %eax   // xs[0] is int, only load 4 bytes
    cmp $1, %r13
    je sum_array_done

    //int mid = nn / 2;
    mov %r13, %r14
    sar $1, %r14

    //int y0 = sum_array(xs, mid);
    mov %r12, %rdi
    mov %r14, %rsi
    call sum_array
    mov %rax, %r15 // e

    //int y1 = sum_array(xs + mid, nn - mid);
    //xs + mid => &(xs[mid])
    lea (%r12,%r14,4), %rdi
    mov %r13, %rsi
    sub %r14, %rsi
    call sum_array

    //return y0 + y1;
    add %r15d, %eax

//Vars: xs - %r12, nn - %r13, mid - %r14, y0 - %r15, y1 - %rax
sum_array_done:
    leave
    pop %r15
    pop %r14
    pop %r13
    pop %r12
    ret

/*
int
main(int _ac, char* _av[])
{
    int sum = sum_array(DATA, SIZE);
    printf("%d\n", sum);
    return 0;
}
*/

main:
    enter $0, $0
    mov $DATA, %rdi
    mov $0, %rsi
    mov SIZE, %esi
    call sum_array

    mov $fmt, %rdi
    mov %eax, %esi
    mov $0, %al
    call printf

    mov $0, %rax
    leave
    ret

.data
fmt: .string "%d\n"
