# lem-in

## The problem
Lem-in is a project where you need to device a clever algorithm that guides variable number ants through a path of interconnected rooms towards a single goal. Only one ant can be in a room at any given time. The problem can be described through graph theory as a maximum flow problem in a graph (g) made of nodes (n) connected by edges (e). The optimization goal is to find the minimum number of steps to get each ant to the end room.

## The solution
Edmonds-Karp algorithm, which uses breath first search (BFS) to find all of the shortest, nonoverlapping paths to the end node and then uses vertex disjoint technique to find the optimal solution by disconnecting some paths and creating new ones.

## Link to visualizer
https://github.com/N1GH7C4P/lem-in_visualizer
