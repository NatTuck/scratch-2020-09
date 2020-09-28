
# System Calls

 - The API exposed by the kernel to userspace programs.

# Syscall Argument Registers

 - %rdi
 - %rsi
 - %rdx
 - %r10
 - %r8
 - %r9
 
 ```
     // Call exit syscall
     mov $60, %rax
     mov $0, %rdi
     syscall
 ```
 
## Standard File Descriptors

 - A file descriptor is an integer
 - The kernel, for each running process, has a file descriptor table.
 - Slots are numbered starting at zero, and assigned in ascending order.
 - Every new process starts with some open file descriptors:
   - 0 is stdin (default: reads keys typed on keyboard)
   - 1 is stdout (default: print to screen)
   - 2 is stderr (default: print to screen)
