# 📅 Diary Management System (Appointments Scheduler)

A simple C-based **Diary Management System** that allows users to manage meetings efficiently. This includes creating, inserting, removing, saving, and loading meetings, all while preventing overlapping appointments.

---

## 🧠 Features

- Create and manage multiple meetings
- Prevents time overlaps
- Save/load diary to/from a file
- Dynamically resizable internal storage
- Print entire diary or individual meetings

---

## 🛠️ Core Structures

### 🧾 `Meeting`
Stores data about a single meeting:
- `startTime` – float
- `endTime` – float
- `room` – int

### 📔 `DiaryManagement`
Represents the diary:
- Dynamically resizable array of `Meeting*`
- Tracks size, capacity, and number of meetings

---

## ⚙️ Available Functions

| Function | Description |
|---------|-------------|
| `DiaryManagementCreate(size, blockSize)` | Creates a new diary |
| `CreateMeeting(startTime, endTime, room)` | Creates a meeting |
| `InsertMeetingToAD(diary, meeting)` | Inserts a meeting (no overlap allowed) |
| `RemoveMeeting(diary, startTime)` | Removes a meeting by start time |
| `FindAppointment(diary, startTime)` | Searches for a meeting |
| `DestroyAD(diary)` | Frees all memory and meetings |
| `SaveToFile(diary, filename)` | Saves all meetings to a file |
| `LoadfromFile(diary, filename)` | Loads meetings from a file |
| `PrintAD(diary)` | Prints all meetings |
| `PrintMeeting(meeting)` | Prints a single meeting |

---

## ⚠️ Error Codes

| Code | Meaning |
|------|---------|
| `OK` | Success |
| `NULL_ERROR` | Null pointer passed |
| `REALOC_FAILED` | Memory reallocation failed |
| `OVERFLOW` | Insertion beyond capacity |
| `UNDERFLOW` | Attempt to remove from empty |
| `FILE_ERROR` | File read/write issue |
| `NOT_FOUND` | Meeting not found |

---

## 📄 License

This project is free to use for learning, assignments, or personal organization.
