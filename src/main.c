/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"


int main() {
    //set clock to a more easily divisable number
    set_sys_clock_khz(144000, true);

    //set output pins
    const uint LOUT_PIN = 20;
    const uint ROUT_PIN = 21;

    const uint LIN_PIN = 26;

    //setup clipping LED
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    uint lin = 0;

    adc_init();
    adc_gpio_init(LIN_PIN);
    adc_select_input(0);

    // set pwm frequency to roughly 384khz
    const uint WRAP = 1497/4; //65535/48;

    //put output pins in pwm mode
    gpio_set_function(LOUT_PIN, GPIO_FUNC_PWM);
    gpio_set_function(ROUT_PIN, GPIO_FUNC_PWM);
    
    //get pwm slice of the two outputs
    const uint LOUT_SLICE = pwm_gpio_to_slice_num(LOUT_PIN);
    const uint ROUT_SLICE = pwm_gpio_to_slice_num(ROUT_PIN);

    //apply pwm frequency change
    pwm_set_wrap(LOUT_SLICE, WRAP);

    //enable PWM
    pwm_set_enabled(LOUT_SLICE, true);

    while(true){
        lin = adc_read();
        pwm_set_gpio_level(LOUT_PIN, (lin*WRAP)/4096);

        //calculate if is clipping
        if(lin > 4090 || lin < 4){
            gpio_put(PICO_DEFAULT_LED_PIN, 1);
        } else{
            gpio_put(PICO_DEFAULT_LED_PIN, 0);
        }

    }
}
