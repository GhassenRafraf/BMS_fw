#include "cell_balance.h"
#include "batt_measure.h"   // For Get_CellVoltage()
#include "bms_config.h"     // For BMS_BALANCE_VOLTAGE_DIFF and other thresholds
#include "diag.h"           // For logging
#include <stdio.h>
#include "stm32f4xx_hal.h"  // For HAL_GPIO_WritePin()

// Example: define the balancing GPIO port and pins for each cell.
// Adjust these definitions to match your hardware.
#define BALANCE_GPIO_PORT     GPIOB
#define BALANCE_CELL0_PIN     GPIO_PIN_0
#define BALANCE_CELL1_PIN     GPIO_PIN_1
#define BALANCE_CELL2_PIN     GPIO_PIN_2
#define BALANCE_CELL3_PIN     GPIO_PIN_3

// Create an array of pins corresponding to each cell.
static const uint16_t balancePins[] = {
        BALANCE_CELL0_PIN,
        BALANCE_CELL1_PIN,
        BALANCE_CELL2_PIN,
        BALANCE_CELL3_PIN
};

/**
 * @brief Initialize the balancing system.
 */
void Cell_Balance_Init(void)
{
    // Typically, GPIO configuration is handled in MX_GPIO_Init().
    // Here we can log that the balancing system is ready.
    diag_Log(DIAG_LEVEL_INFO, "Cell balancing initialized.");
}

/**
 * @brief Enable or disable balancing for a given cell by controlling its GPIO.
 */
void Cell_Balance_Set(uint8_t cell, bool enable)
{
    if (cell >= sizeof(balancePins)/sizeof(balancePins[0]))
        return;

    if (enable)
    {
        // Activate the balancing resistor (assuming active HIGH).
        HAL_GPIO_WritePin(BALANCE_GPIO_PORT, balancePins[cell], GPIO_PIN_SET);
        char buf[64];
        snprintf(buf, sizeof(buf), "Balancing enabled for cell %d", cell);
        diag_Log(DIAG_LEVEL_INFO, buf);
    }
    else
    {
        // Deactivate balancing.
        HAL_GPIO_WritePin(BALANCE_GPIO_PORT, balancePins[cell], GPIO_PIN_RESET);
        char buf[64];
        snprintf(buf, sizeof(buf), "Balancing disabled for cell %d", cell);
        diag_Log(DIAG_LEVEL_INFO, buf);
    }
}

/**
 * @brief Evaluate cell voltages and update balancing circuitry.
 *
 * This example uses a simple algorithm:
 * - Calculate the average cell voltage.
 * - If a cell's voltage exceeds the average by more than BMS_BALANCE_VOLTAGE_DIFF,
 *   then enable balancing on that cell.
 * - Otherwise, disable balancing.
 */
void Cell_Balance_Update(void)
{
    float cellVoltages[NUM_CELLS];
    float totalVoltage = 0.0f;

    // Retrieve each cell's voltage.
    for (uint8_t i = 0; i < NUM_CELLS; i++)
    {
        cellVoltages[i] = Get_CellVoltage(i);
        totalVoltage += cellVoltages[i];
    }

    // Calculate the average voltage.
    float avgVoltage = totalVoltage / NUM_CELLS;

    // Check each cell against the average plus a defined threshold.
    for (uint8_t i = 0; i < NUM_CELLS; i++)
    {
        if (cellVoltages[i] > (avgVoltage + BMS_BALANCE_VOLTAGE_DIFF))
        {
            // Enable balancing if the cell voltage is too high.
            Cell_Balance_Set(i, true);
        }
        else
        {
            // Otherwise, disable balancing.
            Cell_Balance_Set(i, false);
        }
    }
}
