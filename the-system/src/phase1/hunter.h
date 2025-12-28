/*
 * hunter.h — The Hunter's Identity and Progression
 * 
 * THE SYSTEM: HUNTER PROTOCOL
 * Phase 1: The Seed
 * 
 * This header defines WHO you are in The System.
 * Every stat, every rank, every achievement lives here.
 * 
 * Learning Focus:
 *   - typedef and struct
 *   - enum for type-safe constants  
 *   - Fixed-size arrays in structs
 *   - Header guards
 * 
 * Reference: Effective C 2nd Ed., Chapter 5 (Types)
 */

#ifndef HUNTER_H
#define HUNTER_H

#include <time.h>      /* For time_t */
#include <stdint.h>    /* For uint32_t, etc. */

/*
 * ============================================================================
 * CONSTANTS
 * ============================================================================
 * 
 * Why #define for these?
 * - Array sizes must be compile-time constants in C99
 * - These values won't change at runtime
 * - Preprocessor substitution is simple and fast
 */

#define MAX_NAME_LENGTH  64
#define MAX_TITLE_LENGTH 128
#define PROTOCOL_DAYS    210

/*
 * ============================================================================
 * ENUMERATIONS
 * ============================================================================
 * 
 * Enums give us type-safe, named constants.
 * Much better than #define for related values.
 * 
 * The explicit values (= 0, = 1, etc.) aren't strictly necessary,
 * but they make the code self-documenting and ensure stability
 * if we later insert new ranks.
 */

/*
 * HunterRank — Your standing in The System
 * 
 * Based on Solo Leveling's ranking system.
 * Most hunters never rise above C-Rank.
 * S-Rank is legendary. Shadow Monarch is myth.
 */
typedef enum {
    RANK_E            = 0,  /* Starting rank — everyone begins here */
    RANK_D            = 1,  /* Basic competence achieved */
    RANK_C            = 2,  /* Solid fundamentals */
    RANK_B            = 3,  /* Professional level */
    RANK_A            = 4,  /* Expert — top 10% */
    RANK_S            = 5,  /* Elite — top 1% */
    RANK_NATIONAL     = 6,  /* Special: exceptional achievement */
    RANK_SHADOW_MONARCH = 7 /* Final form: Protocol complete */
} HunterRank;

/*
 * ============================================================================
 * STRUCTURES
 * ============================================================================
 */

/*
 * HunterStats — The six attributes that define a Hunter's power
 * 
 * Each stat corresponds to a domain of knowledge:
 *   STR (Strength)     — Raw C programming power
 *   INT (Intelligence) — Algorithms, problem-solving, architecture
 *   SYS (Systems)      — Linux, OS internals, low-level understanding
 *   GPU (Graphics)     — GPU architecture, CUDA, parallel computing
 *   SEC (Security)     — Cybersecurity awareness, defensive coding
 *   END (Endurance)    — Consistency, grinding, showing up daily
 * 
 * Stats start at 1 and grow through quest completion.
 * No theoretical maximum, but 100+ is god-tier.
 */
typedef struct {
    int strength;
    int intelligence;
    int systems;
    int gpu;
    int security;
    int endurance;
} HunterStats;

/*
 * Hunter — The complete Hunter profile
 * 
 * This struct is the heart of your save file.
 * It contains everything about your journey.
 * 
 * Memory Layout Notes:
 *   - char arrays are fixed-size (no pointers = no malloc needed yet)
 *   - Structs are laid out in memory in declaration order
 *   - sizeof(Hunter) tells you exactly how many bytes this takes
 * 
 * Why unsigned int for counts?
 *   - These values are never negative
 *   - unsigned gives us a larger positive range
 *   - Signals intent: this is a count, not a delta
 */
typedef struct {
    /* Identity */
    char name[MAX_NAME_LENGTH];
    char title[MAX_TITLE_LENGTH];  /* e.g., "Shadow Initiate", "Gate Breaker" */
    
    /* Progression */
    HunterRank rank;
    HunterStats stats;
    
    /* Protocol Tracking */
    uint32_t current_day;          /* Day in Protocol (1-210+) */
    uint32_t total_xp;
    uint32_t xp_to_next_rank;
    
    /* Timestamps */
    time_t protocol_start_date;    /* When the journey began */
    time_t last_activity;          /* For streak calculation */
    
    /* Streak System */
    uint32_t current_streak;       /* Consecutive active days */
    uint32_t longest_streak;       /* Personal record */
    
    /* Achievement Counters */
    uint32_t quests_completed;
    uint32_t shadow_quests_found;
    uint32_t deaths;               /* Failed challenges — respawn stronger */
    
} Hunter;

/*
 * ============================================================================
 * FUNCTION PROTOTYPES
 * ============================================================================
 * 
 * These are the operations you can perform on a Hunter.
 * Implementations are in hunter.c
 * 
 * Naming Convention:
 *   hunter_<action> — follows a noun_verb pattern
 *   This groups related functions and reads naturally
 */

/*
 * hunter_init — Initialize a new Hunter with starting values
 * 
 * Parameters:
 *   h    — Pointer to Hunter struct to initialize
 *   name — Hunter's chosen name (will be truncated if too long)
 * 
 * Returns:
 *   0 on success
 *  -1 on error (e.g., NULL pointer)
 * 
 * Note: This sets all stats to 1, rank to E, and records start time.
 */
int hunter_init(Hunter *h, const char *name);

/*
 * hunter_add_xp — Award experience points and handle level-ups
 * 
 * Parameters:
 *   h      — Pointer to Hunter
 *   amount — XP to add (always positive)
 * 
 * Returns:
 *   1 if rank increased (level up!)
 *   0 if no rank change
 *  -1 on error
 */
int hunter_add_xp(Hunter *h, uint32_t amount);

/*
 * hunter_add_stats — Increase Hunter's stats
 * 
 * Parameters:
 *   h     — Pointer to Hunter
 *   bonus — Stats to add (can increase multiple at once)
 */
void hunter_add_stats(Hunter *h, const HunterStats *bonus);

/*
 * hunter_update_streak — Update the daily activity streak
 * 
 * Called when Hunter completes any activity.
 * Handles streak continuation and reset logic.
 * 
 * Parameters:
 *   h — Pointer to Hunter
 * 
 * Returns:
 *   Current streak value after update
 */
uint32_t hunter_update_streak(Hunter *h);

/*
 * hunter_get_rank_name — Get human-readable rank name
 * 
 * Parameters:
 *   rank — The rank to name
 * 
 * Returns:
 *   Pointer to static string (do not free!)
 */
const char *hunter_get_rank_name(HunterRank rank);

/*
 * hunter_display — Print Hunter status to stdout
 * 
 * Shows the full status panel.
 * Phase 1: Simple printf
 * Phase 2: ncurses window
 * 
 * Parameters:
 *   h — Pointer to Hunter (const because we don't modify)
 */
void hunter_display(const Hunter *h);

#endif /* HUNTER_H */
