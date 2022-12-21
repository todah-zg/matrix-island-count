# C++ sample project

## Task
Following our great technical interview session, as a next step we would like to see your code writing skills. The solution should be sent back to us by an email. Here is the problem:
 - Having a matrix of n by m elements. Each of them can be marked or not. In the example shown this is expressed by white (not marked) and red (marked) colors. The numbers inside are just for clearance, and will not be given as an input condition.

 ![matrix illustration](https://github.com/todah-zg/matrix-island-count/blob/master/matrix.png)
 
 - The goal is to find the number of all individual figures, by one figure we mean all colored elements (squares in the matrix) that touch each other by one of their sides. If two cells touch only a vertex (diagonally) and not a common side, they are not considered one figure.
 
For example, for the matrix shown above, the program must give us a "3 figures" solution. The figures themselves are marked with numbers in each square, but only for clarity. It is not necessary for the program to mark the affiliation of the fields as in this case if this will slow down the execution of the algorithm.

### Requirements for the provided solution:
- Used programming language - C ++.
- It is important that the code is written professionally as a commercial software meeting all quality requirements as such. It would be good to consider a scalable solution that would work with large matrices of millions of elements.
- It is of no use to anyone if the algorithm is taken from the Internet, but on the other hand, it is not forbidden to seek knowledge in the problem area if you think it is necessary.

The task does not aim to take too much of your time, the goal is to see how you write production ready code. There is no need (still not forbidden) to further complicate the solution, such as the use of external databases, multi-threaded execution, etc.

## Solution
### Base case
The sample solution creates a simple `Matrix` class that stores data in a 2D int vector and searches for set fields sequentially. When a set element is found, it uses a Breadth First Search (BFS) to quickly find all other connected fields, marking the visited fields so as to avoid processing them again.
This simple approach does not preserve the original state and the matrix is modified during the figure counting process.

### Improvements
To enable correctly preserving the original state, two derived classes are provided that slightly modify the original algorithm and restore the state after the counting process.

Class `FastMatrix` tries to minimize the number of computational steps by sacrificing memory. It creates a copy of the original 2D array and restores it afterwards. Quick testing indicated it is 7% slower than the base case, but still faster then the third option.

Class `LeanMatrix` keeps the original state by going through the matrix again and reverting all the elements that were marked as visited earlier. This increases complexity by extra (row * col) steps. It does not require extra memory but is 11% slower than the base case.

## Unit tests
Some basic unit tests are provided using [GoogleTest](https://google.github.io/googletest/) framework, more as an illustration than as an exhaustive coverage.


## Instructions
1. Make sure you have all of the prerequisites:
    - a compatible operating system (Linux, macOS, Windows)
    - a compatible C++ compiler that supports at least C++14
    - [CMake](https://cmake.org/) and [Make](https://www.gnu.org/software/make/)
2. Clone the project locally (e.g. to the `matrix-project` folder)
3. Setup CMake and fetch dependencies (GoogleTest)
 ```bash
cd matrix-project
cmake -S . -B build
```
4. Build the project
 ```bash
cmake --build build
```
5. Execute the tests
 ```bash
cd build && ctest
```