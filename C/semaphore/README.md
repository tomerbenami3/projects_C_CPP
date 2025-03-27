# 🔄 Producer-Consumer Problem in C (Multithreading)

This project implements the classic **Producer-Consumer** problem using **POSIX threads (pthreads)**, a **circular buffer**, and **mutex/condition variables** for safe synchronization between threads.

---

## 🧠 Description

Two threads are created:
- **Producer**: Adds items to a shared buffer.
- **Consumer**: Removes items from the buffer.

The buffer has a fixed size (`BUFFER_SIZE`) and follows **FIFO** logic using a **circular array**. Proper synchronization ensures that:
- The producer waits when the buffer is full.
- The consumer waits when the buffer is empty.

---

## ⚙️ Features

- Circular buffer implementation
- Mutex to protect shared state
- Condition variables to signal state changes
- Controlled production and consumption count
- No busy-waiting

---

## 🧩 Key Variables

| Name              | Purpose                                      |
|-------------------|----------------------------------------------|
| `buffer[]`        | Shared buffer between producer and consumer  |
| `in`, `out`       | Indexes to insert/remove items               |
| `produced_count`  | Number of items produced                     |
| `consumed_count`  | Number of items consumed                     |
| `mutex`           | Protects buffer and counters                 |
| `full`, `empty`   | Condition variables to block/wake threads    |

---

## 🛠️ Compilation & Run

```bash
gcc -pthread -o producer_consumer main.c
./producer_consumer
