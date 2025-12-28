/*
 * main.c — The System: Hunter Protocol Entry Point
 * 
 * THE SYSTEM: HUNTER PROTOCOL
 * Phase 1: The Seed
 * 
 * This is where it all begins.
 * 
 * Program Flow:
 *   1. Initialize save system
 *   2. Load or create Hunter profile
 *   3. Display status
 *   4. Main menu loop
 *   5. Save and exit
 * 
 * Learning Focus:
 *   - Program structure
 *   - Main loop pattern
 *   - Error handling
 *   - Clean startup/shutdown
 * 
 * Build:
 *   make
 * 
 * Run:
 *   ./hunter
 * 
 * ============================================================================
 * 
 *   "I alone level up."
 * 
 *   Welcome to The System, Hunter.
 *   Your journey of 210 days begins with a single compilation.
 * 
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hunter.h"
#include "quest.h"
#include "save.h"
#include "display.h"

/*
 * ============================================================================
 * GLOBAL STATE
 * ============================================================================
 * 
 * In Phase 1, we use global state for simplicity.
 * Phase 2 will refactor this into a proper application context.
 * 
 * This is a pragmatic choice: globals are fine for small programs.
 * The goal now is to get something working, not architectural purity.
 */

static Hunter g_hunter;
static QuestList g_quests;
static int g_running = 1;

/*
 * ============================================================================
 * FORWARD DECLARATIONS
 * ============================================================================
 */

static void init_game(void);
static void main_loop(void);
static void shutdown_game(void);
static void handle_menu_choice(char choice);
static void show_status(void);
static void show_quests(void);
static void add_sample_quests(void);

/*
 * ============================================================================
 * MAIN
 * ============================================================================
 */

int main(int argc, char *argv[])
{
    /*
     * Suppress unused parameter warnings.
     * We'll use argc/argv in later phases for CLI arguments.
     */
    (void)argc;
    (void)argv;
    
    /* Seed random number generator (for future shadow quests) */
    srand((unsigned int)time(NULL));
    
    /* Initialize and run */
    init_game();
    main_loop();
    shutdown_game();
    
    return 0;
}

/*
 * ============================================================================
 * INITIALIZATION
 * ============================================================================
 */

static void init_game(void)
{
    SaveResult result;
    char name_buf[MAX_NAME_LENGTH];
    
    /* Ensure save directory exists */
    result = save_init();
    if (result != SAVE_OK) {
        fprintf(stderr, "Warning: Could not initialize save system: %s\n",
                save_result_string(result));
        /* Continue anyway — we can still run without saving */
    }
    
    /* Try to load existing save */
    if (save_exists()) {
        result = save_read(&g_hunter, &g_quests);
        if (result == SAVE_OK) {
            display_clear();
            display_banner();
            printf("\n");
            display_notification("HUNTER DATA LOADED");
            printf("\n");
            printf("  Welcome back, %s.\n", g_hunter.name);
            printf("  Day %u of the Protocol.\n", g_hunter.current_day);
            printf("  Current Rank: %s\n", hunter_get_rank_name(g_hunter.rank));
            printf("\n");
            display_wait("Press Enter to continue...");
            return;
        } else {
            fprintf(stderr, "Warning: Could not load save: %s\n",
                    save_result_string(result));
            fprintf(stderr, "Starting fresh...\n\n");
        }
    }
    
    /* No save exists or load failed — create new Hunter */
    display_clear();
    display_banner();
    printf("\n");
    display_notification("NEW HUNTER DETECTED");
    printf("\n");
    printf("  「 The System has chosen you. 」\n");
    printf("\n");
    printf("  A new shadow rises.\n");
    printf("  210 days stand between you and transcendence.\n");
    printf("\n");
    printf("  Enter your name, Hunter: ");
    
    /* Read name from user */
    if (fgets(name_buf, sizeof(name_buf), stdin) != NULL) {
        /* Remove trailing newline */
        size_t len = strlen(name_buf);
        if (len > 0 && name_buf[len - 1] == '\n') {
            name_buf[len - 1] = '\0';
        }
        
        /* Use default if empty */
        if (strlen(name_buf) == 0) {
            strcpy(name_buf, "Hunter");
        }
    } else {
        strcpy(name_buf, "Hunter");
    }
    
    /* Initialize Hunter */
    hunter_init(&g_hunter, name_buf);
    
    /* Initialize quest list with sample quests */
    questlist_init(&g_quests);
    add_sample_quests();
    
    /* Save initial state */
    result = save_write(&g_hunter, &g_quests);
    if (result != SAVE_OK) {
        fprintf(stderr, "Warning: Could not save: %s\n",
                save_result_string(result));
    }
    
    printf("\n");
    display_notification("SYSTEM INITIALIZED");
    printf("\n");
    printf("  Welcome, %s.\n", g_hunter.name);
    printf("  You begin at E-Rank.\n");
    printf("  Your first quest awaits.\n");
    printf("\n");
    display_wait("Press Enter to begin your journey...");
}

