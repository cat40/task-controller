#include "pico/stdlib.h"

extern "C"
{
#include "config.h"
#include "utilities.h"
#include "data_structures.h"
}

#include <stdio.h>
#include <stdint.h>

#include "Adafruit_NeoPixel.hpp"
#include "button_matrix.hpp"
#include "settings.hpp"
#include "eeprom.hpp"
#include "pcf8523.hpp"

Adafruit_NeoPixel rgb1(DEFAULT_NUM_PIXELS, RGB_1_PIN, PIXEL_PARAMETERS);
Adafruit_NeoPixel rgb2(DEFAULT_NUM_PIXELS, RGB_2_PIN, PIXEL_PARAMETERS);
Adafruit_NeoPixel rgb3(DEFAULT_NUM_PIXELS, RGB_3_PIN, PIXEL_PARAMETERS);

ButtonMatrix buttons(MATRIX_ROWS, MATRIX_COLUMNS, NUM_MATRIX_ROWS, NUM_MATRIX_COLUMNS, 200);

Eeprom eeprom (I2C, EEPROM_ADDRESS);
Settings settings(&eeprom);

Pcf8523 rtc(I2C);
rtc_reading_t rtc_reading;

chore_t chores[NUM_CHORES];

static void setup(void);
static void blink(void);
static chore_status_t check_chore_status(rtc_reading_t time, chore_t chore);
static int64_t rtc_reading_to_epoch(rtc_reading_t rtc_reading);

int main(void)
{
    stdio_init_all();

    busy_wait_ms(STARTUP_WAIT);

    printf("Starting program chore-board, hash: %s\n", COMMIT_HASH);

    setup();

    rgb1.updateLength(30);

    uint32_t hue = 0;

    // todo pull chore list from settings

    // while (1)
    // {
    //     rgb1.fill(rgb1.ColorHSV(hue));
    //     rgb1.setBrightness(0x0f);
    //     rgb1.show();
    //     busy_wait_ms(25);
    //     hue += 256;
    //     printf("color: %u\n", hue);
    // }

    while(1)
    {
        chore_t chore;
        rtc.get_reading(&rtc_reading);
        for (uint16_t i=0; i<NUM_CHORES; i++)
        {
            chore = chores[i];
            check_chore_status(rtc_reading, chore);
        }
        busy_wait_ms(5000);  // give the rtc time to actually be an rtc
    }
}

static void setup(void)
{
    setup_digital_output(FUNSIES_LED_PIN, 1);

    buttons.init();
}

static chore_status_t check_chore_status(rtc_reading_t time, chore_t chore)
{
    if (chore.chore_type == PERIODIC)
    {
        int64_t current_epoch = rtc_reading_to_epoch(time);
        int64_t time_since_last_done = current_epoch - chore.time_last_done;
        if(time_since_last_done/60 > chore.deadline)
        {
            return OVERDUE;
        }
        else if(time_since_last_done/60 >= (chore.deadline-chore.warning_length_mintues))
        {
            return WARNING;
        }
        return GOOD;
    }
}

static int64_t rtc_reading_to_epoch(rtc_reading_t rtc_reading)
{
    const static uint16_t days_passed_by_month_normal[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
    const static uint16_t days_passed_by_month_leap[] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };
    int64_t time = 0;
    time += ((rtc_reading.year-1970)*365 + rtc_reading.year/4)*24*60*60;  // might be off by a few days
    if (rtc_reading.year % 4 == 0)
    {
        time += (days_passed_by_month_leap[rtc_reading.month])*24*60*60; // todo implement days per month
    }
    else
    {
        time += (days_passed_by_month_normal[rtc_reading.month])*24*60*60; // todo implement days per month
    }
    time += rtc_reading.day*24*60*60;
    time += rtc_reading.hour*60*60;
    time += rtc_reading.minute*60;
    time += rtc_reading.second;
    return time;
}

static void blink(void)
{
    busy_wait_ms(1000);
    gpio_put(FUNSIES_LED_PIN, 1);
    busy_wait_ms(1000);
    gpio_put(FUNSIES_LED_PIN, 0);
}