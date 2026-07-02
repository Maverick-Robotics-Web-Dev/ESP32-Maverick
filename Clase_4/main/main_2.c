#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/gptimer.h"

// Identificador del Timer
gptimer_handle_t TMR0=NULL;

// Variables Global
bool flagTime=false;

void GPIOInit(void);
void GPTimerInit(void);

bool IRAM_ATTR TMR0AlarmEventCb(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx )
{
    flagTime=true;

    gpio_set_level(GPIO_NUM_18,0);
    gptimer_stop(TMR0);
    gptimer_disable(TMR0);

    return true;
}

void app_main(void)
{
    GPIOInit();
    GPTimerInit();

    while (1)
    {

        if(gpio_get_level(GPIO_NUM_26)==0)
        {
            vTaskDelay(pdMS_TO_TICKS(1000));
            printf("Encender sistema de Alarma Activado\n");
            gpio_set_level(GPIO_NUM_18,1);
            printf("Sistema de conteo iniciado\n");
            gptimer_enable(TMR0); // Habilitar el Timer
            gptimer_start(TMR0); // Iniciar el Timer
        }

        if(flagTime==true)
        {
            flagTime=false;
            printf("Tiempo Vencido\n");
            printf("Sistema de Alarma Desactivado\n");
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }

}

void GPIOInit(void){

    gpio_set_direction(GPIO_NUM_18,GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_26,GPIO_MODE_INPUT);
    gpio_set_level(GPIO_NUM_18,0);


    
    
}

void GPTimerInit(void){
    gptimer_config_t tmr0config={
        .clk_src=GPTIMER_CLK_SRC_APB, // 80 Mhz
        .direction=GPTIMER_COUNT_UP, // Ascendente
        .resolution_hz=1000000,// 1 Mhz
        .intr_priority=0,
        .flags.intr_shared=0
    };

    // Asignar la configuracion
    gptimer_new_timer(&tmr0config, &TMR0);

    // Configurar la funcion
    gptimer_event_callbacks_t eventAlarmCb={
        .on_alarm=TMR0AlarmEventCb
    };

    gptimer_register_event_callbacks(TMR0, &eventAlarmCb, NULL); // Registrar funcion callback
    

    gptimer_alarm_config_t alarmConfig={
        .alarm_count=10000000,// pulsos para genera 10seg
        .reload_count=0,
        .flags.auto_reload_on_alarm=true
    };

    // Establecer la configuracion de la alarma
    gptimer_set_alarm_action(TMR0, &alarmConfig);

    
    
}