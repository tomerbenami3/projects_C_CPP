# 🔺 Generic Heap in C

This project implements a **generic binary heap** (min-heap or max-heap) using a dynamic array (`Vector`). It supports efficient insertion and extraction operations while maintaining heap properties, with full control over element comparison via user-defined functions.

---

## 🧠 Features

- Generic data storage using `void*`
- User-defined "less than" comparator to support min or max heap
- Built on top of an external vector (dynamic array)
- Fast insert, peek, and extract operations
- Optional traversal with user-defined actions

---

## ⚙️ Core Components

### `Heap* HeapBuild(Vector* vector, LessThanComparator compare)`
Creates a heap from an existing vector.

### `HeapResultCode HeapInsert(Heap*, void* element)`
Inserts a new element while maintaining the heap property.

### `void* HeapExtract(Heap*)`
Removes and returns the top element (min or max).

### `const void* HeapPeek(const Heap*)`
Returns the top element without removing it.

### `size_t HeapSize(const Heap*)`
Returns the number of elements in the heap.

### `Vector* HeapDestroy(Heap**)`
Destroys the heap structure and returns the underlying vector.

### `size_t HeapForEach(const Heap*, ActionFunction, void* context)`
Applies a user-defined action to every element in the heap.

---

## ⚠️ Notes

- The **user must manage the underlying vector**: allocate it before calling `HeapBuild()` and free it after `HeapDestroy()`.
- The comparator function defines the heap type:
  - Min-heap: `_left < _right` returns true
  - Max-heap: `_left > _right` returns true

---

## 🚨 Error Codes

| Code                        | Meaning                           |
|-----------------------------|------------------------------------|
| `HEAP_SUCCESS`              | Operation successful               |
| `HEAP_NOT_INITIALIZED`      | Heap pointer is NULL               |
| `ITEN_NOT_INITIALIZED`      | Element is NULL                    |
| `HEAP_REALLOCATION_FAILED`  | Could not grow vector              |
| `HEAP_INDEX_OUT_OF_BOUNDS`  | Accessed invalid index             |
| `HEAP_OVERFLOW`             | Heap is full (rare, dynamic alloc) |
| `HEAP_UNDERFLOW`            | Tried to remove from empty heap    |

---

## 🧪 Example Use Cases

- Task schedulers (priority queues)
- Sorting algorithms (e.g., heap sort)
- Simulation engines
- Graph algorithms (e.g., Dijkstra’s shortest path)

---

## 📄 License

This heap implementation is free to use for academic, learning, or personal projects.
