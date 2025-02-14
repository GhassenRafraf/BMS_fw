//
// Created by Ghassen on 2/12/2025.
//
#include "FreeRTOS.h"
#include "task.h"
#include "batt_measure.h"
#include "diag.h"
#include <stdio.h>

void Task_Data_Acquisition(void *argument)
{
    for (;;)
    {
        // Read battery measurements
        float packVoltage = Get_PackVoltage();
        float current = Get_Current();
        float cellVoltage0 = Get_CellVoltage(0);
        float cellVoltage1 = Get_CellVoltage(1);
        float cellVoltage2 = Get_CellVoltage(2);
        float cellVoltage3 = Get_CellVoltage(3);



        // optional : log measurements to console
        char buf[128];
        snprintf(buf, sizeof(buf), "DataAcq: Pack=%.2f V, Current=%.2f A, Cell0=%.2f V, Cell1=%.2f V, Cell2=%.2f V, Cell3=%.2f V", packVoltage, current, cellVoltage0, cellVoltage1, cellVoltage2, cellVoltage3);
        diag_Log(DIAG_LEVEL_INFO, buf);

        // TODO: add logic to process measurements

        // Delay until next measurement (adjust period as necessary)
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
