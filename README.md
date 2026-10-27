# DSA in C++

[![build](https://github.com/DivyanBabbar/Dsa-cpp/actions/workflows/build.yml/badge.svg)](https://github.com/DivyanBabbar/Dsa-cpp/actions/workflows/build.yml)

Data structures and algorithms basics, one concept per file. Every file is self-contained
(one `main()` with a demo and expected output in comments), so you can compile and run any
file on its own.

## Structure

| Folder | Files |
|---|---|
| `01_arrays` | static array operations, dynamic array (own vector), binary search, prefix sum + two pointers, bubble/selection/insertion sort, LeetCode 238 product of array except self, LeetCode 11 container with most water |
| `02_linked_lists` | singly, doubly, circular singly, circular doubly, classic problems (middle, cycle, merge, remove n-th from end), LeetCode 2 add two numbers |
| `03_stacks` | array stack, linked-list stack, balanced parentheses, infix to postfix + evaluation, next greater element, LeetCode 155 min stack |
| `04_queues` | linear array queue, circular queue, linked-list queue, deque, queue using two stacks, LeetCode 994 rotting oranges |
| `05_trees` | binary tree basics, iterative traversals, binary tree problems, BST, BST problems, AVL tree, LeetCode 199 right side view |
| `06_heaps` | min-heap, max-heap, heap sort, STL priority_queue (k-th largest, merge k sorted lists), LeetCode 347 top k frequent elements |
| `07_hashing` | hash table with chaining (+ resize), hash table with linear probing (tombstones), hash map problems (two sum, first non-repeating char, subarray sum = k, longest consecutive run), LeetCode 49 group anagrams |
| `08_graphs` | adjacency matrix vs list, BFS + DFS (+ distances, connected components), Kruskal's MST (union-find), Prim's MST (min-heap), LeetCode 200 number of islands, LeetCode 207 course schedule (topological sort) |

## Run a single file

Windows (PowerShell):
```powershell
g++ -std=c++17 01_arrays\01_static_array_operations.cpp -o static_array.exe
.\static_array.exe
```

Linux / macOS / WSL:
```bash
g++ -std=c++17 01_arrays/01_static_array_operations.cpp -o static_array
./static_array
```

## Build everything

Windows: `.\build_all.ps1` (output in `build\`)
Linux / macOS / WSL: `make`

## CI
Every push compiles all files with `-Wall -Wextra -Werror` plus AddressSanitizer/UBSan and runs them, so a memory leak or warning fails the build.

## Conventions
- Variable names are explicit (`previous`, `current`, `toDelete`, not `p`, `c`, `t`).
- Recursive tree functions always have: base case, left subtree, right subtree, return value.
- Time complexity is noted in comments next to the operation.
