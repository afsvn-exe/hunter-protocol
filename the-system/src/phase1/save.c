/*
 * save.c — Persistence Layer Implementation
 * 
 * THE SYSTEM: HUNTER PROTOCOL
 * Phase 1: The Seed
 * 
 * Learning Focus:
 *   - Binary file I/O (fread, fwrite)
 *   - File system operations (mkdir, stat)
 *   - Error handling patterns
 *   - Checksum calculation (CRC32)
 * 
 * Reference: Effective C 2nd Ed., Chapter 10 (I/O)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include "save.h"

/*
 * ============================================================================
 * CRC32 IMPLEMENTATION
 * ============================================================================
 * 
 * CRC (Cyclic Redundancy Check) is a checksum algorithm.
 * We use it to detect if save files have been corrupted.
 * 
 * This is a simple lookup-table implementation.
 * The table is generated once at startup.
 */

static uint32_t crc32_table[256];
static int crc32_table_initialized = 0;

/*
 * generate_crc32_table — Build the CRC32 lookup table
 * 
 * This uses the standard CRC32 polynomial (0xEDB88320).
 * Called once, the first time we need to compute a checksum.
 */
static void generate_crc32_table(void)
{
    uint32_t crc;
    int i, j;
    
    for (i = 0; i < 256; i++) {
        crc = (uint32_t)i;
        for (j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc = crc >> 1;
            }
        }
        crc32_table[i] = crc;
    }
    
    crc32_table_initialized = 1;
}

uint32_t save_compute_checksum(const void *data, size_t len)
{
    const unsigned char *buf = (const unsigned char *)data;
    uint32_t crc = 0xFFFFFFFF;
    size_t i;
    
    if (!crc32_table_initialized) {
        generate_crc32_table();
    }
    
    if (data == NULL || len == 0) {
        return 0;
    }
    
    for (i = 0; i < len; i++) {
        crc = (crc >> 8) ^ crc32_table[(crc ^ buf[i]) & 0xFF];
    }
    
    return crc ^ 0xFFFFFFFF;
}

/*
 * ============================================================================
 * PATH HANDLING
 * ============================================================================
 */

SaveResult save_get_path(char *buf, size_t bufsize)
{
    const char *home;
    int written;
    
    if (buf == NULL || bufsize == 0) {
        return SAVE_ERR_NULL_PTR;
    }
    
    home = getenv("HOME");
    if (home == NULL) {
        return SAVE_ERR_NO_HOME;
    }
    
    written = snprintf(buf, bufsize, "%s/%s/%s", home, SAVE_DIR, SAVE_FILE);
    if (written < 0 || (size_t)written >= bufsize) {
        return SAVE_ERR_OPEN;  /* Buffer too small */
    }
    
    return SAVE_OK;
}

/*
 * get_save_dir — Get path to save directory
 */
static SaveResult get_save_dir(char *buf, size_t bufsize)
{
    const char *home;
    int written;
    
    if (buf == NULL || bufsize == 0) {
        return SAVE_ERR_NULL_PTR;
    }
    
    home = getenv("HOME");
    if (home == NULL) {
        return SAVE_ERR_NO_HOME;
    }
    
    written = snprintf(buf, bufsize, "%s/%s", home, SAVE_DIR);
    if (written < 0 || (size_t)written >= bufsize) {
        return SAVE_ERR_OPEN;
    }
    
    return SAVE_OK;
}

/*
 * ============================================================================
 * INITIALIZATION
 * ============================================================================
 */

SaveResult save_init(void)
{
    char dir_path[512];
    SaveResult result;
    struct stat st;
    
    /* Build directory path */
    result = get_save_dir(dir_path, sizeof(dir_path));
    if (result != SAVE_OK) {
        return result;
    }
    
    /* Check if directory exists */
    if (stat(dir_path, &st) == 0) {
        /* Path exists, check if it's a directory */
        if (S_ISDIR(st.st_mode)) {
            return SAVE_OK;
        } else {
            /* Exists but not a directory — problem! */
            return SAVE_ERR_MKDIR;
        }
    }
    
    /* Directory doesn't exist, create it */
    /*
     * mkdir permissions: 0755 = rwxr-xr-x
     * Owner can read/write/execute
     * Group and others can read/execute
     */
    if (mkdir(dir_path, 0755) != 0) {
        return SAVE_ERR_MKDIR;
    }
    
    return SAVE_OK;
}

/*
 * ============================================================================
 * EXISTENCE CHECK
 * ============================================================================
 */

int save_exists(void)
{
    char path[512];
    struct stat st;
    
    if (save_get_path(path, sizeof(path)) != SAVE_OK) {
        return 0;
    }
    
    return (stat(path, &st) == 0 && S_ISREG(st.st_mode));
}

/*
 * ============================================================================
 * WRITE (SAVE)
 * ============================================================================
 */

