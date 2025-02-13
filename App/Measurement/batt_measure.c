//
// Created by Ghassen on 2/12/2025.
//

#include "batt_measure.h"
#include "math.h"

/* ADC Handle */
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;

/* ADC Channels */
uint32_t adcRawValues[NUM_CELLS + 2];  // ADC raw values for cells, current, temp

/* Resistor Divider Ratios */
const float voltageDividerRatio = (100.0 + 33.0) / 33.0;  // R1=100k, R2=33k

/* === Initialize Battery Measurement System === */
void BatteryMeasure_Init(void) {
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adcRawValues, NUM_CELLS + 2);
}

/* === Get Individual Cell Voltage === */
float Get_CellVoltage(uint8_t cell) {
    if (cell >= NUM_CELLS) return 0.0f;
    float adcVoltage = (adcRawValues[cell] * ADC_REF_VOLTAGE) / ADC_RESOLUTION;
    return adcVoltage * voltageDividerRatio;  // Convert back to actual voltage
}

/* === Get Pack Voltage === */
float Get_PackVoltage(void) {
    float totalVoltage = 0.0f;
    for (uint8_t i = 0; i < NUM_CELLS; i++) {
        totalVoltage += Get_CellVoltage(i);
    }
    return totalVoltage;
}

/* === Get Current Using Shunt Resistor === */
float Get_Current(void) {
    float shuntVoltage = (adcRawValues[NUM_CELLS] * ADC_REF_VOLTAGE) / ADC_RESOLUTION;
    return shuntVoltage / SHUNT_RESISTOR;  // Ohm’s Law: I = V/R
}

/* === Get Temperature from NTC Thermistor === */
float Get_Temperature(uint8_t sensor) {
    if (sensor >= 1) return 0.0f;  // Assuming 1 temp sensor
    float adcVoltage = (adcRawValues[NUM_CELLS + 1] * ADC_REF_VOLTAGE) / ADC_RESOLUTION;

    // Convert using Steinhart-Hart equation (simplified lookup method)
    float resistance = (10000.0 * adcVoltage) / (ADC_REF_VOLTAGE - adcVoltage); // Assume 10kΩ pull-up
    float temperature = 1.0 / (0.001129148 + (0.000234125 * log(resistance)) + (0.0000000876741 * pow(log(resistance), 3)));
    return temperature - 273.15;  // Convert Kelvin to Celsius
}
