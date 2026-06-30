#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

bool flagBtn1=false;
bool flagBtn2=false;
uint16_t counterBtn1=0;
uint16_t counterBtn2=0;

void GPIOInit(void);

void IRAM_ATTR gpio26IsrHandler(void *args)
{
    // Tarea Breve
    flagBtn1=true;
    counterBtn1++;
    if(counterBtn1>10)
    {
        counterBtn1=0;
    }
}

void IRAM_ATTR gpio27IsrHandler(void *args)
{
    // Tarea Breve
    flagBtn2=true;
    counterBtn2++;
    if(counterBtn2>10)
    {
        counterBtn2=0;
    }
}

void app_main(void)
{
    GPIOInit();

    while(1)
    {
        if(flagBtn1==true)
        {
            flagBtn1=false;
            printf("Pulsos de Btn1: %u\n",counterBtn1);
        }

        if(flagBtn2==true)
        {
            flagBtn2=false;
            printf("Pulsos de Btn2: %u\n",counterBtn2);
        }
    }

    vTaskDelay(pdMS_TO_TICKS(100));

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
        .intr_type=GPIO_INTR_NEGEDGE
    };

    // Iniciar servicio ISR GPIO
    gpio_install_isr_service(ESP_INTR_FLAG_IRAM);

    // Asociar los GPIO a los ISR
    gpio_isr_handler_add(GPIO_NUM_26,gpio26IsrHandler,NULL);
    gpio_isr_handler_add(GPIO_NUM_27,gpio27IsrHandler,NULL);

    gpio_config(&gpioConfigIn);

    gpio_set_level(GPIO_NUM_0,0);
    gpio_set_level(GPIO_NUM_2,0);
}
