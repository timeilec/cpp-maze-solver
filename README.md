# Maze Solver

## What is the Maze Solver?

The Maze Solver allows you to input a maze of any dimensions and will use my recursive backtracking algorithm to find a solution to get from the top left (start) square to the bottom right (end) square. The maze will be solved randomly every time the program is run, unless a generation seed is supplied with the command line parameters.

## Steps to use:
1. Compile the C++ file
2. Run the executable with command line parameters for: number of rows, number of columns, and (optional) seed value

Example compilation command on Mac/Linux:
```
g++ -std=c++17 maze-solver.cpp -o maze-solver
```


Example execution command on Mac/Linux (no seed):
```
./maze-solver 15 20
```

Example execution command on Mac/Linux (with seed):
```
./maze-solver 15 20 51931
```
