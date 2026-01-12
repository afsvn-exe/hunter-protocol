# ⚔️ HUNTER PROTOCOL 2.0 — DAY 11: STRINGS DEEP DIVE

```
╔═══════════════════════════════════════════════════════════════════════════╗
║  "Own the abstractions. Implement what you use."                          ║
╚═══════════════════════════════════════════════════════════════════════════╝
```

## 📋 Today's Mission

Implement the core string functions from scratch:
- `strlen` — Count characters until null terminator
- `strcpy` — Copy string including null terminator  
- `strcmp` — Compare strings lexicographically
- `strcat` — Concatenate strings
- **BONUS:** `strrev` — Reverse string in-place
- **BOSS:** `strstr` — Find substring

## 📁 Files

| File | Purpose |
|------|---------|
| `my_string.h` | Header with function declarations and documentation |
| `my_string.c` | Reference implementations (study AFTER attempting) |
| `test_my_string.c` | Comprehensive test suite |
| `exercises.c` | **YOUR WORK** — Empty stubs to implement |
| `Makefile` | Build automation |

## 🛠️ Quick Start

```bash
# Build and run reference tests
make test

# Build and run YOUR exercises  
make exercises

# Run with memory checking (after implementing)
make valgrind

# Clean up
make clean
```

## 📖 Study Order

1. **Read `my_string.h`** — Understand the contracts (preconditions, postconditions)
2. **Open `exercises.c`** — Implement each function without looking at reference
3. **Run `make exercises`** — Test your implementations
4. **If stuck >15 min** — Peek at `my_string.c` for that specific function
5. **Achieve perfect clear** — All tests passing, Valgrind-clean

## 🧠 First Principles

**What is a C string?**
- An array of characters
- Terminated by `'\0'` (null byte, value 0)
- Accessed via pointer to first element
- **NOT a first-class type** — it's a convention!

```
char greeting[] = "Hi";

Memory:  [ 'H' ][ 'i' ][ '\0' ]
Address:  0x100  0x101   0x102
          ↑
       greeting (decays to pointer)
```

## ⚠️ Key Insights

1. **`size_t` for lengths** — String length can't be negative
2. **`const` correctness** — Mark read-only parameters as `const`
3. **`restrict`** — Tell compiler pointers don't overlap (enables optimization)
4. **Cast to `unsigned char`** — For correct comparison ordering
5. **Include the null!** — `strcpy` must copy `'\0'` too

## 🎯 XP Rewards

| Achievement | XP |
|-------------|-----|
| Implement `strlen` | +50 |
| Implement `strcpy` | +50 |
| Implement `strcmp` | +50 |
| Implement `strcat` | +50 |
| Implement `strrev` (bonus) | +100 |
| Implement `strstr` (boss) | +150 |
| All tests passing | +100 |
| Valgrind-clean | +50 |
| **Perfect Clear** | **+600 total** |

## 📚 Reference

- **Effective C, 2nd Ed.** — Chapter 7: Characters and Strings
- **C17 Standard** — §7.24 String handling `<string.h>`

---

*"Every time you call `strlen()`, you're trusting code written decades ago. Today, you wrote that code yourself."*
