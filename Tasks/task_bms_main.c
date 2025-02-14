//
// Created by Ghassen on 2/12/2025.
//
#include "FreeRTOS.h"
#include "task.h"
#include "bms_state.h"
#include "diag.h"

void Task_BMS_Main(void *argument)
{
    // Initialize the BMS State Machine (including SOC & SOH modules)
    BMS_StateMachine_Init();

    // Main loop: periodically update the state machine
    for (;;)
    {
        BMS_StateMachine_Update();
        vTaskDelay(pdMS_TO_TICKS(100));  // Run every 100ms
    }
}
