    .global main
    .data
/*
long xs[] = {1, 22, 2, 21, 3, 20, 4, 29, 5, 18, 6, 17};
long nn = 12;
*/
xs:
    .int 1, 22, 2, 21, 3, 2
    .int 4, 29, 5, 18, 6, 17
nn:
    .int 12

    .text
// Find the maximum value in the array xs
// in array indexes i0 <= ii < i1
/*
long
max(long* xs, long i0, long i1)
{
    if (i1 - i0 == 1) {
        return xs[i0];
    }
    
    long mid = (i0 + i1) / 2;
    long y0 = max(xs, i0, mid);
    long y1 = max(xs, mid, i1); 
    return (y0 > y1) ? y0 : y1;
}
Vars:
    - xs - %r12
    - i0 - %rsi
    - i1 - %r13
    - mid - %r14
    - y0 - %r15
    - y1 - %rax
    - (i0 - i1) - %rdx
*/

max:
    push %r12 
    push %r13 
    push %r14 
    push %r15 
    enter $0, $0
    mov %rdi, %r12
    mov %rdx, %r13 

    mov (%r12,%rsi,4), %eax
    //if (i1 - i0 == 1) {
    sub %rsi, %rdx  // can't use r13, since we want to keep that
    cmp $1, %rdx
    je max_done

    //long mid = (i0 + i1) / 2;    // r14, rsi, r13
    mov %rsi, %r14
    add %r13, %r14
    sar $1, %r14      // should be %r14 /= 2

    //long y0 = max(xs, i0, mid);
    mov %r12, %rdi
    //mov %rsi, %rsi
    mov %r14, %rdx
    call max
    mov %rax, %r15

    //long y1 = max(xs, mid, i1); 
    mov %r12, %rdi
    mov %r14, %rsi
    mov %r13, %rdx
    call max
    // y1 is %rax

    /*
    mov %rax, %rbx
   
    mov %rax, %rdi
    mov %r15, %rsi
    call print2

    mov %rbx, %rax
    */

    //return (y0 > y1) ? y0 : y1;
    cmp %eax, %r15d
    jg y0_bigger
    // y0 not bigger
    // return y1
    jmp max_done
y0_bigger:
    mov %r15, %rax

max_done:
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
    long yy = max(xs, 0, nn);
    printf("Max of array is: %ld\n", yy);
}
*/

// in C, "string" means "char*"

main:
    enter $0, $0
    mov $xs, %rdi
    mov $0, %rsi
    mov $0, %rdx
    mov nn, %edx
    call max

    // max(xs, 0, nn)
    // max(xs, 0, &nn)

    mov $fmt, %rdi
    mov %rax, %rsi
    mov $0, %al
    call printf
    
    mov $0, %rax
    leave
    ret

    .data
fmt:    .string "Max of array is: %d\n"
