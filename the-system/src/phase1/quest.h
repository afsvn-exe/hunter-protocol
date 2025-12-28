/*
 * quest.h — The Challenge System
 * 
 * THE SYSTEM: HUNTER PROTOCOL
 * Phase 1: The Seed
 * 
 * Quests are how you grow. Each completed quest grants XP and stats.
 * The quest system is the engine that drives progression.
 * 
 * Learning Focus:
 *   - More complex structs
 *   - Enum for state machines (QuestStatus)
 *   - Thinking about data relationships
 * 
 * Reference: Effective C 2nd Ed., Chapter 6 (Pointers)
 */

#ifndef QUEST_H
#define QUEST_H

#include <time.h>
#include <stdint.h>
#include "hunter.h"   /* For HunterStats, HunterRank */

/*
 * ============================================================================
 * CONSTANTS
 * ============================================================================
 */

#define MAX_QUEST_NAME        128
#define MAX_QUEST_DESCRIPTION 512
#define MAX_OBJECTIVES        8

/*
 * ============================================================================
 * ENUMERATIONS
 * ============================================================================
 */

/*
 * QuestType — Categories of challenges
 * 
 * DAILY   — Must complete within the day, standard progression
 * WEEKLY  — Capstone projects, larger scope
 * SHADOW  — Hidden quests that appear based on special triggers
 * BOSS    — Season-ending challenges, major tests
 * SIDE    — Optional expansion, not required for progression
 */
typedef enum {
    QUEST_TYPE_DAILY  = 0,
    QUEST_TYPE_WEEKLY = 1,
    QUEST_TYPE_SHADOW = 2,
    QUEST_TYPE_BOSS   = 3,
    QUEST_TYPE_SIDE   = 4
} QuestType;

/*
 * QuestStatus — State machine for quest progression
 * 
 * This is a classic state machine pattern:
 * 
 *   LOCKED ──prerequisites met──▶ AVAILABLE
 *                                      │
 *                               hunter accepts
 *                                      ▼
 *                                   ACTIVE
 *                                   │    │
 *                             success    failure
 *                                ▼          ▼
 *                           COMPLETED    FAILED
 *                                           │
 *                                         retry
 *                                           ▼
 *                                        ACTIVE
 */
typedef enum {
    QUEST_STATUS_LOCKED    = 0,  /* Prerequisites not met */
    QUEST_STATUS_AVAILABLE = 1,  /* Ready to accept */
    QUEST_STATUS_ACTIVE    = 2,  /* Currently working on it */
    QUEST_STATUS_COMPLETED = 3,  /* Successfully finished */
    QUEST_STATUS_FAILED    = 4   /* Failed — death, can retry */
} QuestStatus;

/*
 * ProtocolSeason — The four seasons of Hunter Protocol 2.0
 * 
 * Each season has its own focus and unlocks new quest types.
 */
typedef enum {
    SEASON_FOUNDATION     = 1,  /* Days 1-60: C mastery */
    SEASON_ARCHITECTURE   = 2,  /* Days 61-105: CPU internals, C++ */
    SEASON_SYSTEMS        = 3,  /* Days 106-165: Linux internals */
    SEASON_SPECIALIZATION = 4   /* Days 166-210: GPU, CUDA */
} ProtocolSeason;

/*
 * ============================================================================
 * STRUCTURES
 * ============================================================================
 */

/*
 * QuestReward — What you get for completing a quest
 * 
 * Separating rewards into its own struct makes the code cleaner
 * and lets us easily add new reward types later.
 */
typedef struct {
    uint32_t xp;              /* Experience points */
    HunterStats stat_bonus;   /* Stat increases */
    /* Future: unlock_skill_id, item_id, title_id */
} QuestReward;

/*
 * QuestRequirement — What's needed to unlock or complete a quest
 */
typedef struct {
    uint32_t min_day;             /* Minimum Protocol day */
    HunterRank min_rank;          /* Minimum Hunter rank */
    uint32_t prerequisite_id;     /* Quest that must be completed first (0 = none) */
} QuestRequirement;

/*
 * Quest — A single challenge in The System
 * 
 * This is a larger struct with nested components.
 * Notice how we compose smaller structs (QuestReward, QuestRequirement)
 * to build a larger one. This is composition — a key design pattern.
 */
