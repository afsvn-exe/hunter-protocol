/*
 * hunter.c — Hunter Implementation
 * 
 * THE SYSTEM: HUNTER PROTOCOL
 * Phase 1: The Seed
 * 
 * This file implements the Hunter-related functions declared in hunter.h.
 * 
 * Learning Focus:
 *   - Implementing functions from declarations
 *   - Working with structs through pointers
 *   - String handling with strncpy
 *   - Time functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hunter.h"

/*
 * ============================================================================
 * RANK DATA
 * ============================================================================
 */

/*
 * Rank names — static array for lookup
 * 
 * Using an array indexed by enum value is a common pattern.
 * Much faster than a switch statement for simple lookups.
 */
static const char *RANK_NAMES[] = {
    "E-Rank",
    "D-Rank",
    "C-Rank",
    "B-Rank",
    "A-Rank",
    "S-Rank",
    "National Level",
    "Shadow Monarch"
};

/*
 * XP thresholds for each rank
 * 
 * XP_THRESHOLDS[rank] = XP needed to reach that rank
 * E-Rank starts at 0 (everyone begins there)
 */
static const uint32_t XP_THRESHOLDS[] = {
    0,       /* E-Rank: starting point */
    1000,    /* D-Rank */
    3000,    /* C-Rank */
    7000,    /* B-Rank */
    15000,   /* A-Rank */
    30000,   /* S-Rank */
    50000,   /* National Level */
    100000   /* Shadow Monarch */
};

#define NUM_RANKS (sizeof(XP_THRESHOLDS) / sizeof(XP_THRESHOLDS[0]))

/*
 * ============================================================================
 * HUNTER FUNCTIONS
 * ============================================================================
 */

int hunter_init(Hunter *h, const char *name)
{
    /*
     * Defensive programming: always check for NULL pointers.
     * This prevents crashes from programmer errors.
     */
    if (h == NULL || name == NULL) {
        return -1;
    }
    
    /*
     * memset zeros the entire struct.
     * This ensures no garbage values from uninitialized memory.
     * 
     * sizeof(*h) is a common pattern — it works even if the type changes.
     */
    memset(h, 0, sizeof(*h));
    
    /*
     * strncpy is safer than strcpy — it won't overflow the buffer.
     * But it has a quirk: it doesn't guarantee null-termination
     * if the source is too long. So we manually ensure it.
     */
    strncpy(h->name, name, MAX_NAME_LENGTH - 1);
    h->name[MAX_NAME_LENGTH - 1] = '\0';
    
    /* Default title for new Hunters */
    strncpy(h->title, "Shadow Initiate", MAX_TITLE_LENGTH - 1);
    h->title[MAX_TITLE_LENGTH - 1] = '\0';
    
    /* Starting rank */
    h->rank = RANK_E;
    
    /*
     * All stats start at 1.
     * Zero would mean "no ability at all" which doesn't make sense
     * for someone who has begun training.
     */
    h->stats.strength = 1;
    h->stats.intelligence = 1;
    h->stats.systems = 1;
    h->stats.gpu = 1;
    h->stats.security = 1;
    h->stats.endurance = 1;
    
    /* Protocol day 1 */
    h->current_day = 1;
    
    /* XP to reach D-Rank */
    h->xp_to_next_rank = XP_THRESHOLDS[RANK_D];
    
    /*
     * time(NULL) returns current time as seconds since Unix epoch.
     * We store this to calculate things like streak length.
     */
    h->protocol_start_date = time(NULL);
    h->last_activity = time(NULL);
    
    /* Fresh start, no streaks yet */
    h->current_streak = 1;  /* First day counts! */
    h->longest_streak = 1;
    
    return 0;
}

