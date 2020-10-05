

# Search Problems

 - Some search space
 - Trying to find something
 - Subset, path, optimization ....

## Kerbal Moon Tour

Problem 1: Define the search space

 - Idea 1: Just looking for a visitation order.
      { Mun, Minmus } => { { Mun, Minmus }, { Minmum, Moon } }
      P(set of size N) = N!/(N-r)! = (r=N) = N!
      { 5 moons of Jool } = 5! = 120 orders
 - Idea 2: Look for a visitation order, considering multiple 
   inter-moon trajectoires. i.e., do we circularize at a low
   planetary orbit or not. Which low orbit?

Problem 2: Find a strategy to solve it

 - Idea 1: Enumerate them all (the orders), pick the best one.
 - Generalization: Optimization problem.

What is best?

 - Among possible plans, which one has the best score?
 - Best score = lowest in-game time.

Problem 3: Solve it

 - It's possible to create "fake" orbits in Kerboscript and then
   operate on them.


## Knapsack Problem

You've broken into the bank vault and broken open 
all the safe deposit boxes.

There are a bunch of objects, each with a resale value
and a volume. Which one should you steal.

Your backpack only holds 1 cubic meter.

Simplifying assumption: All the objects can be squished
so shape doesn't matter.

This is NP-complete. To get a perfect solution, need to
test all permutations. 