typedef struct {
    /* Identity */
    uint32_t id;                              /* Unique quest identifier */
    char name[MAX_QUEST_NAME];
    char description[MAX_QUEST_DESCRIPTION];
    
    /* Classification */
    QuestType type;
    QuestStatus status;
    ProtocolSeason season;
    
    /* Requirements and Rewards */
    QuestRequirement requirements;
    QuestReward rewards;
    
    /* Time Tracking */
    uint32_t day_deadline;    /* 0 = no deadline */
    time_t started_at;        /* When quest was accepted */
    time_t completed_at;      /* When quest was finished */
    
    /* Attempt Tracking (for the death/respawn system) */
    uint32_t attempts;
    
} Quest;

/*
 * QuestList — Container for multiple quests
 * 
 * In Phase 1, we use a fixed-size array.
 * In Phase 2, this might become a dynamic array or linked list.
 * 
 * The count field tracks how many quests are actually used.
 */
#define MAX_QUESTS 256

typedef struct {
    Quest quests[MAX_QUESTS];
    uint32_t count;
} QuestList;

/*
 * ============================================================================
 * FUNCTION PROTOTYPES
 * ============================================================================
 */

/*
 * quest_init — Initialize a quest with given parameters
 */
int quest_init(Quest *q, uint32_t id, const char *name, const char *desc,
               QuestType type, ProtocolSeason season);

/*
 * quest_set_rewards — Set the rewards for a quest
 */
void quest_set_rewards(Quest *q, uint32_t xp, const HunterStats *stats);

/*
 * quest_set_requirements — Set unlock requirements
 */
void quest_set_requirements(Quest *q, uint32_t min_day, HunterRank min_rank,
                            uint32_t prerequisite_id);

/*
 * quest_can_unlock — Check if a quest can be unlocked
 * 
 * Parameters:
 *   q — The quest to check
 *   h — The hunter attempting to unlock
 * 
 * Returns:
 *   1 if quest can be unlocked
 *   0 if requirements not met
 */
int quest_can_unlock(const Quest *q, const Hunter *h);

/*
 * quest_accept — Transition quest from AVAILABLE to ACTIVE
 * 
 * Returns:
 *   0 on success
 *  -1 if quest not available
 */
int quest_accept(Quest *q);

/*
 * quest_complete — Mark quest as completed, apply rewards
 * 
 * Parameters:
 *   q — Quest to complete
 *   h — Hunter receiving rewards
 * 
 * Returns:
 *   XP awarded (for display purposes)
 */
uint32_t quest_complete(Quest *q, Hunter *h);

/*
 * quest_fail — Mark quest as failed (death)
 * 
 * Increments attempt counter. Quest can be retried.
 */
void quest_fail(Quest *q);

/*
 * quest_retry — Reset failed quest to ACTIVE
 */
int quest_retry(Quest *q);

/*
 * quest_get_type_name — Human-readable quest type
 */
const char *quest_get_type_name(QuestType type);

/*
 * quest_get_status_name — Human-readable quest status
 */
const char *quest_get_status_name(QuestStatus status);

/*
 * quest_display — Print quest details to stdout
 */
void quest_display(const Quest *q);

/*
 * ============================================================================
 * QUEST LIST OPERATIONS
 * ============================================================================
 */

/*
 * questlist_init — Initialize an empty quest list
 */
void questlist_init(QuestList *ql);

/*
 * questlist_add — Add a quest to the list
 * 
 * Returns:
 *   Pointer to the added quest (for further configuration)
 *   NULL if list is full
 */
Quest *questlist_add(QuestList *ql, uint32_t id, const char *name,
                     const char *desc, QuestType type, ProtocolSeason season);

/*
 * questlist_find — Find a quest by ID
 * 
 * Returns:
 *   Pointer to quest if found
 *   NULL if not found
 */
Quest *questlist_find(QuestList *ql, uint32_t id);

/*
 * questlist_get_active — Get currently active quests
 * 
 * Parameters:
 *   ql      — Source quest list
 *   out     — Array to fill with active quest pointers
 *   max_out — Maximum quests to return
 * 
 * Returns:
 *   Number of active quests found
 */
int questlist_get_active(QuestList *ql, Quest **out, int max_out);

/*
 * questlist_get_available — Get quests that can be accepted
 */
int questlist_get_available(QuestList *ql, const Hunter *h, 
                            Quest **out, int max_out);

#endif /* QUEST_H */
