# Generic Binary Search Tree (BSTree)

This project provides a **generic binary search tree (BST)** data structure in C, designed to store elements of any type using user-defined comparison functions.

It uses a **sentinel-based approach** and supports basic operations such as insertion, deletion, traversal, and custom actions on elements.

---

## Features

- Generic tree using `void*` data
- Prevents duplicate entries
- In-order, pre-order, and post-order traversal support
- Iterator-based API for safe tree navigation
- Utility functions: Mirror, Compare, Depth Calculation, and more

---

## How to Use

1. **Create a tree** using `BSTreeCreate()` with a custom comparator.
2. **Insert elements** with `BSTreeInsert()`.
3. **Iterate and access** elements using tree iterators like `BSTreeItrBegin()`, `BSTreeItrNext()`, etc.
4. **Traverse the tree** with `BSTreeForEach()` and apply custom actions.
5. **Destroy the tree** cleanly using `BSTreeDestroy()`.

---

## Utilities

- `IsFullTree()` – Checks if all nodes have 0 or 2 children.
- `AreSimilarTree()` – Compares two trees for structural similarity.
- `CalcTreeLevel()` – Computes the height (depth) of the tree.
- `MirrorTree()` – Converts the tree to its mirror image.
- `IsPerfectTree()` – Checks if the tree is perfect (all levels filled).

---

## File Overview

- `BSTree.h` – Header file containing the full API and documentation.
- `BSTree.c` – Implementation file (not included here, but expected in the project).

---

## License

This project is free to use and modify for learning or development purposes.
