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
    // Configurar como salidas
    gpio_set_direction(GPIO_NUM_0,GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_2,GPIO_MODE_OUTPUT);

    // Configurar como entradas
    gpio_set_direction(GPIO_NUM_26,GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_NUM_27,GPIO_MODE_INPUT);

    gpio_set_level(GPIO_NUM_0,0);
    gpio_set_level(GPIO_NUM_2,0);
}
