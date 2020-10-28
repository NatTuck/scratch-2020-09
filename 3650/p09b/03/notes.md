

Core i7 8650U

Boosts to 4.2 GHz, round 4GHz, then one cycle is 0.25 ns

Each core can do an add every cycle

```
for (;;) { a += 5; } // 4 billion adds / second
```

To complicate things further, we have 4 ALUs, each of which
can do an add or other simple arithmetic op every cycle

All 4 ALUs can run in parallel if there's work to do that
doesn't have data depenencies.

```
for (;;) { a += 5; b += 5; c += 5; d += 5; } // 16 billion adds / second
```

500 million loop iterations @ 1 clock cycle each


Estimate from instrucitons: Time = 500 M * 0.25 ns = 1/8th of a second

Estimate from RAM throughput: < 1/2 second

Estimate from RAM latency: 

 - If we need to pay 60 ns for each int, then 1B * 60ns = 60s
 - We don't need to pay for each int, because cache operates in cache lines.
   - A cache line is 64B = 16 ints
   - 60s / 16 = 4s

Modern CPUs have a thing called a prefetcher.

 - Attempts to detect load patterns and load data before we need it.

Memory and cache

## System Memory

 - 16 GB
 - Latency is 60ns = 240 clocks
 - Throughput: 20 GB/s

## Processor Caches

 - L3
   - 8 MB (shared)
   - Latency: 11ns = 44 clocks
   - Thoroughput: > 200 GB/s
 - L2
   - 256kB (per core)
   - Latency: 3ns = 12 clocks
   - Thoroughput: > 400 GB/s
 - L1d
   - 32kB (per core)
   - Latency: 1ns = 4 clocks
   - Thoroughput: > 1 TB/s















