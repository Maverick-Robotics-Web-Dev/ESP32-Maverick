// Encabezados de la libreria estandar de C
#include <stdio.h>
#include <stdint.h> // Trabajar con tipos de datos enteros estandar

// Incluir librerias de ESPD-IDF
#include <freertos/FreeRTOS.h> // Definiciones internas del kernel FreeRTOS
#include <freertos/task.h> // delays

#include <driver/gpio.h> // Configuracion de pines

// Prototipo de funcion
void GPIO_Init(void);

void app_main(void)
{
    GPIO_Init();

    //Bucle infinito
    while (1)
    {
        //Escribir sobre el pin 2 logico
        gpio_set_level(GPIO_NUM_2,1);
        gpio_set_level(GPIO_NUM_5,0);
        printf('Led rojo encendido\n');

        //Retardo
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_set_level(GPIO_NUM_2,0);
        gpio_set_level(GPIO_NUM_5,1);
        printf('Led azul encendido\n');

        //Retardo
        vTaskDelay(pdMS_TO_TICKS(500));
    }
    
}

// Funcion que permite configurar a los GPIO

void GPIO_Init(void)
{
    // Configurar a GPIO2 y GPIO5
    gpio_config_t gpioConfig={
        .pin_bit_mask= (1<< GPIO_NUM_2) | (1<< GPIO_NUM_5),
        .mode= GPIO_MODE_OUTPUT,
        .pull_down_en=GPIO_PULLDOWN_DISABLE,
        .pull_up_en=GPIO_PULLUP_DISABLE,
        .intr_type=GPIO_INTR_DISABLE
    };

    // Establecer configuracion
    // gpio_config(&gpioConfig)

    // Evaluar si se configuro correctamente los pines
    if (gpio_config(&gpioConfig)==ESP_OK)
    {
        printf('Configuracion exitosa\n');
    }
    else
    {
        printf('Configuracion GPIO fallida\n');
    }
    
}