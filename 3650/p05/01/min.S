    .global main
    .data
//int xs[] = {10, 100, 2, 90, 3, 180, 4, 70, 5};
//int nn = 10;
xs:
    .int 10, 100, 2, 90, 3, 180, 4, 70, 5
nn:
    .int 10

    .text
/*
// Return the smallest number in the array
// in index range i0 <= ii < i1.
int
min(int* xs, long i0, long i1)
{
    if (i1 - i0 == 1) {
        return xs[i0];
    }

    int mid = (i0 + i1) / 2; // truncate = round down
    int y0 = min(xs, i0, mid);
    int y1 = min(xs, mid, i1);
    return (y0 < y1) ? y0 : y1;
}
Vars:
    - xs - %r12
    - i0 - %rsi
    - i1 - %r13
    - mid - %r14d
    - y0 - %r15d
    - y1 - %eax
    - temp - %rdx
*/

min:
    push %r12
    push %r13
    push %r14
    push %r15
    enter $0, $0
    mov %rdi, %r12
    mov %rdx, %r13

    mov (%r12,%rsi,4), %eax
    sub %rsi, %rdx     // i1 still in rdx
    cmp $1, %rdx
    je min_done

    // General case
    //int mid = (i0 + i1) / 2; // truncate = round down
    mov %rsi, %r14
    add %r13, %r14
    // simulate division by two with bit shift
    sar $1, %r14

    //int y0 = min(xs, i0, mid);
    mov %r12, %rdi
    // i0 is already in %rsi
    mov %r14, %rdx      
    call min
    mov %eax, %r15d

    //int y1 = min(xs, mid, i1);
    mov %r12, %rdi
    mov %r14, %rsi
    mov %r13, %rdx
    call min
    // y1 is in %eax

    //return (y0 < y1) ? y0 : y1;
    cmp %eax, %r15d
    jl return_y0
    jmp min_done

return_y0:
    mov %r15d, %eax
 
min_done:
    // function returns %eax 
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
    int yy = min(xs, 0, nn);
    printf("yy = %d\n", yy);
    return 0;
}
*/
main:
    enter $0, $0
    mov $xs, %rdi
    mov $0, %rsi
    mov $0, %rdx   // zero 64-bits before 32-bit load
    mov nn, %edx   // second arg is long, but nn is int
    call min

    mov $fmt, %rdi
    mov %eax, %esi
    mov $0, %al
    call printf

    mov $0, %rax
    leave
    ret

    .data
fmt:    .string "yy = %d\n"

