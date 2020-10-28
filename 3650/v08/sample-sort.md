
# Merge Sort

## No work on the way down, splitting is "free"

    3 5 22 9 35 61 2            <- sequential split
    [ 3 5 9 22 ] | [ 2 35 61 ]  <- sequential merge
    
    3 5 22 9 | 35 61 2          <- split two things in two processes
    [ 3 5 ] | [ 9 22 ] | [35 61] | [ 2 ]   <- merge 4 to 2 in two processes
   
    3 5 | 22 9 | 35 61 2
    
    3 | 5 | 22 9 | 35 61 2

## We do the work on the way back up

    [ 3 5 ] | 22 9 | 35 61 2
    
    [ 3 5 ] | 22 | 9 | 35 61 2
    
    [ 3 5 ] | [ 9 22 ] | 35 61 2
    
    [ 3 5 ] | [ 9 22 ] | 35 61 | 2
    
    [ 3 5 ] | [ 9 22 ] | 35 | 61 | 2
    
    [ 3 5 ] | [ 9 22 ] | [35 61] | [ 2 ]
 
    [ 3 5 9 22 ] | [ 2 35 61 ]

## Merge Sort Analysis

 - Total levels of recursion is log(N)
 - 1 + 2 + ... + log(N)
 - Sort a million items, log2(a million) = 30
 

# Quick sort


## We do the work on the way down

    3 5 22 9 35 61 2  <- input
    3 5 2 [9] 35 61 22  <- partitioned array
   
    3 5 2  |  35 61 22  <- recurse on left and right half

    ...

    2 | 3 | 5 | 9 | 22 | 35 | 61 <- bottom level of recursion
    
    2 | 3 | 5 | [9] | 22 | 35 | 61 <- optimal one pivot
    
    2 | [3] | 5 | [9] | 22 | [35] | 61 <- optimal three pivots
    


## No work after returning from recursive calls

  - Nothing to do
  
## Parallelizing Quick Sort

 - We can pick more than one pivot.
 - We can do out-of-place parititioning in parallel, up to (# of pivots + 1)
   processes.

 - Problem: To get a good parallel speedup, we need to pick "the right" pivots.
 - Solution: Just look at the array to find good pivots. We don't need to look
   at the whole input array, just a representative sample. With a large input,
   looking at 1% of the input is plenty to find good pivots.








