# 📐 Generic Vector (Dynamic Array) in C

This project implements a **generic, resizable vector (dynamic array)** in C using `void*`, allowing it to store elements of any type. It supports dynamic resizing, safe access, and element-wise iteration with user-defined actions.

---

## 🧠 Features

- Dynamically grows and shrinks based on usage
- Stores generic elements using `void*`
- Optional fixed-size behavior (when `blockSize == 0`)
- Supports `append`, `remove`, `get`, `set` operations
- Safe destruction with optional element cleanup
- Element-wise iteration with a user callback

---

## ⚙️ API Overview

### Creation & Destruction

| Function | Description |
|---------|-------------|
| `VectorCreate(initialCapacity, blockSize)` | Creates a new vector |
| `VectorDestroy(&vector, destroyFunc)` | Frees memory, with optional cleanup for items |

---

### Basic Operations

| Function | Description |
|----------|-------------|
| `VectorAppend(vector, item)` | Adds item to the end of the vector |
| `VectorRemove(vector, &outItem)` | Removes item from the end of the vector |
| `VectorGet(vector, index, &outItem)` | Gets item at `index` (1-based) |
| `VectorSet(vector, index, item)` | Replaces item at `index` |
| `VectorSize(vector)` | Returns the number of elements stored |
| `VectorCapacity(vector)` | Returns the total allocated capacity |

---

### Iteration

| Function | Description |
|----------|-------------|
| `VectorForEach(vector, actionFn, context)` | Calls `actionFn` on every item until it returns `0` or finishes |

Example usage:
```c
int PrintElement(void* elem, size_t index, void* ctx) {
    printf("Index %zu: %d\n", index, *(int*)elem);
    return 1;
}
VectorForEach(myVector, PrintElement, NULL);
