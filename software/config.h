#ifndef CONFIG_H
#define CONFIG_H

#include "pico/stdlib.h"
#include "hardware/uart.h"

#define STARTUP_WAIT        3000

// pin assignments
#define FUNSIES_LED_PIN 4

#define RGB_1_PIN       5
#define RGB_2_PIN       6
#define RGB_3_PIN       7

// there are 10k pullups on the columns due to likely high wiring capacitence
const static uint KEYPAD_ROWS[]    = {8, 9, 10, 11, 12, 13, 14};
const static uint KEYPAD_COLUMNS[] = {15, 16, 17, 21, 22, 23, 24};

#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define UART_ID uart0
#define UART_BAUD_RATE 460800

#define I2C_SDA         2
#define I2C_SCL         3

#define SPI_SCK         18
#define SPI_MOSI        19
#define SPI_MISO        20
#define SD_CS           25

#define PHOTORESISTOR_PIN   26
#define BRIGHTNESS_POT      27
#define RTC_INT             28
#define BUTTON              29

#endif