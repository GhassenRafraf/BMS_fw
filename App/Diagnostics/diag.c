//
// Created by Ghassen on 2/13/2025.
//

#include "diag.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>

extern UART_HandleTypeDef huart2;

void diag_Init(void)
{
    /*
     * TODO : Initialize any diagnostic peripherals or resources if needed.
     * we assume UART is already set up.
     */
}

void diag_Log(DiagLevel_t level, const char *message)
{
    char logBuffer[128];
    const char *levelStr = "";

    switch (level)
    {
        case DIAG_LEVEL_INFO:
            levelStr = "INFO: ";
            break;
        case DIAG_LEVEL_WARNING:
            levelStr = "WARNING: ";
            break;
        case DIAG_LEVEL_ERROR:
            levelStr = "ERROR: ";
            break;
        default:
            levelStr = "UNKNOWN: ";
            break;
    }

    /* Format the message */
    snprintf(logBuffer, sizeof(logBuffer), "%s%s\r\n", levelStr, message);

    /* Transmit the log message over UART. */
    HAL_UART_Transmit(&huart2, (uint8_t*)logBuffer, strlen(logBuffer), HAL_MAX_DELAY);
}
