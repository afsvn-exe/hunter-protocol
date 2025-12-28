/*
 * display.c — Terminal Display Implementation
 * 
 * THE SYSTEM: HUNTER PROTOCOL
 * Phase 1: The Seed
 * 
 * Learning Focus:
 *   - printf formatting and escape codes
 *   - ANSI terminal control
 *   - ASCII art and box drawing characters
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "display.h"

/*
 * ============================================================================
 * ANSI ESCAPE CODES
 * ============================================================================
 * 
 * These are special character sequences that control terminal behavior.
 * They start with ESC (0x1B or \033) followed by '[' and a command.
 * 
 * Not all terminals support these, but most modern ones do.
 */

#define ANSI_RESET      "\033[0m"
#define ANSI_BOLD       "\033[1m"
#define ANSI_DIM        "\033[2m"
#define ANSI_UNDERLINE  "\033[4m"

#define ANSI_BLACK      "\033[30m"
#define ANSI_RED        "\033[31m"
#define ANSI_GREEN      "\033[32m"
#define ANSI_YELLOW     "\033[33m"
#define ANSI_BLUE       "\033[34m"
#define ANSI_MAGENTA    "\033[35m"
#define ANSI_CYAN       "\033[36m"
#define ANSI_WHITE      "\033[37m"

#define ANSI_CLEAR      "\033[2J"
#define ANSI_HOME       "\033[H"

/*
 * ============================================================================
 * TERMINAL CONTROL
 * ============================================================================
 */

void display_clear(void)
{
    /*
     * \033[2J clears the screen
     * \033[H moves cursor to home position (top-left)
     * Combined, they reset the terminal view.
     */
    printf(ANSI_CLEAR ANSI_HOME);
    fflush(stdout);
}

void display_set_title(const char *title)
{
    if (title == NULL) {
        return;
    }
    
    /*
     * OSC (Operating System Command) sequence for setting window title.
     * \033]0; starts the title sequence
     * \007 (BEL) ends it
     */
    printf("\033]0;%s\007", title);
    fflush(stdout);
}

/*
 * ============================================================================
 * BANNERS AND NOTIFICATIONS
 * ============================================================================
 */

void display_banner(void)
{
    printf(ANSI_CYAN);
    printf("╔═══════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                   ║\n");
    printf("║   ████████╗██╗  ██╗███████╗    ███████╗██╗   ██╗███████╗          ║\n");
    printf("║   ╚══██╔══╝██║  ██║██╔════╝    ██╔════╝╚██╗ ██╔╝██╔════╝          ║\n");
    printf("║      ██║   ███████║█████╗      ███████╗ ╚████╔╝ ███████╗          ║\n");
    printf("║      ██║   ██╔══██║██╔══╝      ╚════██║  ╚██╔╝  ╚════██║          ║\n");
    printf("║      ██║   ██║  ██║███████╗    ███████║   ██║   ███████║          ║\n");
    printf("║      ╚═╝   ╚═╝  ╚═╝╚══════╝    ╚══════╝   ╚═╝   ╚══════╝          ║\n");
    printf("║                                                                   ║\n");
    printf("║                  H U N T E R   P R O T O C O L                    ║\n");
    printf("║                                                                   ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════╝\n");
    printf(ANSI_RESET);
}

void display_notification(const char *message)
{
    if (message == NULL) {
        return;
    }
    
    printf(ANSI_YELLOW ANSI_BOLD);
    printf("  「 %s 」\n", message);
    printf(ANSI_RESET);
}

void display_alert(const char *message)
{
    if (message == NULL) {
        return;
    }
    
    printf(ANSI_RED ANSI_BOLD);
    printf("\n");
    printf("  ╔═══════════════════════════════════════╗\n");
    printf("  ║ ! ALERT: %-28s ║\n", message);
    printf("  ╚═══════════════════════════════════════╝\n");
    printf(ANSI_RESET);
}

/*
 * ============================================================================
 * HUNTER DISPLAY
 * ============================================================================
 */

