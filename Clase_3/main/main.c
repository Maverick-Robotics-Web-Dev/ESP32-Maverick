#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

void GPIOInit(void);

void app_main(void)
{
    GPIOInit();

    while(1)
    {
        if(gpio_get_level(GPIO_NUM_26)==0)
        {
            vTaskDelay(pdMS_TO_TICKS(10));
            gpio_set_level(GPIO_NUM_0,1);
        }else{
            gpio_set_level(GPIO_NUM_0,0);
        }

        if(gpio_get_level(GPIO_NUM_27)==0)
        {
            vTaskDelay(pdMS_TO_TICKS(10));
            gpio_set_level(GPIO_NUM_2,1);
        }else{
            gpio_set_level(GPIO_NUM_2,0);
        }
    }

}

void GPIOInit(void)
{
    gpio_config_t gpioConfigOut={
        .pin_bit_mask=(1<<GPIO_NUM_0) | (1<<GPIO_NUM_2),
        .mode=GPIO_MODE_OUTPUT,
        .pull_up_en=GPIO_PULLUP_DISABLE,
        .pull_down_en=GPIO_PULLDOWN_DISABLE,
        .intr_type=GPIO_INTR_DISABLE
    };

    gpio_config(&gpioConfigOut);

    gpio_config_t gpioConfigIn={
        .pin_bit_mask=(1<<GPIO_NUM_26) | (1<<GPIO_NUM_27),
        .mode=GPIO_MODE_INPUT,
        .pull_up_en=GPIO_PULLUP_DISABLE,
        .pull_down_en=GPIO_PULLDOWN_DISABLE,
        .intr_type=GPIO_INTR_DISABLE
    };

    gpio_config(&gpioConfigIn);

    gpio_set_level(GPIO_NUM_0,0);
    gpio_set_level(GPIO_NUM_2,0);
}
