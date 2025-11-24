#include <stdio.h>
#include <stdint.h>
#include "mxc_device.h"
#include "board.h"
#include "mxc_delay.h"
#include "gpio.h"

#define NUM_LEDS 8

#define BTN_PORT MXC_GPIO0
#define BTN_PIN  MXC_GPIO_PIN_2

typedef struct {
    mxc_gpio_regs_t *port;
    uint32_t mask;
} pin_t;

pin_t leds[NUM_LEDS] = {
    {MXC_GPIO2, MXC_GPIO_PIN_3}, // 1
    {MXC_GPIO2, MXC_GPIO_PIN_4}, // 2
    {MXC_GPIO1, MXC_GPIO_PIN_0}, // 3
    {MXC_GPIO0, MXC_GPIO_PIN_7}, // 4
    {MXC_GPIO0, MXC_GPIO_PIN_5}, // 5
    {MXC_GPIO0, MXC_GPIO_PIN_6}, // 6
    {MXC_GPIO2, MXC_GPIO_PIN_6}, // 7
    {MXC_GPIO2, MXC_GPIO_PIN_7}  // 8
};

volatile int current_mode = 0;

void led_on(int index) {
    MXC_GPIO_OutClr(leds[index].port, leds[index].mask);
}

void led_off(int index) {
    MXC_GPIO_OutSet(leds[index].port, leds[index].mask);
}

void clear_all() {
    for (int i = 0; i < NUM_LEDS; i++) led_off(i);
}

void check_button() {
    if (MXC_GPIO_InGet(BTN_PORT, BTN_PIN) == 0) {
        MXC_Delay(MXC_DELAY_MSEC(50));
        if (MXC_GPIO_InGet(BTN_PORT, BTN_PIN) == 0) {
            current_mode++;
            if (current_mode > 1) current_mode = 0;
            
            clear_all();
            MXC_Delay(MXC_DELAY_MSEC(200));
            
            while(MXC_GPIO_InGet(BTN_PORT, BTN_PIN) == 0);
        }
    }
}

int main(void)
{
    printf("8-LED Mode Switch Demo\n");

    mxc_gpio_cfg_t gpio_led;
    mxc_gpio_cfg_t gpio_btn;

    // 1. Configure LEDs
    for (int i = 0; i < NUM_LEDS; i++) {
        gpio_led.port = leds[i].port;
        gpio_led.mask = leds[i].mask;
        gpio_led.pad  = MXC_GPIO_PAD_NONE;
        gpio_led.func = MXC_GPIO_FUNC_OUT;
        
        if (leds[i].port == MXC_GPIO2) {
             gpio_led.vssel = MXC_GPIO_VSSEL_VDDIOH;
        } else {
             gpio_led.vssel = MXC_GPIO_VSSEL_VDDIO;
        }
        MXC_GPIO_Config(&gpio_led);
        led_off(i);
    }

    gpio_btn.port = BTN_PORT;
    gpio_btn.mask = BTN_PIN;
    gpio_btn.pad  = MXC_GPIO_PAD_PULL_UP;
    gpio_btn.func = MXC_GPIO_FUNC_IN;
    gpio_btn.vssel = MXC_GPIO_VSSEL_VDDIO;
    MXC_GPIO_Config(&gpio_btn);

    while (1) {
        check_button();
        
        int delay_time = 150;

        if (current_mode == 0) {
            for (int i = 0; i < NUM_LEDS/2; i++) {
                if (MXC_GPIO_InGet(BTN_PORT, BTN_PIN) == 0) break; 
                
                clear_all();
                led_on(i);
                led_on(NUM_LEDS - 1 - i);
                MXC_Delay(MXC_DELAY_MSEC(delay_time));
            }
        } else {
            for (int i = (NUM_LEDS/2) - 1; i >= 0; i--) {
                if (MXC_GPIO_InGet(BTN_PORT, BTN_PIN) == 0) break;
                
                clear_all();
                led_on(i);
                led_on(NUM_LEDS - 1 - i);
                MXC_Delay(MXC_DELAY_MSEC(delay_time));
            }
        }
    }
}