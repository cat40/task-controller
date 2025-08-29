#ifndef SETTINGS_H
#define SETTINGS_H

extern "C"
{
#include "data_structures.h"
}

#include <stdint.h>

void write_settings(void);
void read_settings(void);

class Settings
{
    public:
        Settings(void);
        void write(void);
        void read(void);
        void get_chore(uint8_t port, chore_t* chore);
        void set_chore(uint8_t port, chore_t* chore);
        settings_packet_t* packet;
    private:
        

}

#endif