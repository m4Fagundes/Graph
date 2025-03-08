# Graph Cycle Detection

This project implements two different methods for detecting cycles in an undirected graph. The implementation is written in C++ using an adjacency list representation for efficient traversal.

## Methods Implemented

### 1. Cycle Detection Using Recursive Exploration
- Traverses the graph starting from each vertex.
- Expands paths recursively, ensuring they form a closed cycle.
- Normalizes cycles to avoid duplicates.
- Efficient for sparse graphs.

### 2. Cycle Extraction Using Edge Grouping
- Collects all edges and attempts to form cycles by combining them.
- Normalizes cycles to eliminate redundancies.
- Suitable for detecting cycles of a specific size.
- More efficient in highly connected graphs.

## Results
- The implementation correctly detects all cycles in a sample graph with six vertices.
- The recursive method is more efficient for arbitrary cycles.
- The edge-grouping method performs better when filtering for specific cycle sizes.

## Documentation
For more details, refer to the full documentation: [Graph Cycle Detection Documentation](https://www.overleaf.com/read/myynpkpcnpry#09e0ea)
