/*
 * display.h — Terminal Display Functions
 * 
 * THE SYSTEM: HUNTER PROTOCOL
 * Phase 1: The Seed
 * 
 * This module handles all terminal output formatting.
 * Phase 1: printf with ASCII art
 * Phase 2: Will be replaced with ncurses
 * 
 * Learning Focus:
 *   - printf formatting
 *   - Terminal control (clearing screen)
 *   - ASCII art and box drawing
 *   - Modular design (separating display from logic)
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "hunter.h"
#include "quest.h"

/*
 * ============================================================================
 * TERMINAL CONTROL
 * ============================================================================
 */

/*
 * display_clear — Clear the terminal screen
 * 
 * Uses ANSI escape codes. Works on most modern terminals.
 */
void display_clear(void);

/*
 * display_set_title — Set terminal window title
 * 
 * Uses ANSI escape codes. May not work on all terminals.
 */
void display_set_title(const char *title);

/*
 * ============================================================================
 * SYSTEM BANNERS AND FRAMES
 * ============================================================================
 */

/*
 * display_banner — Show the main title banner
 */
void display_banner(void);

/*
 * display_notification — Show a system notification
 * 
 * Format: 「 MESSAGE 」
 * Used for level-ups, achievements, shadow quest triggers.
 */
void display_notification(const char *message);

/*
 * display_alert — Show an important alert
 * 
 * Draws attention with special formatting.
 */
void display_alert(const char *message);

/*
 * ============================================================================
 * HUNTER DISPLAY
 * ============================================================================
 */

/*
 * display_hunter_status — Full hunter status panel
 * 
 * Shows:
 *   - Name and title
 *   - Rank
 *   - Current day
 *   - XP bar
 *   - All stats
 *   - Streak info
 */
void display_hunter_status(const Hunter *h);

/*
 * display_hunter_compact — Single-line hunter summary
 * 
 * For use in headers: "Afsan | E-Rank | Day 3 | XP: 340/1000"
 */
void display_hunter_compact(const Hunter *h);

/*
 * display_stats — Show just the stats block
 */
void display_stats(const HunterStats *s);

/*
 * display_stat_bar — Visual bar for a single stat
 * 
 * Example: STR: ███░░░░░░░ 34
 */
void display_stat_bar(const char *name, int value, int max_display);

/*
 * display_xp_bar — Visual XP progress bar
 * 
 * Example: XP: ████████░░░░░░░░░░░░ 340/1000
 */
void display_xp_bar(uint32_t current, uint32_t target);

/*
 * display_rank_up — Special animation for rank increase
 * 
 * Makes the moment feel special!
 */
void display_rank_up(HunterRank old_rank, HunterRank new_rank);

/*
 * ============================================================================
 * QUEST DISPLAY
 * ============================================================================
 */

/*
 * display_quest — Show full quest details
 */
void display_quest(const Quest *q);

/*
 * display_quest_compact — Single-line quest summary
 */
void display_quest_compact(const Quest *q);

/*
 * display_quest_list — Show list of quests
 * 
 * Parameters:
 *   quests — Array of quest pointers
 *   count  — Number of quests
 *   title  — Section title (e.g., "ACTIVE QUESTS")
 */
void display_quest_list(Quest **quests, int count, const char *title);

/*
 * display_quest_complete — Animation for completing a quest
 */
void display_quest_complete(const Quest *q, uint32_t xp_earned);

/*
 * display_death — Animation for failing a quest
 * 
 * "YOU DIED" but with respawn messaging
 */
void display_death(const Quest *q);

/*
 * ============================================================================
 * MENU DISPLAY
 * ============================================================================
 */

/*
 * display_main_menu — Show the main menu options
 */
void display_main_menu(void);

/*
 * display_prompt — Show input prompt and get choice
 * 
 * Returns:
 *   Character entered by user (lowercase)
 */
char display_prompt(const char *prompt);

/*
 * display_confirm — Yes/no confirmation
 * 
 * Returns:
 *   1 for yes
 *   0 for no
 */
int display_confirm(const char *question);

/*
 * ============================================================================
 * UTILITY
 * ============================================================================
 */

/*
 * display_wait — Pause with message
 * 
 * Shows message and waits for Enter key.
 */
void display_wait(const char *message);

/*
 * display_divider — Print a horizontal line
 */
void display_divider(void);

/*
 * display_box — Draw text inside a box
 * 
 * ╔══════════════════╗
 * ║ Your text here   ║
 * ╚══════════════════╝
 */
void display_box(const char *text);

#endif /* DISPLAY_H */
