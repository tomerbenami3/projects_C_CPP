# 🔗 Singly Linked List in C

This project implements a basic **singly linked list** in C to manage a dynamic list of `Person` nodes. Each node contains a person's ID, name, age, and a pointer to the next node in the list. The API supports both iterative and recursive operations for insertion, removal, and searching.

---

## 👤 Person Structure

Each node in the list is defined by:

```c
typedef struct Person {
    int m_id;
    char m_name[128];
    int m_age;
    struct Person* m_next;
} Person;
