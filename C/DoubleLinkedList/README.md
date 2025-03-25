# 🔁 Generic Doubly Linked List (DList)

This project implements a **generic doubly linked list** in C using void pointers, allowing you to store and manipulate any data type. The API provides full control over list traversal, insertion, removal, and iteration with custom user-defined functions.

---

## 🧠 Features

- Add/remove elements from both head and tail (O(1))
- Iterator-based access and traversal
- Safe insert/remove operations via iterators
- Custom actions via callback functions
- Utility functions like size check, emptiness check, and ranged iteration

---

## ⚙️ Core Concepts

### `List`
- Main doubly linked list structure (opaque).

### `ListItr`
- Opaque iterator used for safe list navigation and element access.

### `ListActionFunction`
- User-defined function to perform actions on list elements.

---

## 🔧 Available Functions

### 🔨 Creation & Destruction
- `List* ListCreate()` – Create a new list
- `void ListDestroy(List** list, void (*destroyFunc)(void*))` – Destroy list and optionally its contents

### ➕ Insertion
- `ListItr ListPushHead(List*, void*)`
- `ListItr ListPushTail(List*, void*)`
- `ListItr ListItrInsertBefore(ListItr, void*)`

### ➖ Removal
- `void* ListPopHead(List*)`
- `void* ListPopTail(List*)`
- `void* ListItrRemove(ListItr)`

### 🎯 Iterators & Access
- `ListItr ListItrBegin(List*)` / `ListItr ListItrEnd(List*)`
- `ListItr ListItrNext(ListItr)` / `ListItr ListItrPrev(ListItr)`
- `int ListItrEquals(ListItr, ListItr)`
- `void* ListItrGet(ListItr)` / `void* ListItrSet(ListItr, void*)`

### 🧰 Utilities
- `size_t ListSize(List*)`
- `size_t ListIsEmpty(List*)`
- `ListItr ListItrForEach(ListItr begin, ListItr end, ListActionFunction, void* context)`

---

## 🧪 Example Use Cases
- Implementing stacks, queues, or deques
- Custom containers for any data type
- Processing data in both directions with iterators

---

## 📄 License

Free to use for educational and personal projects.
