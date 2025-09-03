#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdint.h>

#include "config.h"

typedef enum {
    DAY_OF_MONTH,
    DAY_OF_WEEK,
    PERIODIC
} chore_type_t;

typedef enum {
    GOOD,
    WARNING,
    OVERDUE
} chore_status_t;

typedef struct {
    char str_id[ID_LENGTH];
    uint8_t port;
    uint32_t deadline;  // interpretation changes depending on chore type. See comment below
    uint32_t warning_length_mintues;
    uint8_t priority;
    chore_type_t chore_type;
    int64_t time_last_done;  // unix epoch
} chore_t;

/* Deadline interpretation by chore type:
    * Day of month: month day (1-28). Don't put 29, 30, or 31 if you value your sanity...
    * Day of week: Week day (0-6). Sunday is 0.
    * Periodic: Interval in mintues. 
*/

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} color_t;

typedef struct {
    chore_t chores[NUM_CHORES];
    uint32_t good_color;
    uint32_t warn_color;
    uint32_t overdue_color;
    uint32_t low_priority_overdue_color;
} settings_packet_t;


#endif