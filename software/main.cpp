#include "pico/stdlib.h"

#include "config.h"

#include <stdio.h>

#include "Adafruit_NeoPixel.hpp"



int main(void)
{
    stdio_init_all();

    busy_wait_ms(STARTUP_WAIT);

    printf("Starting program Pokey, hash: %s\n", COMMIT_HASH);

    while(1);
}