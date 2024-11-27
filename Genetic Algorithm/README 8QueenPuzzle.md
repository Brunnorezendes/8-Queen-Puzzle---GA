# Genetic Algorithm Solution for the 8-Queens Problem

## Overview

This repository contains two C++ implementations of the Genetic Algorithm (GA) designed to solve the 8-Queens puzzle. The 8-Queens problem requires placing eight queens on a chessboard such that no two queens threaten each other. This involves avoiding conflicts along rows, columns, and diagonals. 

These implementations demonstrate how GAs can solve combinatorial optimization problems by mimicking natural evolutionary processes, such as selection, crossover, and mutation.

## Representation of Solutions

In the GA, each individual (solution) is represented as a **genetic chain** or vector of integers of size 8. The **position** of each integer in the vector represents the **column** on the chessboard, while the **value** of the integer specifies the **row** of the queen in that column.

For example:
[4, 6, 1, 5, 8, 2, 7, 3]

represents a solution where:
- The queen in column 1 is in row 4.
- The queen in column 2 is in row 6.
- The queen in column 3 is in row 1.
- ...

This representation ensures that each column contains exactly one queen, satisfying the column constraint by design. Additional processing ensures that conflicts along rows and diagonals are minimized.

## Implementations

### Specific Algorithm (`GA_8QueenPuzzle_Especific.cpp`)
This implementation assumes that a valid solution to the problem must have exactly one queen per row. This assumption simplifies the genetic representation: the vector is treated as a **permutation** of the numbers 1 to 8, guaranteeing that no two queens share a row.

- **Key Features**:
  - **Ordered Crossover (OX)**: Combines two parents by taking a subsequence from one parent and filling the remaining slots with elements from the other parent, preserving the permutation structure.
  - **Mutation**: Swaps two random positions in the vector to introduce variation while maintaining the permutation.
  - **Fitness Function**: Counts the number of non-attacking queen pairs, with a maximum fitness of 28.

- **Advantages**:
  - The constraint of one queen per row is inherently satisfied, reducing the search space.
  - Faster convergence due to the reduced number of invalid solutions.

### Generic Algorithm (`GA_8QueenPuzzle_Generic.cpp`)
This implementation does not enforce the one-queen-per-row constraint, allowing any combination of rows in the genetic chain. The algorithm relies on crossover and mutation to evolve toward valid solutions.

- **Key Features**:
  - **Single-Point Crossover**: Divides two parent solutions at a random point and swaps segments to create offspring. This method is simpler and does not enforce permutations.
  - **Mutation**: Randomly replaces the value of a gene (queen's row) with another valid row.
  - **Fitness Function**: Counts non-attacking queen pairs, with a maximum of 28.

- **Advantages**:
  - More general and adaptable to other problems where permutation-based constraints do not apply.
  - Explores a larger solution space, which can sometimes help avoid premature convergence.

- **Disadvantages**:
  - Requires additional iterations to eliminate invalid solutions (e.g., multiple queens in the same row).

## Methodology

Both implementations follow the same general Genetic Algorithm framework:

1. **Initialization**:
   - Generate a population of random solutions.
   - In the specific algorithm, solutions are random permutations of numbers 1 to 8.
   - In the generic algorithm, solutions are random vectors with values from 1 to 8.

2. **Evaluation**:
   - Compute the fitness of each solution. The fitness function evaluates the number of non-attacking queen pairs on the board. A solution with a fitness of 28 is considered optimal.

3. **Selection**:
   - Use a fitness-proportional selection (roulette wheel) mechanism. Solutions with higher fitness are more likely to be selected as parents.

4. **Crossover**:
   - Combine selected parents to produce offspring:
     - The specific algorithm uses Ordered Crossover (OX) to maintain the permutation structure.
     - The generic algorithm uses Single-Point Crossover to produce more general offspring.

5. **Mutation**:
   - Introduce random changes to offspring:
     - The specific algorithm swaps two random positions in the vector.
     - The generic algorithm replaces a random gene with a new value.

6. **Termination**:
   - Repeat the above steps until an optimal solution is found (fitness = 28) or the iteration limit is reached.

## Results

The output includes:
- The number of iterations required to find the solution.
- The fitness value of the best solution found.
- The vector representing the positions of the queens.

### Example Output
For the specific algorithm:
Number of Iterations: 128 
Maximum found: 28 
Queen Positions: [4, 6, 1, 5, 8, 2, 7, 3]

For the generic algorithm:
Number of Iterations: 314 
Maximum found: 28 
Queen Positions: [3, 5, 7, 2, 4, 6, 1, 8]

## Conclusion
The specific algorithm is more efficient for the 8-Queens problem due to its tailored design, ensuring one queen per row and reducing the solution space. The generic algorithm, while more flexible, requires additional iterations to refine solutions.

Both approaches illustrate the power of Genetic Algorithms in solving combinatorial optimization problems and provide a foundation for applying GAs to more complex scenarios.