int hunter_add_xp(Hunter *h, uint32_t amount)
{
    int ranked_up = 0;
    HunterRank new_rank;
    
    if (h == NULL || amount == 0) {
        return -1;
    }
    
    /* Add XP */
    h->total_xp += amount;
    
    /*
     * Check for rank-up.
     * We loop because a large XP gain could skip multiple ranks
     * (though that would be unusual).
     */
    new_rank = h->rank;
    while (new_rank < RANK_SHADOW_MONARCH && 
           h->total_xp >= XP_THRESHOLDS[new_rank + 1]) {
        new_rank++;
        ranked_up = 1;
    }
    
    if (ranked_up) {
        h->rank = new_rank;
        
        /* Update XP target for next rank */
        if (new_rank < RANK_SHADOW_MONARCH) {
            h->xp_to_next_rank = XP_THRESHOLDS[new_rank + 1];
        } else {
            h->xp_to_next_rank = h->total_xp; /* Max rank reached */
        }
        
        return 1; /* Indicate rank-up occurred */
    }
    
    return 0;
}

void hunter_add_stats(Hunter *h, const HunterStats *bonus)
{
    if (h == NULL || bonus == NULL) {
        return;
    }
    
    /*
     * Simple addition. Stats have no maximum in Phase 1.
     * Later phases might add diminishing returns or caps.
     */
    h->stats.strength += bonus->strength;
    h->stats.intelligence += bonus->intelligence;
    h->stats.systems += bonus->systems;
    h->stats.gpu += bonus->gpu;
    h->stats.security += bonus->security;
    h->stats.endurance += bonus->endurance;
}

uint32_t hunter_update_streak(Hunter *h)
{
    time_t now;
    double diff;
    
    if (h == NULL) {
        return 0;
    }
    
    now = time(NULL);
    
    /*
     * difftime returns the difference in seconds as a double.
     * We check if more than 48 hours have passed (broken streak)
     * or less than 24 hours (same day, no change).
     */
    diff = difftime(now, h->last_activity);
    
    if (diff > 48 * 60 * 60) {
        /* More than 48 hours — streak broken */
        h->current_streak = 1;
    } else if (diff > 24 * 60 * 60) {
        /* Between 24-48 hours — streak continues */
        h->current_streak++;
        if (h->current_streak > h->longest_streak) {
            h->longest_streak = h->current_streak;
        }
    }
    /* Less than 24 hours — same day, no streak change */
    
    h->last_activity = now;
    return h->current_streak;
}

const char *hunter_get_rank_name(HunterRank rank)
{
    /*
     * Bounds check to prevent array overflow.
     * If someone passes an invalid rank, return a safe default.
     */
    if (rank < 0 || rank >= (int)NUM_RANKS) {
        return "Unknown";
    }
    
    return RANK_NAMES[rank];
}

void hunter_display(const Hunter *h)
{
    if (h == NULL) {
        printf("Error: No hunter data\n");
        return;
    }
    
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║  HUNTER: %-20s  RANK: %-16s  ║\n", 
           h->name, hunter_get_rank_name(h->rank));
    printf("║  TITLE: %-51s ║\n", h->title);
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║  DAY: %03u/210            SEASON: %-24s ║\n", 
           h->current_day,
           h->current_day <= 60 ? "Foundation" :
           h->current_day <= 105 ? "Architecture" :
           h->current_day <= 165 ? "Systems" : "Specialization");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    
    /* Stats */
    printf("║  STATS                                                       ║\n");
    printf("║    STR: %-4d    INT: %-4d    SYS: %-4d                       ║\n",
           h->stats.strength, h->stats.intelligence, h->stats.systems);
    printf("║    GPU: %-4d    SEC: %-4d    END: %-4d                       ║\n",
           h->stats.gpu, h->stats.security, h->stats.endurance);
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    
    /* XP */
    printf("║  XP: %u / %u", h->total_xp, h->xp_to_next_rank);
    
    /* Pad to align right edge */
    int xp_len = snprintf(NULL, 0, "XP: %u / %u", h->total_xp, h->xp_to_next_rank);
    for (int i = 0; i < 60 - xp_len - 2; i++) {
        printf(" ");
    }
    printf("║\n");
    
    /* Streak */
    printf("║  STREAK: %u days (Best: %u)", h->current_streak, h->longest_streak);
    int streak_len = snprintf(NULL, 0, "STREAK: %u days (Best: %u)", 
                              h->current_streak, h->longest_streak);
    for (int i = 0; i < 60 - streak_len - 2; i++) {
        printf(" ");
    }
    printf("║\n");
    
    printf("╚══════════════════════════════════════════════════════════════╝\n");
}
