#include "chore.hpp"

#include <array>

Chores::Chores(void)
{

}

chore_t Chores::get_chore_by_port(uint8_t port)
{

}

void Chores::update_chore_status(rtc_reading_t reading)  // updates chore status but does not change the shown colors
{

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