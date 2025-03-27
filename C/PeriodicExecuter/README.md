# ⏱️ Periodic Executor in C

This project implements a **Periodic Executor** in C, which runs tasks at defined time intervals. It's useful for building real-time systems, schedulers, or time-based simulations where functions need to be executed repeatedly at fixed intervals.

---

## 🧠 Features

- Add multiple tasks with individual execution periods
- Each task runs based on a specified delay in milliseconds
- Uses `clock_gettime` with a configurable clock source (`clockid_t`)
- Lightweight and modular design
- Built on top of a custom `Task` module and `Vector` for storage

---

## ⚙️ API Overview

### `PeriodicExecutor* PeriodicExecutor_Create(const char* name, clockid_t clk_id)`
Creates a new periodic executor with a name and a clock type (e.g., `CLOCK_MONOTONIC`).

---

### `void PeriodicExecutor_Destroy(PeriodicExecutor* executor)`
Frees all memory and resources used by the executor.

---

### `int PeriodicExecutor_Add(PeriodicExecutor* executor, TaskFunction task, void* context, size_t period_ms)`
Adds a new task to the executor.

- `task` – function to be executed
- `context` – argument passed to the task
- `period_ms` – execution interval in milliseconds

---

### `size_t PeriodicExecutor_Run(PeriodicExecutor* executor)`
Starts executing all scheduled tasks. Each task runs periodically according to its own defined interval.

- Returns the number of tasks that ran
- Blocks and manages time internally

---

## 📦 Dependencies

- Custom `task.h` module (defines Task and TaskFunction)
- Custom `vector.h` module (dynamic array for managing tasks)
- POSIX `time.h` for clock management

---

## 🧪 Example Use Case

```c
void PrintHello(void* context) {
    printf("Hello %s!\n", (char*)context);
}

PeriodicExecutor* exec = PeriodicExecutor_Create("MyExec", CLOCK_MONOTONIC);
PeriodicExecutor_Add(exec, PrintHello, "World", 1000); // every 1 second
PeriodicExecutor_Run(exec);
PeriodicExecutor_Destroy(exec);
