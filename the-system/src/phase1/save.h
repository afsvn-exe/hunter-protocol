/*
 * save.h — Persistence Layer
 * 
 * THE SYSTEM: HUNTER PROTOCOL
 * Phase 1: The Seed
 * 
 * This module handles saving and loading Hunter progress.
 * Phase 1 uses binary files — raw bytes, no dependencies.
 * 
 * Learning Focus:
 *   - File I/O (fopen, fread, fwrite, fclose)
 *   - Binary data serialization
 *   - Error handling patterns
 *   - Understanding memory layout
 * 
 * Reference: Effective C 2nd Ed., Chapter 10 (I/O)
 * 
 * ============================================================================
 * SAVE FILE FORMAT
 * ============================================================================
 * 
 * Location: ~/.hunter-protocol/save.dat
 * 
 * Binary Layout:
 * 
 *   ┌─────────────────────────────────────────────────────────┐
 *   │  HEADER (16 bytes)                                      │
 *   │    magic:    4 bytes  "HUNT" (0x48554E54)               │
 *   │    version:  4 bytes  Save format version               │
 *   │    flags:    4 bytes  Reserved for future use           │
 *   │    checksum: 4 bytes  CRC32 of data section             │
 *   ├─────────────────────────────────────────────────────────┤
 *   │  HUNTER DATA (sizeof(Hunter) bytes)                     │
 *   │    The complete Hunter struct                           │
 *   ├─────────────────────────────────────────────────────────┤
 *   │  QUEST COUNT (4 bytes)                                  │
 *   │    Number of quests stored                              │
 *   ├─────────────────────────────────────────────────────────┤
 *   │  QUEST DATA (sizeof(Quest) * count bytes)               │
 *   │    Array of Quest structs                               │
 *   └─────────────────────────────────────────────────────────┘
 * 
 * Why binary format?
 *   - Teaches low-level file I/O
 *   - No parsing logic needed
 *   - Compact storage
 *   - Fast read/write
 *   - Later phases will add JSON export for sync
 */

#ifndef SAVE_H
#define SAVE_H

#include <stdint.h>
#include "hunter.h"
#include "quest.h"

/*
 * ============================================================================
 * CONSTANTS
 * ============================================================================
 */

/* Magic number: ASCII "HUNT" = 0x48 0x55 0x4E 0x54 */
#define SAVE_MAGIC   0x48554E54

/* Increment this when save format changes */
#define SAVE_VERSION 1

/* Default save directory (relative to HOME) */
#define SAVE_DIR     ".hunter-protocol"
#define SAVE_FILE    "save.dat"
#define BACKUP_FILE  "save.dat.bak"

/*
 * ============================================================================
 * STRUCTURES
 * ============================================================================
 */

/*
 * SaveHeader — The first 16 bytes of every save file
 * 
 * This header lets us:
 *   - Verify this is actually our file (magic)
 *   - Handle version migrations (version)
 *   - Detect corruption (checksum)
 */
typedef struct {
    uint32_t magic;      /* Must be SAVE_MAGIC */
    uint32_t version;    /* Save format version */
    uint32_t flags;      /* Reserved */
    uint32_t checksum;   /* CRC32 of data after header */
} SaveHeader;

/*
 * SaveResult — Outcome of save/load operations
 * 
 * Using an enum for error codes is cleaner than magic numbers.
 * Each error tells you exactly what went wrong.
 */
typedef enum {
    SAVE_OK              =  0,  /* Success */
    SAVE_ERR_NULL_PTR    = -1,  /* NULL pointer passed */
    SAVE_ERR_NO_HOME     = -2,  /* HOME environment variable not set */
    SAVE_ERR_MKDIR       = -3,  /* Failed to create save directory */
    SAVE_ERR_OPEN        = -4,  /* Failed to open file */
    SAVE_ERR_READ        = -5,  /* Read error */
    SAVE_ERR_WRITE       = -6,  /* Write error */
    SAVE_ERR_MAGIC       = -7,  /* Invalid magic number (not our file) */
    SAVE_ERR_VERSION     = -8,  /* Incompatible save version */
    SAVE_ERR_CHECKSUM    = -9,  /* Data corruption detected */
    SAVE_ERR_BACKUP      = -10  /* Failed to create backup */
} SaveResult;

/*
 * ============================================================================
 * FUNCTION PROTOTYPES
 * ============================================================================
 */

/*
 * save_init — Ensure save directory exists
 * 
 * Creates ~/.hunter-protocol/ if it doesn't exist.
 * Should be called at program startup.
 * 
 * Returns:
 *   SAVE_OK on success
 *   SAVE_ERR_* on failure
 */
SaveResult save_init(void);

/*
 * save_write — Write Hunter and quests to save file
 * 
 * This is the main save function. It:
 *   1. Creates a backup of existing save
 *   2. Writes header with checksum
 *   3. Writes Hunter data
 *   4. Writes quest list
 * 
 * Parameters:
 *   h  — Hunter to save
 *   ql — Quest list to save
 * 
 * Returns:
 *   SAVE_OK on success
 *   SAVE_ERR_* on failure
 */
SaveResult save_write(const Hunter *h, const QuestList *ql);

/*
 * save_read — Load Hunter and quests from save file
 * 
 * Parameters:
 *   h  — Hunter struct to fill (output)
 *   ql — Quest list to fill (output)
 * 
 * Returns:
 *   SAVE_OK on success
 *   SAVE_ERR_* on failure
 */
SaveResult save_read(Hunter *h, QuestList *ql);

/*
 * save_exists — Check if a save file exists
 * 
 * Returns:
 *   1 if save file exists
 *   0 if no save file
 */
int save_exists(void);

/*
 * save_delete — Delete save file (with confirmation)
 * 
 * Use with caution! This is permanent.
 * 
 * Returns:
 *   SAVE_OK on success
 *   SAVE_ERR_* on failure
 */
SaveResult save_delete(void);

/*
 * save_get_path — Get full path to save file
 * 
 * Fills the provided buffer with the path.
 * 
 * Parameters:
 *   buf     — Buffer to fill
 *   bufsize — Size of buffer
 * 
 * Returns:
 *   SAVE_OK on success
 *   SAVE_ERR_NULL_PTR if buf is NULL
 *   SAVE_ERR_NO_HOME if HOME not set
 */
SaveResult save_get_path(char *buf, size_t bufsize);

/*
 * save_result_string — Get human-readable error message
 * 
 * Returns:
 *   Static string describing the error
 */
const char *save_result_string(SaveResult result);

/*
 * ============================================================================
 * HELPER FUNCTIONS (internal, but exposed for testing)
 * ============================================================================
 */

/*
 * save_compute_checksum — Calculate CRC32 of data
 * 
 * Used to detect file corruption.
 * 
 * Parameters:
 *   data — Pointer to data
 *   len  — Length in bytes
 * 
 * Returns:
 *   CRC32 checksum
 */
uint32_t save_compute_checksum(const void *data, size_t len);

#endif /* SAVE_H */
