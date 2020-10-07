
Windows doesn't have fork / exec.

Instead, it has one system call: 

   CreateProcess(..., const char* path, ....);
   // - Create a new process.
   // - Load the program at path to run in that process.
   
Why use fork/exec over CreateProcess?

Being able to call just fork gives some additional options:

 - fork can be used for parallel / concurrent execution
 - multiple processes can be used for other stuff, e.g. security 

Exec without fork can also be useful.


# Bitwise OR for flags

Example flags:

```
  O_WRONLY = 1
  O_APPEND = 2
  O_CREAT  = 4
  
  int x = O_WRONLY | O_APPEND; // ( == 3 )
 
  if (x & O_WRONLY) { // true only of O_WRONLY was set
```
