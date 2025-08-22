#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdint.h>

typedef struct {
    char str_id[16];
    uint8_t num_id;
    uint32_t timeout_interval_mintues;
    uint32_t warning_length_mintues;
    uint8_t priority;
} chore_t;

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} color_t;

typedef struct {
    chore_t chores[48];
    uint32_t good_color;
    uint32_t warn_color;
    uint32_t overdue_color;
    uint32_t low_priority_overdue_color;
} settings_packet_t;


#endif