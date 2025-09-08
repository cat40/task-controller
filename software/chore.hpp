#ifndef CHORE_H
#define CHORE_H

#include <stdint.h>
#include <array>

extern "C"
{
#include "config.h"
}

#include "pcf8523.hpp"

typedef enum {
    DAY_OF_MONTH,
    DAY_OF_WEEK,
    PERIODIC
} chore_type_t;

typedef struct {
    char str_id[ID_LENGTH];
    uint8_t port;
    uint32_t deadline;  // interpretation changes depending on chore type. See comment below
    uint32_t warning_length_mintues;
    chore_type_t chore_type;
    int64_t time_last_done;  // unix epoch
} chore_t;

class Chores
{
    public:
        Chores(void);
        void reorder_chores(uint8_t ports[NUM_CHORES]);
        chore_t get_chore_by_port(uint8_t port);
        void update_chore_status(rtc_reading_t reading);  // updates chore status but does not change the shown colors
        std::array<chore_t, NUM_CHORES> chore_list;
}

#endif