void display_hunter_status(const Hunter *h)
{
    if (h == NULL) {
        printf("Error: No hunter data\n");
        return;
    }
    
    /* Call the Hunter's own display function */
    hunter_display(h);
}

void display_hunter_compact(const Hunter *h)
{
    if (h == NULL) {
        return;
    }
    
    printf("%s | %s | Day %u | XP: %u/%u",
           h->name,
           hunter_get_rank_name(h->rank),
           h->current_day,
           h->total_xp,
           h->xp_to_next_rank);
}

void display_stats(const HunterStats *s)
{
    if (s == NULL) {
        return;
    }
    
    printf("  STR: %3d  INT: %3d  SYS: %3d\n",
           s->strength, s->intelligence, s->systems);
    printf("  GPU: %3d  SEC: %3d  END: %3d\n",
           s->gpu, s->security, s->endurance);
}

void display_stat_bar(const char *name, int value, int max_display)
{
    int filled;
    int i;
    
    if (name == NULL || max_display <= 0) {
        return;
    }
    
    /* Calculate how many blocks to fill */
    filled = (value > max_display) ? max_display : value;
    
    printf("  %s: ", name);
    
    for (i = 0; i < filled; i++) {
        printf("█");
    }
    for (i = filled; i < max_display; i++) {
        printf("░");
    }
    
    printf(" %d\n", value);
}

void display_xp_bar(uint32_t current, uint32_t target)
{
    int bar_width = 20;
    int filled;
    int i;
    float progress;
    
    if (target == 0) {
        progress = 1.0f;
    } else {
        progress = (float)current / (float)target;
        if (progress > 1.0f) progress = 1.0f;
    }
    
    filled = (int)(progress * bar_width);
    
    printf("  XP: ");
    printf(ANSI_GREEN);
    for (i = 0; i < filled; i++) {
        printf("█");
    }
    printf(ANSI_DIM);
    for (i = filled; i < bar_width; i++) {
        printf("░");
    }
    printf(ANSI_RESET);
    printf(" %u/%u\n", current, target);
}

void display_rank_up(HunterRank old_rank, HunterRank new_rank)
{
    printf("\n");
    printf(ANSI_YELLOW ANSI_BOLD);
    printf("  ╔═══════════════════════════════════════════════════════════╗\n");
    printf("  ║                                                           ║\n");
    printf("  ║                    「 RANK UP 」                           ║\n");
    printf("  ║                                                           ║\n");
    printf("  ║          %s  ──────▶  %s              \n",
           hunter_get_rank_name(old_rank), hunter_get_rank_name(new_rank));
    printf("  ║                                                           ║\n");
    printf("  ║              You have grown stronger.                     ║\n");
    printf("  ║                                                           ║\n");
    printf("  ╚═══════════════════════════════════════════════════════════╝\n");
    printf(ANSI_RESET);
    printf("\n");
}

/*
 * ============================================================================
 * QUEST DISPLAY
 * ============================================================================
 */

void display_quest(const Quest *q)
{
    if (q == NULL) {
        return;
    }
    
    quest_display(q);
}

void display_quest_compact(const Quest *q)
{
    if (q == NULL) {
        return;
    }
    
    printf("  [%s] %s (+%u XP)\n",
           quest_get_status_name(q->status),
           q->name,
           q->rewards.xp);
}

void display_quest_list(Quest **quests, int count, const char *title)
{
    if (quests == NULL || count <= 0) {
        return;
    }
    
    if (title != NULL) {
        printf("\n  ═══ %s ═══\n\n", title);
    }
    
    for (int i = 0; i < count; i++) {
        if (quests[i] != NULL) {
            printf("  %d. ", i + 1);
            display_quest_compact(quests[i]);
        }
    }
}

