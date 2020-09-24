
    // xs is %rdx, is a long**
    // ii is %r10

    // xs[0]
    mov 0(%rdx), %rcx

    // xs[0][4]
    mov 0(%rdx), %rcx
    mov 32(%rcx), %rax
    
    // xs[ii][4]
    mov (%rdx,%r10,8), %rcx
    mov 32(%rcx), %rax