SaveResult save_write(const Hunter *h, const QuestList *ql)
{
    char path[512];
    char backup_path[520];  /* +8 for ".bak" suffix */
    SaveResult result;
    FILE *fp;
    SaveHeader header;
    uint32_t quest_count;
    uint32_t checksum;
    
    if (h == NULL || ql == NULL) {
        return SAVE_ERR_NULL_PTR;
    }
    
    /* Build paths */
    result = save_get_path(path, sizeof(path));
    if (result != SAVE_OK) {
        return result;
    }
    
    /* Create backup if save exists */
    if (save_exists()) {
        snprintf(backup_path, sizeof(backup_path), "%s.bak", path);
        rename(path, backup_path);  /* Ignore errors on backup */
    }
    
    /* Open file for writing */
    fp = fopen(path, "wb");
    if (fp == NULL) {
        return SAVE_ERR_OPEN;
    }
    
    /*
     * Calculate checksum over all data.
     * We need to compute this before writing the header.
     */
    checksum = save_compute_checksum(h, sizeof(*h));
    checksum ^= save_compute_checksum(&ql->count, sizeof(ql->count));
    checksum ^= save_compute_checksum(ql->quests, sizeof(Quest) * ql->count);
    
    /* Prepare header */
    header.magic = SAVE_MAGIC;
    header.version = SAVE_VERSION;
    header.flags = 0;
    header.checksum = checksum;
    
    /* Write header */
    if (fwrite(&header, sizeof(header), 1, fp) != 1) {
        fclose(fp);
        return SAVE_ERR_WRITE;
    }
    
    /* Write Hunter data */
    if (fwrite(h, sizeof(*h), 1, fp) != 1) {
        fclose(fp);
        return SAVE_ERR_WRITE;
    }
    
    /* Write quest count */
    quest_count = ql->count;
    if (fwrite(&quest_count, sizeof(quest_count), 1, fp) != 1) {
        fclose(fp);
        return SAVE_ERR_WRITE;
    }
    
    /* Write quests */
    if (quest_count > 0) {
        if (fwrite(ql->quests, sizeof(Quest), quest_count, fp) != quest_count) {
            fclose(fp);
            return SAVE_ERR_WRITE;
        }
    }
    
    fclose(fp);
    return SAVE_OK;
}

/*
 * ============================================================================
 * READ (LOAD)
 * ============================================================================
 */

SaveResult save_read(Hunter *h, QuestList *ql)
{
    char path[512];
    SaveResult result;
    FILE *fp;
    SaveHeader header;
    uint32_t quest_count;
    uint32_t computed_checksum;
    
    if (h == NULL || ql == NULL) {
        return SAVE_ERR_NULL_PTR;
    }
    
    /* Build path */
    result = save_get_path(path, sizeof(path));
    if (result != SAVE_OK) {
        return result;
    }
    
    /* Open file for reading */
    fp = fopen(path, "rb");
    if (fp == NULL) {
        return SAVE_ERR_OPEN;
    }
    
    /* Read header */
    if (fread(&header, sizeof(header), 1, fp) != 1) {
        fclose(fp);
        return SAVE_ERR_READ;
    }
    
    /* Verify magic number */
    if (header.magic != SAVE_MAGIC) {
        fclose(fp);
        return SAVE_ERR_MAGIC;
    }
    
    /* Check version */
    if (header.version != SAVE_VERSION) {
        fclose(fp);
        return SAVE_ERR_VERSION;
    }
    
    /* Read Hunter data */
    if (fread(h, sizeof(*h), 1, fp) != 1) {
        fclose(fp);
        return SAVE_ERR_READ;
    }
    
    /* Read quest count */
    if (fread(&quest_count, sizeof(quest_count), 1, fp) != 1) {
        fclose(fp);
        return SAVE_ERR_READ;
    }
    
    /* Sanity check quest count */
    if (quest_count > MAX_QUESTS) {
        fclose(fp);
        return SAVE_ERR_READ;
    }
    
    /* Initialize quest list */
    questlist_init(ql);
    ql->count = quest_count;
    
    /* Read quests */
    if (quest_count > 0) {
        if (fread(ql->quests, sizeof(Quest), quest_count, fp) != quest_count) {
            fclose(fp);
            return SAVE_ERR_READ;
        }
    }
    
    fclose(fp);
    
    /* Verify checksum */
    computed_checksum = save_compute_checksum(h, sizeof(*h));
    computed_checksum ^= save_compute_checksum(&quest_count, sizeof(quest_count));
    computed_checksum ^= save_compute_checksum(ql->quests, sizeof(Quest) * quest_count);
    
    if (computed_checksum != header.checksum) {
        return SAVE_ERR_CHECKSUM;
    }
    
    return SAVE_OK;
}

/*
 * ============================================================================
 * DELETE
 * ============================================================================
 */

SaveResult save_delete(void)
{
    char path[512];
    SaveResult result;
    
    result = save_get_path(path, sizeof(path));
    if (result != SAVE_OK) {
        return result;
    }
    
    if (remove(path) != 0) {
        return SAVE_ERR_OPEN;  /* Could not delete */
    }
    
    return SAVE_OK;
}

/*
 * ============================================================================
 * ERROR STRINGS
 * ============================================================================
 */

const char *save_result_string(SaveResult result)
{
    switch (result) {
        case SAVE_OK:           return "Success";
        case SAVE_ERR_NULL_PTR: return "Null pointer";
        case SAVE_ERR_NO_HOME:  return "HOME environment variable not set";
        case SAVE_ERR_MKDIR:    return "Could not create save directory";
        case SAVE_ERR_OPEN:     return "Could not open file";
        case SAVE_ERR_READ:     return "Read error";
        case SAVE_ERR_WRITE:    return "Write error";
        case SAVE_ERR_MAGIC:    return "Invalid file format (bad magic)";
        case SAVE_ERR_VERSION:  return "Incompatible save version";
        case SAVE_ERR_CHECKSUM: return "File corrupted (checksum mismatch)";
        case SAVE_ERR_BACKUP:   return "Could not create backup";
        default:                return "Unknown error";
    }
}
