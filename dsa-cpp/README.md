# DSA in C++

Data structures and algorithms basics, one concept per file. Every file is self-contained
(one `main()` with a demo and expected output in comments), so you can compile and run any
file on its own.

## Structure

| Folder | Files |
|---|---|
| `01_arrays` | static array operations, dynamic array (own vector), binary search, prefix sum + two pointers, bubble/selection/insertion sort |
| `02_linked_lists` | singly, doubly, circular singly, circular doubly, classic problems (middle, cycle, merge, remove n-th from end) |
| `03_stacks` | array stack, linked-list stack, balanced parentheses, infix to postfix + evaluation, next greater element |
| `04_queues` | linear array queue, circular queue, linked-list queue, deque, queue using two stacks |
| `05_trees` | binary tree basics, iterative traversals, binary tree problems, BST, BST problems, AVL tree |
| `06_heaps` | min-heap, max-heap, heap sort, STL priority_queue (k-th largest, merge k sorted lists) |

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

## Conventions
- Variable names are explicit (`previous`, `current`, `toDelete`, not `p`, `c`, `t`).
- Recursive tree functions always have: base case, left subtree, right subtree, return value.
- Time complexity is noted in comments next to the operation.
