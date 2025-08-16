#include "pico/stdlib.h"

extern "C"
{
#include "config.h"
#include "utilities.h"
}

#include <stdio.h>

#include "Adafruit_NeoPixel.hpp"

int main(void)
{
    stdio_init_all();

    busy_wait_ms(STARTUP_WAIT);

    printf("Starting program chore-board, hash: %s\n", COMMIT_HASH);

    setup_digital_output(FUNSIES_LED_PIN, 0);

    while (1)
    {
        busy_wait_ms(1000);
        gpio_put(FUNSIES_LED_PIN, 1);
        busy_wait_ms(1000);
        gpio_put(FUNSIES_LED_PIN, 0);
    }

    while(1);
}