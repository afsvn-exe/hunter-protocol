/*
 * quest.c — Quest System Implementation
 * 
 * THE SYSTEM: HUNTER PROTOCOL
 * Phase 1: The Seed
 * 
 * Learning Focus:
 *   - More complex struct manipulation
 *   - State machine implementation
 *   - Pointer-based array operations
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "quest.h"

/*
 * ============================================================================
 * NAME LOOKUP TABLES
 * ============================================================================
 */

static const char *QUEST_TYPE_NAMES[] = {
    "Daily",
    "Weekly",
    "Shadow",
    "Boss",
    "Side"
};

static const char *QUEST_STATUS_NAMES[] = {
    "Locked",
    "Available",
    "Active",
    "Completed",
    "Failed"
};

/*
 * ============================================================================
 * QUEST FUNCTIONS
 * ============================================================================
 */

int quest_init(Quest *q, uint32_t id, const char *name, const char *desc,
               QuestType type, ProtocolSeason season)
{
    if (q == NULL || name == NULL) {
        return -1;
    }
    
    memset(q, 0, sizeof(*q));
    
    q->id = id;
    
    strncpy(q->name, name, MAX_QUEST_NAME - 1);
    q->name[MAX_QUEST_NAME - 1] = '\0';
    
    if (desc != NULL) {
        strncpy(q->description, desc, MAX_QUEST_DESCRIPTION - 1);
        q->description[MAX_QUEST_DESCRIPTION - 1] = '\0';
    }
    
    q->type = type;
    q->status = QUEST_STATUS_LOCKED;
    q->season = season;
    
    return 0;
}

void quest_set_rewards(Quest *q, uint32_t xp, const HunterStats *stats)
{
    if (q == NULL) {
        return;
    }
    
    q->rewards.xp = xp;
    
    if (stats != NULL) {
        q->rewards.stat_bonus = *stats;
    }
}

void quest_set_requirements(Quest *q, uint32_t min_day, HunterRank min_rank,
                            uint32_t prerequisite_id)
{
    if (q == NULL) {
        return;
    }
    
    q->requirements.min_day = min_day;
    q->requirements.min_rank = min_rank;
    q->requirements.prerequisite_id = prerequisite_id;
}

int quest_can_unlock(const Quest *q, const Hunter *h)
{
    if (q == NULL || h == NULL) {
        return 0;
    }
    
    /* Check day requirement */
    if (h->current_day < q->requirements.min_day) {
        return 0;
    }
    
    /* Check rank requirement */
    if (h->rank < q->requirements.min_rank) {
        return 0;
    }
    
    /*
     * Prerequisite check would require access to the full quest list.
     * For now, we assume prerequisites are handled externally.
     * This is a simplification for Phase 1.
     */
    
    return 1;
}

int quest_accept(Quest *q)
{
    if (q == NULL) {
        return -1;
    }
    
    if (q->status != QUEST_STATUS_AVAILABLE) {
        return -1;
    }
    
    q->status = QUEST_STATUS_ACTIVE;
    q->started_at = time(NULL);
    q->attempts++;
    
    return 0;
}

uint32_t quest_complete(Quest *q, Hunter *h)
{
    if (q == NULL || h == NULL) {
        return 0;
    }
    
    if (q->status != QUEST_STATUS_ACTIVE) {
        return 0;
    }
    
    q->status = QUEST_STATUS_COMPLETED;
    q->completed_at = time(NULL);
    
    /* Award XP */
    hunter_add_xp(h, q->rewards.xp);
    
    /* Award stat bonuses */
    hunter_add_stats(h, &q->rewards.stat_bonus);
    
    /* Update quest counter */
    h->quests_completed++;
    
    /* Update streak */
    hunter_update_streak(h);
    
    return q->rewards.xp;
}

void quest_fail(Quest *q)
{
    if (q == NULL) {
        return;
    }
    
    if (q->status != QUEST_STATUS_ACTIVE) {
        return;
    }
    
    q->status = QUEST_STATUS_FAILED;
}

