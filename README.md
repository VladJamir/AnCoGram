# AnCoGram: Nonogram Solver using Constraint Propagation and Ant Colony System

A C++ Nonogram Solver using a Hybrid of Constraint Propagation and Ant Colony System as introduced by (Lloyd & Amos, 2020).

## Build

make -f Makefile

The makefile uses g++ to compile. However, any C++ compiler should work, as long as it supports C++11 standard.

## Command-line arguments

__--file filename__ open puzzle instance in filename

## Example

Solve the crane puzzle.
`./nonogramsolver --puzzle db/crane.txt`