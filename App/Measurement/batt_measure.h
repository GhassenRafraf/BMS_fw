//
// Created by Ghassen on 2/12/2025.
//

#ifndef BATT_MEASURE_H
#define BATT_MEASURE_H

#include "stm32f4xx_hal.h"

/* Constants */
#define NUM_CELLS 4             // Number of series cells in the battery pack
#define SHUNT_RESISTOR 0.001    // 1mΩ for current sensing (Ohms)
#define ADC_REF_VOLTAGE 3.3     // Reference voltage of ADC
#define ADC_RESOLUTION 4096.0   // 12-bit ADC resolution

/* Function Prototypes */
void BatteryMeasure_Init(void);
float Get_CellVoltage(uint8_t cell);
float Get_PackVoltage(void);
float Get_Current(void);
float Get_Temperature(uint8_t sensor);

#endif /* BATT_MEASURE_H */

