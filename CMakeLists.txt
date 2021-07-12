cmake_minimum_required(VERSION 3.12)

#include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)
include(./pico-sdk/pico_sdk_init.cmake)
pico_sdk_init()

#project(main C CXX ASM)
project(main)
#set(CMAKE_C_STANDARD 11)
#set(CMAKE_CXX_STANDARD 17)

#add_subdirectory(./src)

add_executable(main src/main.c)

# Pull in our pico_stdlib which pulls in commonly used features
#target_link_libraries(main pico_stdlib)

# create map/bin/hex file etc.
#pico_add_extra_outputs(main)

# add url via pico_set_program_url
#example_auto_set_url(main)

target_link_libraries(main pico_stdlib hardware_pwm hardware_adc)

# create map/bin/hex file etc.
pico_add_extra_outputs(main)

# add url via pico_set_program_url
#example_auto_set_url(main)

