# THE SYSTEM: HUNTER PROTOCOL
## Master Architecture Document v1.0

```
╔═══════════════════════════════════════════════════════════════════════════════╗
║                                                                               ║
║      "I alone level up." — But first, I build the dungeon.                   ║
║                                                                               ║
╚═══════════════════════════════════════════════════════════════════════════════╝
```

---

## Table of Contents

1. [Vision & Philosophy](#1-vision--philosophy)
2. [The Hunter's Journey](#2-the-hunters-journey)
3. [Technical Architecture](#3-technical-architecture)
4. [Data Model](#4-data-model)
5. [Core Systems](#5-core-systems)
6. [Phase Evolution](#6-phase-evolution)
7. [Repository Structure](#7-repository-structure)
8. [The Pact](#8-the-pact)

---

## 1. Vision & Philosophy

### What Is The System?

The System is a **living training application** that grows alongside its creator. It is not merely a todo app with RPG aesthetics — it is a manifestation of the Hunter Protocol curriculum, built from first principles using only the skills acquired through that same curriculum.

### Core Principles

| Principle | Meaning |
|-----------|---------|
| **Recursive Mastery** | The app is built using skills learned from the app's own training program |
| **No Frameworks Before Understanding** | Every dependency must be understood at the implementation level |
| **Evolution Over Revolution** | The app grows incrementally; we don't rewrite, we *transcend* |
| **The Code Is The Teacher** | Reading this codebase should teach C, systems programming, and GPU engineering |
| **Solo Leveling Philosophy** | Start weak, grind relentlessly, become overwhelming |

### The Ego Mandate (Blue Lock Principle)

This application exists to cultivate an **unbreakable competitive spirit**. Every feature should:

- Challenge the Hunter to push beyond comfort
- Provide immediate, visceral feedback on progress
- Create healthy pressure through visibility and accountability
- Transform failures into fuel for evolution

---

## 2. The Hunter's Journey

### Alignment with Hunter Protocol 2.0

| Protocol Season | Days | App Phase | Technical Focus |
|-----------------|------|-----------|-----------------|
| **Foundation** | 1-60 | Seed | Pure C, terminal I/O, file persistence |
| **Architecture** | 61-105 | Sprout | Data structures, ncurses TUI, modular design |
| **Systems** | 106-165 | Blade | Linux internals, daemons, IPC, networking |
| **Specialization** | 166-210 | Shadow Monarch | GPU acceleration, custom renderer, CUDA effects |

### The Recursive Loop

```
┌─────────────────────────────────────────────────────────────────┐
│                                                                 │
│   ┌─────────────┐      ┌─────────────┐      ┌─────────────┐    │
│   │   LEARN     │ ───▶ │   BUILD     │ ───▶ │    USE      │    │
│   │  (Protocol) │      │  (The App)  │      │  (Training) │    │
│   └─────────────┘      └─────────────┘      └─────────────┘    │
│          ▲                                         │            │
│          └─────────────────────────────────────────┘            │
│                    FEEDBACK LOOP                                │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

## 3. Technical Architecture

### High-Level System Design

```
┌──────────────────────────────────────────────────────────────────────────────┐
│                           THE SYSTEM: HUNTER PROTOCOL                        │
├──────────────────────────────────────────────────────────────────────────────┤
│                                                                              │
│  ┌────────────────────────────────────────────────────────────────────────┐  │
│  │                         PRESENTATION LAYER                             │  │
│  │  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐                 │  │
│  │  │   Terminal   │  │   ncurses    │  │  GPU Render  │                 │  │
│  │  │   (Phase 1)  │  │   (Phase 2)  │  │  (Phase 4)   │                 │  │
│  │  └──────────────┘  └──────────────┘  └──────────────┘                 │  │
│  └────────────────────────────────────────────────────────────────────────┘  │
│                                    │                                         │
│                                    ▼                                         │
│  ┌────────────────────────────────────────────────────────────────────────┐  │
│  │                          CORE ENGINE                                   │  │
│  │  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐                 │  │
│  │  │    Quest     │  │   Hunter     │  │  Progression │                 │  │
│  │  │   Manager    │  │   Profile    │  │    Engine    │                 │  │
│  │  └──────────────┘  └──────────────┘  └──────────────┘                 │  │
│  │  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐                 │  │
│  │  │  Skill Tree  │  │   Shadow     │  │  Achievement │                 │  │
│  │  │   System     │  │   Quests     │  │    Tracker   │                 │  │
│  │  └──────────────┘  └──────────────┘  └──────────────┘                 │  │
│  └────────────────────────────────────────────────────────────────────────┘  │
│                                    │                                         │
│                                    ▼                                         │
│  ┌────────────────────────────────────────────────────────────────────────┐  │
│  │                        PERSISTENCE LAYER                               │  │
│  │  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐                 │  │
│  │  │  Local Save  │  │   Git Sync   │  │  Remote API  │                 │  │
│  │  │   (Binary)   │  │  (Connected) │  │  (Future)    │                 │  │
│  │  └──────────────┘  └──────────────┘  └──────────────┘                 │  │
│  └────────────────────────────────────────────────────────────────────────┘  │
│                                                                              │
└──────────────────────────────────────────────────────────────────────────────┘
```

### Technology Stack Evolution

| Phase | Language | UI Layer | Persistence | Sync | Build System |
|-------|----------|----------|-------------|------|--------------|
| 1 - Seed | C99 | printf/scanf | Binary files | Git commits | Make |
| 2 - Sprout | C99 | ncurses | Structured binary | Git + cron | Make |
| 3 - Blade | C99/C11 | ncurses + daemon | SQLite (optional) | Git + systemd | CMake |
| 4 - Shadow | C++/CUDA | Custom SDL2/Vulkan | Full database | REST API | CMake + CUDA |

### Design Decisions

**Why C first, not C++?**
- Forces understanding of memory at the byte level
- No hidden constructors, destructors, or vtables
- Aligns with Protocol Season 1 (Foundation)
- Makes the C++ transition in later phases meaningful

**Why binary files before SQLite?**
- Teaches file I/O, serialization, and data layout
- No external dependencies in Phase 1
- Builds appreciation for what databases abstract away

**Why Git as sync mechanism?**
- Already part of the workflow
- Human-readable history of progress
- No server infrastructure needed initially
- Natural progression to full sync later

---

## 4. Data Model

### Core Entities

```c
/*
 * hunter.h - The Hunter's identity and progression
 * 
 * This is WHO you are in The System.
 */

#define MAX_NAME_LENGTH 64
#define MAX_TITLE_LENGTH 128

typedef enum {
    RANK_E = 0,
    RANK_D = 1,
    RANK_C = 2,
    RANK_B = 3,
    RANK_A = 4,
    RANK_S = 5,
    RANK_NATIONAL = 6,      /* Special rank for exceptional achievement */
    RANK_SHADOW_MONARCH = 7  /* Final form */
} HunterRank;

typedef struct {
    int strength;      /* STR: Raw C programming power */
    int intelligence;  /* INT: Algorithm and problem-solving */
    int systems;       /* SYS: Linux/OS understanding */
    int gpu;           /* GPU: Graphics and parallel computing */
    int security;      /* SEC: Cybersecurity awareness */
    int endurance;     /* END: Consistency and grinding power */
} HunterStats;

typedef struct {
    char name[MAX_NAME_LENGTH];
    char title[MAX_TITLE_LENGTH];  /* e.g., "Shadow Initiate" */
    
    HunterRank rank;
    HunterStats stats;
    
    unsigned int current_day;      /* Day in the Protocol (1-210+) */
    unsigned int total_xp;
    unsigned int xp_to_next_rank;
    
    time_t protocol_start_date;    /* When the journey began */
    time_t last_activity;          /* For streak tracking */
    
    unsigned int current_streak;   /* Consecutive active days */
    unsigned int longest_streak;
    
    unsigned int quests_completed;
    unsigned int shadow_quests_found;
    unsigned int deaths;           /* Failed challenges - respawn stronger */
} Hunter;
```

```c
/*
 * quest.h - The challenges that forge a Hunter
 */

typedef enum {
    QUEST_TYPE_DAILY,       /* Must complete today */
    QUEST_TYPE_WEEKLY,      /* Weekly capstone */
    QUEST_TYPE_SHADOW,      /* Hidden challenges - bonus rewards */
    QUEST_TYPE_BOSS,        /* Season-ending challenges */
    QUEST_TYPE_SIDE         /* Optional skill expansion */
} QuestType;

typedef enum {
    QUEST_STATUS_LOCKED,    /* Prerequisites not met */
    QUEST_STATUS_AVAILABLE,
    QUEST_STATUS_ACTIVE,
    QUEST_STATUS_COMPLETED,
    QUEST_STATUS_FAILED     /* Death - can retry */
} QuestStatus;

typedef enum {
    SEASON_FOUNDATION = 1,
    SEASON_ARCHITECTURE = 2,
    SEASON_SYSTEMS = 3,
    SEASON_SPECIALIZATION = 4
} ProtocolSeason;

typedef struct {
    unsigned int id;
    char name[128];
    char description[512];
    
    QuestType type;
    QuestStatus status;
    ProtocolSeason season;
    
    unsigned int day_available;    /* When this quest unlocks */
    unsigned int day_deadline;     /* When it expires (0 = no deadline) */
    
    /* Rewards */
    unsigned int xp_reward;
    HunterStats stat_bonuses;
    
    /* Requirements */
    unsigned int required_day;
    HunterRank required_rank;
    unsigned int prerequisite_quest_id;  /* 0 = no prerequisite */
    
    /* Tracking */
    time_t started_at;
    time_t completed_at;
    unsigned int attempts;
} Quest;
```

```c
/*
 * skill_tree.h - The web of knowledge
 */

typedef enum {
    SKILL_DOMAIN_C,
    SKILL_DOMAIN_ARCHITECTURE,
    SKILL_DOMAIN_LINUX,
    SKILL_DOMAIN_GPU,
    SKILL_DOMAIN_SECURITY,
    SKILL_DOMAIN_TOOLING
} SkillDomain;

typedef struct SkillNode {
    unsigned int id;
    char name[64];
    char description[256];
    
    SkillDomain domain;
    unsigned int level;          /* 0-5, where 5 is mastery */
    unsigned int max_level;
    
    unsigned int xp_invested;
    unsigned int xp_to_next_level;
    
    /* Dependencies */
    unsigned int prerequisite_ids[8];
    unsigned int prerequisite_count;
    
    /* Unlocks */
    unsigned int unlocks_quest_ids[8];
    unsigned int unlocks_count;
} SkillNode;
```

### Save File Format (Phase 1)

```c
/*
 * save.h - Binary save file structure
 * 
 * File: ~/.hunter-protocol/save.dat
 * 
 * Format:
 *   [Header: 16 bytes]
 *   [Hunter: sizeof(Hunter)]
 *   [Quest Count: 4 bytes]
 *   [Quests: Quest * count]
 *   [Skill Count: 4 bytes]
 *   [Skills: SkillNode * count]
 *   [Checksum: 4 bytes]
 */

#define SAVE_MAGIC 0x48554E54  /* "HUNT" in ASCII */
#define SAVE_VERSION 1

typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t hunter_offset;
    uint32_t checksum_offset;
} SaveHeader;
```

---

## 5. Core Systems

### 5.1 Progression Engine

The heart of The System. Calculates XP, handles level-ups, and triggers rank advancements.

```
XP Sources:
├── Quest Completion (primary)
│   ├── Daily Quest: 50-100 XP
│   ├── Weekly Capstone: 300-500 XP
│   ├── Shadow Quest: 150-250 XP (bonus)
│   └── Boss Quest: 1000+ XP
├── Streak Bonuses
│   ├── 7-day streak: +10% XP
│   ├── 30-day streak: +25% XP
│   └── 100-day streak: +50% XP
└── Skill Level-ups: 25 XP per level

Rank Thresholds:
├── E → D: 1,000 XP
├── D → C: 3,000 XP
├── C → B: 7,000 XP
├── B → A: 15,000 XP
├── A → S: 30,000 XP
└── S → Shadow Monarch: Complete all Boss Quests
```

### 5.2 Quest Manager

Tracks quest availability, validates completion, and manages the quest tree.

```
Quest Flow:
                    ┌─────────────┐
                    │   LOCKED    │
                    └──────┬──────┘
                           │ Prerequisites met
                           ▼
                    ┌─────────────┐
                    │  AVAILABLE  │
                    └──────┬──────┘
                           │ Hunter accepts
                           ▼
                    ┌─────────────┐
              ┌─────│   ACTIVE    │─────┐
              │     └─────────────┘     │
              │ Success              Failure
              ▼                         ▼
       ┌─────────────┐          ┌─────────────┐
       │  COMPLETED  │          │   FAILED    │
       └─────────────┘          └──────┬──────┘
                                       │ Retry
                                       ▼
                                ┌─────────────┐
                                │   ACTIVE    │
                                └─────────────┘
```

### 5.3 Shadow Quest System

Hidden challenges that appear based on specific triggers:

| Trigger | Shadow Quest |
|---------|--------------|
| Complete 3 quests in one day | "The Grinder" — Bonus stat points |
| Fail a quest 3 times | "Rise from Death" — Persistence reward |
| 7-day streak | "Weekly Warrior" — Streak protection token |
| Find a bug in your own code | "Self-Critique" — INT bonus |
| Help another Hunter (hypothetical) | "Shadow Exchange" — Connection bonus |

### 5.4 Sync System (Git-Based)

```
Sync Flow:
                    ┌─────────────────────────────────────┐
                    │          LOCAL SAVE                 │
                    │     ~/.hunter-protocol/save.dat     │
                    └─────────────────┬───────────────────┘
                                      │
                                      ▼
                    ┌─────────────────────────────────────┐
                    │        EXPORT TO JSON               │
                    │   ~/.hunter-protocol/sync.json      │
                    └─────────────────┬───────────────────┘
                                      │
                                      ▼
                    ┌─────────────────────────────────────┐
                    │          GIT COMMIT                 │
                    │   "Day 003: +150 XP, Quest done"    │
                    └─────────────────┬───────────────────┘
                                      │
                                      ▼
                    ┌─────────────────────────────────────┐
                    │          GIT PUSH                   │
                    │   origin/hunter-progress            │
                    └─────────────────────────────────────┘
```

---

## 6. Phase Evolution

### Phase 1: The Seed (Days 7-30)

**Goal:** Functional terminal application with core loop

**Features:**
- [ ] Display Hunter status
- [ ] Show current day and active quest
- [ ] Mark quests complete
- [ ] Save/load to binary file
- [ ] Basic XP and stat tracking
- [ ] Rank advancement

**Technical Requirements:**
- Pure C99
- Only standard library (stdio, stdlib, string, time)
- Single-file initially, then split into modules
- Makefile for building

**Learning Integrated:**
- File I/O (fopen, fread, fwrite)
- Structs and memory layout
- Enums and type safety
- Basic error handling

**Deliverable:** `hunter` binary that runs in terminal

---

### Phase 2: The Sprout (Days 31-75)

**Goal:** Rich terminal UI with full quest system

**Features:**
- [ ] ncurses-based interface
- [ ] Multiple windows/panels
- [ ] Quest browser and selection
- [ ] Skill tree visualization (ASCII)
- [ ] Progress graphs
- [ ] Keyboard navigation
- [ ] Color theming

**Technical Requirements:**
- ncurses library
- Modular architecture (separate .c/.h files)
- CMake build system
- Unit tests for core logic

**Learning Integrated:**
- Pointers and dynamic memory
- Linked lists (quest chains)
- Hash tables (skill lookup)
- Terminal control sequences

**Deliverable:** Full TUI application with menus

---

### Phase 3: The Blade (Days 76-150)

**Goal:** System integration and networking

**Features:**
- [ ] Background daemon for notifications
- [ ] Desktop notifications (libnotify)
- [ ] Automatic daily sync
- [ ] Import quests from remote source
- [ ] Code exercise validation (compile & run tests)
- [ ] Pomodoro timer integration
- [ ] System tray indicator

**Technical Requirements:**
- Linux daemon architecture
- systemd service file
- D-Bus for IPC (optional)
- libcurl for HTTP
- SQLite for structured data

**Learning Integrated:**
- Process management (fork, exec)
- Signals and IPC
- Network programming basics
- Linux system integration

**Deliverable:** `hunterd` daemon + `hunter` CLI

---

### Phase 4: Shadow Monarch (Days 151-210+)

**Goal:** GPU-accelerated graphical interface

**Features:**
- [ ] Custom renderer (SDL2 or Vulkan)
- [ ] Animated UI transitions
- [ ] Particle effects for achievements
- [ ] 3D skill tree visualization
- [ ] Audio feedback
- [ ] CUDA-accelerated computations
- [ ] Integration with BLOODCODE capstone

**Technical Requirements:**
- C++ for graphics code
- SDL2 or Vulkan
- CUDA toolkit
- OpenGL/Vulkan shaders
- Audio library (SDL_mixer or OpenAL)

**Learning Integrated:**
- GPU architecture
- Shader programming
- Parallel computing (CUDA)
- Real-time rendering

**Deliverable:** Full graphical application

---

## 7. Repository Structure

```
the-system/
├── ARCHITECTURE.md          # This document
├── README.md                 # Project overview
├── CHANGELOG.md              # Version history
├── LICENSE                   # MIT or similar
│
├── docs/
│   ├── QUEST_CATALOG.md      # All available quests
│   ├── SKILL_TREE.md         # Skill definitions
│   ├── DESIGN_DECISIONS.md   # Why we made certain choices
│   └── phases/
│       ├── phase1-seed.md
│       ├── phase2-sprout.md
│       ├── phase3-blade.md
│       └── phase4-shadow.md
│
├── src/
│   ├── phase1/               # Pure C terminal version
│   │   ├── main.c
│   │   ├── hunter.c
│   │   ├── hunter.h
│   │   ├── quest.c
│   │   ├── quest.h
│   │   ├── save.c
│   │   ├── save.h
│   │   ├── display.c
│   │   ├── display.h
│   │   └── Makefile
│   │
│   ├── phase2/               # ncurses TUI version
│   │   └── ...
│   │
│   ├── phase3/               # Daemon + networking
│   │   └── ...
│   │
│   └── phase4/               # GPU-accelerated
│       └── ...
│
├── data/
│   ├── quests/               # Quest definitions (JSON)
│   │   ├── foundation.json
│   │   ├── architecture.json
│   │   ├── systems.json
│   │   └── specialization.json
│   │
│   └── skills/               # Skill tree definitions
│       └── skill_tree.json
│
├── tests/
│   ├── test_hunter.c
│   ├── test_quest.c
│   └── test_save.c
│
├── scripts/
│   ├── sync.sh               # Git sync helper
│   ├── install.sh            # Installation script
│   └── daily_check.sh        # Cron job for reminders
│
└── progress/                 # Synced progress data
    ├── sync.json             # Current state export
    └── history/              # Daily snapshots
        └── day_XXX.json
```

---

## 8. The Pact

### Commitments

By building The System, the Hunter commits to:

1. **Daily Engagement** — Touch the codebase or complete a quest every day
2. **Public Progress** — Push changes regularly; the Git history is the proof
3. **Honest Tracking** — No falsifying completions; the System knows
4. **Continuous Evolution** — The app is never "done" until Day 210+
5. **Teaching Forward** — Document learnings for future Hunters

### The Shadow Monarch's Oath

```
I am the architect of my own dungeon.
I am the boss at the end of my own raid.
I build the System that builds me.

Where others see a tutorial, I see a forge.
Where others see failure, I see fuel.
Where others stop at competence, I demand mastery.

I am the Shadow Monarch.
I alone level up.
```

---

## Appendix A: Quick Start (Phase 1)

Once Phase 1 is ready:

```bash
# Clone the repository
git clone https://github.com/[username]/the-system.git
cd the-system/src/phase1

# Build
make

# Run
./hunter

# First-time setup will initialize your Hunter profile
```

---

## Appendix B: Version History

| Version | Date | Changes |
|---------|------|---------|
| 1.0 | 2025-12-28 | Initial architecture document |

---

```
╔═══════════════════════════════════════════════════════════════════════════════╗
║                                                                               ║
║                    「 END OF ARCHITECTURE DOCUMENT 」                          ║
║                                                                               ║
║                     Protocol Day: 003 | Rank: E                               ║
║                     The journey of 10,000 lines begins                        ║
║                                                                               ║
╚═══════════════════════════════════════════════════════════════════════════════╝
```
