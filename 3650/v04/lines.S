    // Read a file called "msg.txt", count the lines ("\n" characters) in it.


    .global main
    .text

main:
    push %r14  // fd
    push %r15  // size of data in file
    // We're going to read the whole file into a buffer on the stack.
    //  read buffer - 192 bytes - at 0(%rsp)
    //  print buffer - 64 bytes - at 192(%rsp)
    enter $256, $0

    mov $intro, %rdi
    call strlen

    mov $1, %rdi       // fd 1 is stdout
    mov $intro, %rsi   // buffer
    mov %rax, %rdx     // size
    mov $1, %rax       // syscall 1 is write
    syscall

    mov $2, %rax       // open syscall
    mov $file, %rdi
    mov $0, %rsi
    syscall
    mov %rax, %r14     // fd in %r14

    mov $0, %rax       // read syscall
    mov %r14, %rdi
    lea 0(%rsp), %rsi
    mov $192, %rdx
    syscall
    mov %rax, %r15     // size of data in buffer

    mov $0, %rcx       // ii
    mov $0, %rdx       // count of '\n' bytes
loop_cond:
    cmp %r15, %rcx     // ii < size
    jge loop_done

    mov $0, %rax
    mov (%rsp,%rcx,1), %al
    cmp $'\n', %al
    jne loop_next

    inc %rdx

loop_next:
    inc %rcx
    jmp loop_cond

loop_done:
    lea 192(%rsp), %rdi
    mov $fmt, %rsi
    // count is already in %rdx
    mov $0, %al
    call sprintf

    mov $1, %rdi       // 1 = stdout
    lea 192(%rsp), %rsi
    mov %rax, %rdx
    mov $1, %rax       // write syscall
    syscall

    mov $0, %rax
    leave
    pop %r15  // size of data in file
    pop %r14  // fd
    ret

    .data
intro:  .string "lines in msg.txt:\n"
file:   .string "msg.txt"
fmt:    .string "lines = %ld\n"
