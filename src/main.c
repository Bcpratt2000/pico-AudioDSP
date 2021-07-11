/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/pwm.h"

int main() {
#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else
    const uint LOUT_PIN = 20;
    const uint ROUT_PIN = 21;

    gpio_set_function(LOUT_PIN, GPIO_FUNC_PWM);
    gpio_set_function(ROUT_PIN, GPIO_FUNC_PWM);
    
    const uint LOUT_SLICE = pwm_gpio_to_slice_num(LOUT_PIN);
    const uint ROUT_SLICE = pwm_gpio_to_slice_num(ROUT_PIN);

    // pwm_set_gpio_level(LOUT_PIN, (65535*(rand()%98)+1)/100);

    pwm_set_enabled(LOUT_SLICE, true);

    while(true){
        pwm_set_gpio_level(LOUT_PIN, (65535*(rand()%98)+1)/100);
        sleep_ms(1000);

    }
#endif
}
