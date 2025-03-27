# 📦 Generic Queue in C

This project provides a simple, flexible implementation of a **generic queue** data structure in C. It supports enqueue and dequeue operations, user-defined actions, and safe memory cleanup with optional destructors.

---

## 🧠 Features

- Generic queue using `void*` to support any data type
- Fixed-size, circular buffer queue
- Safe and lightweight
- Optional cleanup function on destruction
- Traversal support with a custom action callback

---

## ⚙️ API Overview

### `Queue* QueueCreate(size_t size)`
Creates a new queue with a maximum capacity of `size`.

---

### `void QueueDestroy(Queue** queue, DestroyItem destroyFn)`
Destroys the queue and optionally frees elements using a user-provided destructor.

---

### `QueueResult QueueInsert(Queue* queue, void* item)`
Adds an item to the end of the queue.

---

### `QueueResult QueueRemove(Queue* queue, void** outItem)`
Removes the item at the front of the queue and stores it in `outItem`.

---

### `size_t QueueIsEmpty(Queue* queue)`
Returns non-zero if the queue is empty, zero otherwise.

---

### `size_t QueueForEach(Queue* queue, ActionFunction action, void* context)`
Executes `action` on each element in the queue until:
- All items are processed, or
- `action` returns `0`

Returns the number of times `action` was successfully called.

---

## 🚨 Result Codes

| Code                          | Meaning                          |
|-------------------------------|----------------------------------|
| `QUEUE_SUCCESS`               | Operation successful             |
| `QUEUE_UNINITIALIZED_ERROR`   | Queue pointer was NULL           |
| `QUEUE_OVERFLOW_ERROR`        | Queue is full                    |
| `QUEUE_DATA_NOT_FOUND_ERROR`  | No data to remove (empty queue)  |
| `QUEUE_DATA_UNINITIALIZED_ERROR` | NULL item passed to function |

---

## 🧪 Example Use Cases

- Job/task scheduling
- Event queues
- Buffering data between producer/consumer threads
- Reusable FIFO structure in embedded systems

---

## 📄 License

This implementation is free for personal, academic, and embedded system use.
