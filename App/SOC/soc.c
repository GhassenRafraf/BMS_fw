#include "soc.h"
#include "bms_config.h"  // For initial SOC value or capacity if needed
#include "diag.h"
#include <stdio.h>

// Example battery capacity (in Ampere-hours)
#define BATTERY_CAPACITY_AH   10.0f

// Conversion constant: 1 Ah = 3600 Coulombs
#define AH_TO_COULOMB         3600.0f

// Static variables to hold SOC and accumulated charge (in Coulombs)
static float soc = BMS_SOC_INITIAL;  // Start at the configured initial SOC percentage
static float accumulatedCharge = 0.0f;

/**
 * @brief Initialize the SOC estimation module.
 */
void SOC_Init(void) {
    // Initialize accumulated charge based on initial SOC
    accumulatedCharge = (soc / 100.0f) * BATTERY_CAPACITY_AH * AH_TO_COULOMB;
    diag_Log(DIAG_LEVEL_INFO, "SOC module initialized");
}

/**
 * @brief Update the SOC estimation using a basic coulomb counting method.
 *
 * @param current   Measured current in Amps (discharge: positive, charge: negative).
 * @param deltaTime Time in seconds since the last update.
 */
void SOC_Update(float current, float deltaTime) {
    // Calculate the change in charge (Coulombs)
    float deltaCharge = current * deltaTime;

    // Update the accumulated charge
    accumulatedCharge -= deltaCharge;  // subtract discharge; add charge when current is negative

    // Compute SOC as a percentage
    soc = (accumulatedCharge / (BATTERY_CAPACITY_AH * AH_TO_COULOMB)) * 100.0f;

    // Clamp the SOC value between 0 and 100%
    if (soc > 100.0f) {
        soc = 100.0f;
    } else if (soc < 0.0f) {
        soc = 0.0f;
    }

    // Optionally, log the updated SOC (comment out if too verbose)
    char buf[64];
    snprintf(buf, sizeof(buf), "SOC updated: %.2f%%", soc);
    diag_Log(DIAG_LEVEL_INFO, buf);
}

/**
 * @brief Retrieve the current SOC value.
 *
 * @return The current SOC as a percentage.
 */
float SOC_Get(void) {
    return soc;
}
