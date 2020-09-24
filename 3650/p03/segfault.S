    .global main
    .text


main:
    enter $0, $0
   
    mov $494387, %rdx
    mov (%rdx), %rax

    leave
    ret
