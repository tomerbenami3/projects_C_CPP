# 🧠 MyMalloc – Custom Memory Allocator in C

This project implements a **simple memory allocator** (`MyMalloc`) in C, mimicking the behavior of `malloc()` and `free()`, but working within a **user-provided memory buffer**.

---

## 🧩 Features

- Allocate memory blocks from a pre-allocated buffer
- Custom `MyMalloc()` and `MyFree()` functions
- Lightweight and efficient for embedded or constrained systems
- No use of system heap (`malloc/free`) after initialization

---

## ⚙️ API Overview

### `void MyMallocInit(void* memory, size_t memorySize)`
Initializes the memory allocator with a given buffer and size.

### `void* MyMalloc(void* memory, size_t requiredBlockSize)`
Allocates a block of memory from the managed buffer.

- Returns a pointer to the allocated block.
- Returns `NULL` if no sufficient memory is available.

### `void MyFree(void* block)`
Frees a previously allocated block, making it reusable.

> **Note:** This implementation assumes that `block` was previously returned by `MyMalloc()`.

---

## 🧪 Example Use Case

```c
char buffer[1024];
MyMallocInit(buffer, sizeof(buffer));

void* ptr1 = MyMalloc(buffer, 100);
void* ptr2 = MyMalloc(buffer, 50);

MyFree(ptr1);
MyFree(ptr2);
