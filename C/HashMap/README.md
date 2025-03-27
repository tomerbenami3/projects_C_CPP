# 🧩 Generic HashMap in C

This project implements a **generic hash map** (also known as a dictionary or associative array) using **separate chaining with doubly linked lists**. The map stores key-value pairs with user-defined hash and equality functions, providing flexibility to work with any data type.

---

## 🧠 Features

- Store and manage key-value pairs of any type
- Handles hash collisions using **linked lists**
- **Lazy allocation** of buckets for memory efficiency
- Automatically resizes capacity to the **nearest prime number**
- Optional **rehash** support for resizing
- Utility: Stats tracking (in debug mode)

---

## ⚙️ Core Components

- `HashMapCreate()` – Initializes a new hash map
- `HashMapInsert()` – Adds a key-value pair
- `HashMapRemove()` – Removes a key-value pair and retrieves both key and value
- `HashMapFind()` – Finds the value associated with a given key
- `HashMapDestroy()` – Frees the hash map (with optional key/value destructors)
- `HashMapSize()` – Returns the number of stored pairs
- `HashMapForEach()` – Applies a function to all elements (optional)
- `HashMapRehash()` – Rebuilds the table with a new size

---

## 🔧 Required User Functions

You must provide the following when creating the map:
- `HashFunction`: Hashing logic for keys  
- `EqualityFunction`: Key comparison logic  

Optional for `Destroy()`:
- Key/value destroyers to clean up memory correctly

---

## 📊 Debug Stats (Optional)

If compiled with debug mode (`NDEBUG` not defined), you can call:
```c
Map_Stats HashMapGetStatistics(const HashMap* map);
