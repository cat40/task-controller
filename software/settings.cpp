#include "settings.hpp"
#include "eeprom.hpp"

Settings::Settings(void)
{

}

void Settings::write(void)
{

}

void Settings::read(void)
{

}

void Settings::get_chore(uint8_t port, chore_t* chore)
{
    chore = &packet->chores[port];
}

void Settings::set_chore(uint8_t port, chore_t* chore)
{
    packet->chores[port] = *chore;
}

#include <stdint.h>