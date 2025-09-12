#include "chore.hpp"
#include "dll.hpp"

extern "C"
{
#include "data_structures.h"
}

#include <array>

Chores::Chores(void)
{

}

chore_t* Chores::get_chore_by_port(uint8_t port)
{
    for (uint8_t i=0; i<NUM_CHORES; i++)
    {
        if (chore_list[i].port == port)
        {
            return chore_list[i];
        }
    }
}

void Chores::update_chore_status(rtc_reading_t reading)  // updates chore status but does not change the shown colors
{        
    chore_t chore;
    for (uint8_t i=0; i<NUM_CHORES; i++)
    {
        chore = chores[i];
        chore_status_t chore_status = check_chore_status(rtc_reading, chore);
        switch (chore_status)
        {
            case GOOD:
                pixel_colors[i] = GOOD_COLOR;
                break;
            case WARNING:
                pixel_colors[i] = WARNING_COLOR;
                break;
            case OVERDUE:
                pixel_colors[i] = OVERDUE_LOW_PRIORITY_COLOR;
                overdue_priorities[i] = chore.priority;
                num_overdue_chores += 1;
                break;
        }
    }
}

void Chores::reorder_chores(uint8_t ports[NUM_CHORES])
{
    // the dumb inefficent way, but it's simple and works
    // todo swap i and j for clarity
    std::array<chore_t, NUM_CHORES> new_chores;
    for (uint8_t i_port=0; i_port<NUM_CHORES; i_port++)
    {
        for (uint8_t j_chore=0; j_chore<NUM_CHORES; j_chore++)
        {
            if (ports[i_port] == this->chore_list[j_chore].port)
            {
                new_chores[i_port] = this->chore_list[j_chore];
                break;
            }
        }
    }
    this->chore_list = new_chores;
}