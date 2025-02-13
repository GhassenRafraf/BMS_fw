#ifndef BMS_CONFIG_H
#define BMS_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/*==============================================================================
  Battery Management System Configuration Parameters
==============================================================================*/

/* --- Battery Voltage Thresholds (in Volts) --- */
#define BMS_CELL_VOLTAGE_MIN   3.0f    // Minimum safe cell voltage
#define BMS_CELL_VOLTAGE_MAX   4.2f    // Maximum safe cell voltage

/* --- Temperature Limits (in °C) --- */
#define BMS_TEMP_MIN           -20     // Minimum operating temperature
#define BMS_TEMP_MAX           60      // Maximum operating temperature

/* --- Balancing Parameters --- */
#define BMS_BALANCE_VOLTAGE_DIFF   0.05f  // Minimum voltage difference for triggering cell balancing (Volts)

/* --- State-of-Charge (SOC) Parameters --- */
#define BMS_SOC_INITIAL        100     // Initial SOC percentage

#ifdef __cplusplus
}
#endif

#endif /* BMS_CONFIG_H */
