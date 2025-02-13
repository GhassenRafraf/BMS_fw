#include "soh.h"
#include "diag.h"
#include <stdio.h>

static float soh = 100.0f;

/**
 * @brief Initialize the SOH estimation module.
 */
void SOH_Init(void) {
    soh = 100.0f;
    diag_Log(DIAG_LEVEL_INFO, "SOH module initialized");
}

/**
 * @brief Update the SOH estimation.
 *
 * A basic degradation model is applied: for each full cycle, the SOH decreases
 * by a fixed percentage (for example, 0.1%). In a real application, this could be
 * based on battery chemistry, temperature, and other stress factors.
 *
 * @param cycleCount Number of full charge-discharge cycles completed.
 */
void SOH_Update(unsigned int cycleCount) {
    // TODO: Implement a more realistic SOH estimation model.
    // Simple degradation: reduce SOH by 0.1% per cycle.
    float degradation = cycleCount * 0.1f;
    soh = 100.0f - degradation;

    if (soh < 0.0f) {
        soh = 0.0f;
    }

    // log SOH updates
     char buf[64];
     snprintf(buf, sizeof(buf), "SOH updated: %.2f%%", soh);
     diag_Log(DIAG_LEVEL_INFO, buf);
}

/**
 * @brief Retrieve the current SOH value.
 *
 * @return The current SOH as a percentage.
 */
float SOH_Get(void) {
    return soh;
}
