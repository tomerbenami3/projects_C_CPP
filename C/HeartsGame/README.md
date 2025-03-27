# ♥️ Hearts Card Game in C

This project is a C-based implementation of the classic **Hearts** card game. It supports both real players and computer-controlled opponents, with a complete card deck, round logic, and game flow management.

---

## 🧠 Features

- Full 52-card deck (4 suits, 13 ranks)
- Deck shuffling and card dealing
- Real and machine players support
- Game and round management logic
- Structured and modular code (Cards, Deck, Round, Game)

---

## 📦 Modules Overview

### 🃏 `cards.h`
Defines the `Card` structure:
- `m_rank`: Card rank (0–12 for Ace to King)
- `m_suite`: Card suit (Heart, Spade, Diamond, Club)

```c
typedef struct {
    int m_rank;
    Suite m_suite;
} Card;
