
# Upcoming: Parallel Sort with Threads

## Test CPU

Core i7-8650U

Expected single-thread clock speed: 4 GHz

Each clock cycle takes how long? 1 / a billion = 1 ns; so 0.25 ns

We can do an add in one clock cycle, so:

```
for (;;) { a += 5; }  // 4 billion adds / second
```

But, the CPU actually has 4 ALUs (Arithmetic Logic Units)

Each one can do an arithmethic instruction per clock, as long
as it doesn't depend on data from another ALU

```
for (;;) { a += 5; b += 5; c += 5; d += 5; }  // 16 billion adds / second
```

Instructions as fast as add: sub, bitwise ops (&, |, ^), others.


# Test Memory

System Memory:

  - 16 GB
  - Latency: 60ns = 240 clocks
  - Throughput: 20 GB/s

Cache:

  - L3
  - 8 MB (shared)
  - Latency: 11ns = 44 clocks
  - Throughput: > 200 GB/s

  - L2
  - 256 KB (per core)
  - Latency: 3ns = 12 clocks
  - Throughput: > 400 GB/s

  - L1 Data
  - Size: 32 KB (per core)
  - Latency: 1ns = 4 clocks
  - Throughput: > 1 TB/s




