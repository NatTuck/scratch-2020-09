
// call vs jmp?

// what are "enter" and "leave"?

// jmp label
//   - causes the next instruction
//     executed to be the one after
//     the label, sets the program
//     counter register

// call label
//   - push a return address
//     (instruction after call)

// enter $XX, $0 is the same as:
//   - push %rbp
//   - mov %rsp, %rbp
//   - sub $XX, %rsp
//   - waste 8 clock cycles

// leave is the same as:
//   - mov %rbp, %rsp
//   - pop %rbp


```
foo:
    enter $16, $0

    // body

    leave
    ret

main:
    ...
    call foo
the_add:
    add $1, %rax
```

// Stack:

// - ret addr ($the_add) 
// - old ebp              <- %rbp
// - 16 bytes
//                        <- %rbp

