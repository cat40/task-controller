#include "pico/stdlib.h"

extern "C"
{
#include "config.h"
#include "utilities.h"
}

#include <stdio.h>
#include <stdint.h>

#include "Adafruit_NeoPixel.hpp"
#include "button_matrix.hpp"

Adafruit_NeoPixel rgb1(DEFAULT_NUM_PIXELS, RGB_1_PIN, PIXEL_PARAMETERS);
Adafruit_NeoPixel rgb2(DEFAULT_NUM_PIXELS, RGB_2_PIN, PIXEL_PARAMETERS);
Adafruit_NeoPixel rgb3(DEFAULT_NUM_PIXELS, RGB_3_PIN, PIXEL_PARAMETERS);

ButtonMatrix buttons(MATRIX_ROWS, MATRIX_COLUMNS, NUM_MATRIX_ROWS, NUM_MATRIX_COLUMNS, 200);

static void setup(void);

int main(void)
{
    stdio_init_all();

    busy_wait_ms(STARTUP_WAIT);

    printf("Starting program chore-board, hash: %s\n", COMMIT_HASH);

    setup();

    rgb1.updateLength(30);

    uint32_t hue = 0;

    while (1)
    {
        // busy_wait_ms(1000);
        // gpio_put(FUNSIES_LED_PIN, 1);
        // busy_wait_ms(1000);
        // gpio_put(FUNSIES_LED_PIN, 0);
        rgb1.fill(rgb1.ColorHSV(hue));
        rgb1.setBrightness(0x0f);
        rgb1.show();
        busy_wait_ms(25);
        hue += 256;
        printf("color: %u\n", hue);
    }

    while(1);
}

static void setup(void)
{
    setup_digital_output(FUNSIES_LED_PIN, 1);

    buttons.init();
}