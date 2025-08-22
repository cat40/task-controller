cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD_HEADER_DIRS ${CMAKE_SOURCE_DIR}) 
set(PICO_BOARD chore_board_hw)

# add_compile_options(-fanalyzer -fstack-usage)
add_compile_options(-fstack-usage)

include(pico_sdk_import.cmake)

project(myproject_test C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(raspberry-kitten/utilities)
add_subdirectory(pi-pico-adafruit-neopixels/pico_neopixels)

# git commit hash macro, from https://stackoverflow.com/a/39739194
execute_process(
  COMMAND git describe --match="" --always --abbrev=7 --dirty
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

add_definitions("-DCOMMIT_HASH=\"${COMMIT_HASH}\"")

add_executable(choreboard
  main.cpp
)

add_compile_options(-fstack-usage)

target_link_libraries( choreboard 
    pico_stdlib
    pico_rand
    hardware_i2c
    hardware_adc
    pico_neopixel
    kitten-utilities
    kitten-matrix
)

target_link_options(choreboard PUBLIC "LINKER:--print-memory-usage,-Map=memory.map,--gc-sections")

pico_enable_stdio_usb(choreboard 1)
pico_enable_stdio_uart(choreboard 1)

pico_add_extra_outputs(choreboard)