void display_quest_complete(const Quest *q, uint32_t xp_earned)
{
    if (q == NULL) {
        return;
    }
    
    printf("\n");
    printf(ANSI_GREEN ANSI_BOLD);
    printf("  ╔═══════════════════════════════════════════════════════════╗\n");
    printf("  ║                                                           ║\n");
    printf("  ║                「 QUEST COMPLETE 」                        ║\n");
    printf("  ║                                                           ║\n");
    printf("  ║  %-55s  ║\n", q->name);
    printf("  ║                                                           ║\n");
    printf("  ║  Rewards:                                                 ║\n");
    printf("  ║    +%u XP                                                 \n", xp_earned);
    if (q->rewards.stat_bonus.strength > 0) {
        printf("  ║    +%d STR                                                \n", 
               q->rewards.stat_bonus.strength);
    }
    if (q->rewards.stat_bonus.intelligence > 0) {
        printf("  ║    +%d INT                                                \n",
               q->rewards.stat_bonus.intelligence);
    }
    printf("  ║                                                           ║\n");
    printf("  ╚═══════════════════════════════════════════════════════════╝\n");
    printf(ANSI_RESET);
    printf("\n");
}

void display_death(const Quest *q)
{
    if (q == NULL) {
        return;
    }
    
    printf("\n");
    printf(ANSI_RED ANSI_BOLD);
    printf("  ╔═══════════════════════════════════════════════════════════╗\n");
    printf("  ║                                                           ║\n");
    printf("  ║                    「 YOU DIED 」                          ║\n");
    printf("  ║                                                           ║\n");
    printf("  ║  Quest Failed: %-40s  ║\n", q->name);
    printf("  ║                                                           ║\n");
    printf("  ║            But death is not the end.                      ║\n");
    printf("  ║                 Respawn. Retry. Rise.                     ║\n");
    printf("  ║                                                           ║\n");
    printf("  ╚═══════════════════════════════════════════════════════════╝\n");
    printf(ANSI_RESET);
    printf("\n");
}

/*
 * ============================================================================
 * MENU DISPLAY
 * ============================================================================
 */

void display_main_menu(void)
{
    printf("  ┌─────────────────────────────────────┐\n");
    printf("  │  [S] Status    [Q] Quests           │\n");
    printf("  │  [C] Complete  [X] Exit             │\n");
    printf("  └─────────────────────────────────────┘\n");
}

char display_prompt(const char *prompt)
{
    char buf[16];
    char result = '\0';
    
    if (prompt != NULL) {
        printf("  %s", prompt);
    }
    
    fflush(stdout);
    
    if (fgets(buf, sizeof(buf), stdin) != NULL) {
        /* Get first non-whitespace character */
        for (int i = 0; buf[i] != '\0'; i++) {
            if (!isspace((unsigned char)buf[i])) {
                result = (char)tolower((unsigned char)buf[i]);
                break;
            }
        }
    }
    
    return result;
}

int display_confirm(const char *question)
{
    char response;
    
    if (question != NULL) {
        printf("  %s (y/n): ", question);
    } else {
        printf("  Confirm? (y/n): ");
    }
    
    response = display_prompt("");
    
    return (response == 'y');
}

/*
 * ============================================================================
 * UTILITY
 * ============================================================================
 */

void display_wait(const char *message)
{
    char buf[8];
    
    if (message != NULL) {
        printf("  %s", message);
    } else {
        printf("  Press Enter to continue...");
    }
    
    fflush(stdout);
    fgets(buf, sizeof(buf), stdin);
}

void display_divider(void)
{
    printf("  ────────────────────────────────────────────────────────\n");
}

void display_box(const char *text)
{
    size_t len;
    size_t i;
    
    if (text == NULL) {
        return;
    }
    
    len = strlen(text);
    
    /* Top border */
    printf("  ╔");
    for (i = 0; i < len + 2; i++) printf("═");
    printf("╗\n");
    
    /* Text */
    printf("  ║ %s ║\n", text);
    
    /* Bottom border */
    printf("  ╚");
    for (i = 0; i < len + 2; i++) printf("═");
    printf("╝\n");
}
