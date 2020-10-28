
Two options for concurrent / parallel execution:

 - Processes with fork()
 - Threads with pthread_create()

Key difference: With threads, all memory shared by default.

 - Advantage: It's conceptually simpler. Some things are simpler, e.g.,
   you can share a vector with threads - harder with processes.
 - Disadvantage: 100% data races

# History

 - Before multi-core systems, parallelism didn't matter.
 - Concurrency was still useful:
   - UNIX: Running multiple programs at once, for multi-user use. This leads
     to processes. Shared system / server type machine.
     - This is *pre-emptive* multi-tasking. One user can't stall another user.
   - On early Windows / Mac systems, concurrency *within* a program was
     represented by threading to support GUIs. Early desktop.
     - This was *cooperative* concurrency. Threads needed to call yield() to let
       other threads run. 
     - Forgetting to put in yields eventually got annoying enough, threads moved
       to being pre-emptive - this happened by the 90's or so.

### Multiprocessors

 - Servers with multiple processor sockets were available mid 90's.
 - Windows and Solaris had good threading support.
 - Linux got good pre-emptive threading support around 2002.
   - The Apache Webserver forked on every incoming request for concurrency.
   - fork() got *super* optimized.
 - Threads under Linux evolved from fork(), so the performance difference is
   small.
 - Windows focused on threads, so they're *much* faster to create than
   processes.
 - Multi-core processors showed up around 2005.
 - Paralell speedup: you want threads
 - Process isolation: you need processes

