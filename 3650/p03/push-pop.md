
## When to use Push, Pop

 - To save the value of safe registers in a function
   prologue / epilogue. Following the "callee-save"
   convention.

```
label:
    push
    push
    enter

    leave
    pop
    pop
    ret
```
 
 - To save the values of temporary registers around a
   function call using the "caller-save" convention.
   (I recommend avoiding this, but it's valid.)

```
label:
    enter

    ...
    mov $10, %r10
    push %r10
    // align stack
    call foo
    pop %r10

    (use %r10)
    ...

    leave
    ret
```

  - For your own logic there may be additional uses
    of push / pop, but the normal patterns never require
    it.

