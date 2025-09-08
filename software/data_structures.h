#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdint.h>

#include "config.h"

/* Deadline interpretation by chore type:
    * Day of month: LSB is month day (1-28). Don't put 29, 30, or 31 if you value your sanity... The rest is the time of day in mintues
    * Day of week: Week day (0-6). Sunday is 0.
    * Periodic: Interval in mintues. 
    * todo add a setting to let the first two set what time of day to trigger
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
    uint8_t  max_overdue_chores; // max before lower priority chores get assigned a different color
} settings_packet_t;


#endif