int quest_retry(Quest *q)
{
    if (q == NULL) {
        return -1;
    }
    
    if (q->status != QUEST_STATUS_FAILED) {
        return -1;
    }
    
    q->status = QUEST_STATUS_ACTIVE;
    q->started_at = time(NULL);
    q->attempts++;
    
    return 0;
}

const char *quest_get_type_name(QuestType type)
{
    if (type < 0 || type > QUEST_TYPE_SIDE) {
        return "Unknown";
    }
    return QUEST_TYPE_NAMES[type];
}

const char *quest_get_status_name(QuestStatus status)
{
    if (status < 0 || status > QUEST_STATUS_FAILED) {
        return "Unknown";
    }
    return QUEST_STATUS_NAMES[status];
}

void quest_display(const Quest *q)
{
    if (q == NULL) {
        printf("Error: No quest data\n");
        return;
    }
    
    printf("┌────────────────────────────────────────────────────────────┐\n");
    printf("│ 「 %s 」\n", q->name);
    printf("├────────────────────────────────────────────────────────────┤\n");
    printf("│ Type: %-10s  Status: %-10s  Season: %d\n",
           quest_get_type_name(q->type),
           quest_get_status_name(q->status),
           q->season);
    printf("├────────────────────────────────────────────────────────────┤\n");
    printf("│ %s\n", q->description);
    printf("├────────────────────────────────────────────────────────────┤\n");
    printf("│ Rewards: +%u XP", q->rewards.xp);
    if (q->rewards.stat_bonus.strength > 0) {
        printf(", +%d STR", q->rewards.stat_bonus.strength);
    }
    if (q->rewards.stat_bonus.intelligence > 0) {
        printf(", +%d INT", q->rewards.stat_bonus.intelligence);
    }
    if (q->rewards.stat_bonus.systems > 0) {
        printf(", +%d SYS", q->rewards.stat_bonus.systems);
    }
    printf("\n");
    printf("└────────────────────────────────────────────────────────────┘\n");
}

/*
 * ============================================================================
 * QUEST LIST FUNCTIONS
 * ============================================================================
 */

void questlist_init(QuestList *ql)
{
    if (ql == NULL) {
        return;
    }
    
    memset(ql, 0, sizeof(*ql));
}

Quest *questlist_add(QuestList *ql, uint32_t id, const char *name,
                     const char *desc, QuestType type, ProtocolSeason season)
{
    Quest *q;
    
    if (ql == NULL || ql->count >= MAX_QUESTS) {
        return NULL;
    }
    
    q = &ql->quests[ql->count];
    
    if (quest_init(q, id, name, desc, type, season) != 0) {
        return NULL;
    }
    
    ql->count++;
    return q;
}

Quest *questlist_find(QuestList *ql, uint32_t id)
{
    if (ql == NULL) {
        return NULL;
    }
    
    for (uint32_t i = 0; i < ql->count; i++) {
        if (ql->quests[i].id == id) {
            return &ql->quests[i];
        }
    }
    
    return NULL;
}

int questlist_get_active(QuestList *ql, Quest **out, int max_out)
{
    int count = 0;
    
    if (ql == NULL || out == NULL || max_out <= 0) {
        return 0;
    }
    
    for (uint32_t i = 0; i < ql->count && count < max_out; i++) {
        if (ql->quests[i].status == QUEST_STATUS_ACTIVE) {
            out[count++] = &ql->quests[i];
        }
    }
    
    return count;
}

int questlist_get_available(QuestList *ql, const Hunter *h,
                            Quest **out, int max_out)
{
    int count = 0;
    
    if (ql == NULL || out == NULL || max_out <= 0) {
        return 0;
    }
    
    for (uint32_t i = 0; i < ql->count && count < max_out; i++) {
        Quest *q = &ql->quests[i];
        
        if (q->status == QUEST_STATUS_AVAILABLE ||
            (q->status == QUEST_STATUS_LOCKED && quest_can_unlock(q, h))) {
            out[count++] = q;
        }
    }
    
    return count;
}
