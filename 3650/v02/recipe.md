
# How to write an Assembly Program

## Design Recipe for Assembly Programs

 - An assembly (or C) program is a collection of functions
 - Figure out at least some of the functions we need.
 
(Hint: you need a "main" function, start there.)

 - Apply the recipie for functions below to write them.
 - As you discover new functions, write those too.

## Design Recipie for an Assembly Function

### Step 1: Signature

This is always a good place to start.

Figure out # of args, types, and return type.

### Step 2: Pseudocode

Thinking in assembly is difficult.

Writing pseudocode can just mean writing almost-working C.

### Step 3: Variable Mappings

Pseudocode has named variables, assembly does not.

For each variable (or temporary value) in the pseudocode, decide where it lives.

 - Register? Which one.
 - On the stack? Where.
 - Global variable? What label.

You should explicitly write down this mapping as a comment in your assembly code.

Which registers:

 - There are two pure temporary registers: %r10 and %r11
   - Temporaries go bad if you call a function.
 - There are five available safe registers: %rbx, %r12-%r15
   - These are safe across function calls.
   - You need to preserve the value of your caller.
 - The first six arguments go in: %rdi, %rsi, %rdx, %rcx, %r8, %r9
   - These are temporaries.
   - If a value is already in one of these, you might be able to leave it there.
   - Remember that %rdx sometimes gets clobbered (e.g. by idiv)
 - The return value of a function goes in %rax
   - This a temporary.
   - Remember that %rax sometimes gets clobbered (e.g. by idiv)

### Step 4: Function Skeleton

```
label:
    // Prologue:
    // push callee-save (safe) registers
    enter ??, $0
    // Stack alignment: 
    // - 8*(# of safe registers) + (bytes requested in enter) / 16
    //   must be an integer

    /* TODO: function body */

    leave
    // Epilogue:
    // pop callee-save (safe) registers in reverse order from pushes
    ret
```

### Step 5: Write the Function Body

Translate your pseudocode to assembly.

Refer to your variable mapping.

Translating C to ASM is a mechanical process - literally, that's what compilers
do.


## Examples of Translation

### Variables, Temporaries, and Assignments


```
int a = 5;
int b = 3 * a + 1;
```

Mappings:

 - a = 0(%rsp)
 - b = 8(%rsp)
 - extra temporary is %rax

```
// int a = 5;
movq $5, 0(%rsp)

// int b = 3 * a + 1;
mov 0(%rsp), %rax
imul $3
inc %rax
mov %rax, 8(%rsp)
```

### If

```
if (a < 7) {
    b++;
}
```

Mappings:

 - a is %rax
 - b is %rbx

```
// if (a < 7) {
  cmp $7, %rax 
  jge skip_body
// b++;
  inc %rbx
skip_body:
```

 - While
 - For
 - Do / While
 