/*
 * ============================================================================
 * MAIN LOOP
 * ============================================================================
 */

static void main_loop(void)
{
    char choice;
    
    while (g_running) {
        display_clear();
        display_hunter_status(&g_hunter);
        printf("\n");
        display_main_menu();
        choice = display_prompt("Choice: ");
        handle_menu_choice(choice);
    }
}

static void handle_menu_choice(char choice)
{
    switch (choice) {
        case 's':  /* Status */
            show_status();
            break;
            
        case 'q':  /* Quests */
            show_quests();
            break;
            
        case 'c':  /* Complete quest (debug/demo) */
            if (g_quests.count > 0) {
                Quest *q = &g_quests.quests[0];
                if (q->status == QUEST_STATUS_AVAILABLE) {
                    quest_accept(q);
                }
                if (q->status == QUEST_STATUS_ACTIVE) {
                    uint32_t xp = quest_complete(q, &g_hunter);
                    display_quest_complete(q, xp);
                    display_wait("Press Enter to continue...");
                    
                    /* Save after quest completion */
                    save_write(&g_hunter, &g_quests);
                }
            } else {
                display_alert("No quests available!");
                display_wait("Press Enter to continue...");
            }
            break;
            
        case 'x':  /* Exit */
        case 'e':
            if (display_confirm("Exit The System?")) {
                g_running = 0;
            }
            break;
            
        default:
            /* Invalid choice — just redraw menu */
            break;
    }
}

static void show_status(void)
{
    display_clear();
    display_banner();
    printf("\n");
    display_hunter_status(&g_hunter);
    printf("\n");
    display_wait("Press Enter to continue...");
}

static void show_quests(void)
{
    Quest *available[16];
    int count;
    
    display_clear();
    display_banner();
    printf("\n");
    display_notification("QUEST LOG");
    printf("\n");
    
    count = questlist_get_available(&g_quests, &g_hunter, available, 16);
    if (count > 0) {
        display_quest_list(available, count, "AVAILABLE QUESTS");
    } else {
        printf("  No quests available.\n");
    }
    
    printf("\n");
    display_wait("Press Enter to continue...");
}

/*
 * ============================================================================
 * SAMPLE DATA
 * ============================================================================
 * 
 * These sample quests are for testing.
 * In the real system, quests will be loaded from data files.
 */

static void add_sample_quests(void)
{
    Quest *q;
    HunterStats bonus = {0};
    
    /* Quest 1: First Blood */
    q = questlist_add(&g_quests, 1, 
                      "First Blood",
                      "Write and compile your first C program. "
                      "The journey of 10,000 lines begins with printf.",
                      QUEST_TYPE_DAILY,
                      SEASON_FOUNDATION);
    if (q != NULL) {
        bonus.strength = 1;
        quest_set_rewards(q, 50, &bonus);
        quest_set_requirements(q, 1, RANK_E, 0);
        q->status = QUEST_STATUS_AVAILABLE;
    }
    
    /* Quest 2: Memory Palace */
    q = questlist_add(&g_quests, 2,
                      "Memory Palace",
                      "Understand the difference between stack and heap. "
                      "Where does your data live?",
                      QUEST_TYPE_DAILY,
                      SEASON_FOUNDATION);
    if (q != NULL) {
        bonus.strength = 1;
        bonus.intelligence = 1;
        quest_set_rewards(q, 75, &bonus);
        quest_set_requirements(q, 1, RANK_E, 1);
        q->status = QUEST_STATUS_LOCKED;
    }
    
    /* Quest 3: Array Awakening */
    q = questlist_add(&g_quests, 3,
                      "Array Awakening",
                      "Master arrays and pointer arithmetic. "
                      "See the memory as it truly is.",
                      QUEST_TYPE_DAILY,
                      SEASON_FOUNDATION);
    if (q != NULL) {
        bonus.strength = 2;
        quest_set_rewards(q, 100, &bonus);
        quest_set_requirements(q, 3, RANK_E, 0);
        q->status = QUEST_STATUS_AVAILABLE;
    }
}

/*
 * ============================================================================
 * SHUTDOWN
 * ============================================================================
 */

static void shutdown_game(void)
{
    SaveResult result;
    
    /* Final save */
    result = save_write(&g_hunter, &g_quests);
    if (result != SAVE_OK) {
        fprintf(stderr, "Warning: Final save failed: %s\n",
                save_result_string(result));
    }
    
    display_clear();
    display_banner();
    printf("\n");
    display_notification("SYSTEM SHUTDOWN");
    printf("\n");
    printf("  Until next time, %s.\n", g_hunter.name);
    printf("  Your progress has been saved.\n");
    printf("  Day %u | %s | XP: %u\n",
           g_hunter.current_day,
           hunter_get_rank_name(g_hunter.rank),
           g_hunter.total_xp);
    printf("\n");
    printf("  「 Arise. 」\n");
    printf("\n");
}
