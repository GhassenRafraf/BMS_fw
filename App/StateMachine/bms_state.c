#include "bms_state.h"
#include "diag.h"
#include "bms_config.h"
#include "soc.h"
#include "soh.h"
#include "batt_measure.h"
#include <stdio.h>

// Variable to hold the current state of the BMS
static BMS_State_t currentState;

/**
 * @brief Initialize the BMS state machine.
 */
void BMS_StateMachine_Init(void) {
    currentState = BMS_STATE_INIT;
    diag_Log(DIAG_LEVEL_INFO, "BMS State Machine Initialized: INIT state");
}

/**
 * @brief Handle the INIT state logic.
 */
static void HandleInitState(void) {
    // Initialize the SOC and SOH modules.
    SOC_Init();
    SOH_Init();
    diag_Log(DIAG_LEVEL_INFO, "SOC and SOH modules initialized.");
    // TODO: add initialization for other modules as needed.
    currentState = BMS_STATE_IDLE;
}

/**
 * @brief Handle the IDLE state logic.
 */
static void HandleIdleState(void) {
    diag_Log(DIAG_LEVEL_INFO, "IDLE state: transitioning to ACTIVE.");
    currentState = BMS_STATE_ACTIVE;
}

/**
 * @brief Handle the ACTIVE state logic.
 *
 * This function updates the SOC using a simple coulomb counting algorithm
 * and checks the pack voltage to detect full discharge cycles for SOH update.
 * It also monitors for out-of-range measurements to transition into FAULT state.
 */
static void HandleActiveState(void) {
    // Assume this function is called every 100ms.
    const float deltaTime = 0.1f;

    // Get the measured current (in Amps).
    float current = Get_Current();
    // Update SOC based on the current measurement and delta time.
    SOC_Update(current, deltaTime);
    float packVoltage = Get_PackVoltage();

    // Log the updated SOC and pack voltage.
    char buf[128];
    snprintf(buf, sizeof(buf), "ACTIVE state: SOC=%.2f%%, Pack Voltage=%.2fV", SOC_Get(), packVoltage);
    diag_Log(DIAG_LEVEL_INFO, buf);

    // Static variables to track full discharge cycles.
    static uint32_t cycleCount = 0;
    static uint8_t cycleCounted = 0;

    // Define the minimum pack voltage threshold (for a 4-cell pack).
    float packVoltageMinThreshold = NUM_CELLS * BMS_CELL_VOLTAGE_MIN;

    // Check if the pack voltage indicates a full discharge cycle.
    // A little hysteresis is added: when pack voltage is below threshold + 0.5V, and we haven't yet counted this cycle.
    if ((packVoltage < (packVoltageMinThreshold + 0.5f)) && (!cycleCounted)) {
        cycleCount++;
        SOH_Update(cycleCount);
        cycleCounted = 1;
        snprintf(buf, sizeof(buf), "Cycle completed: cycleCount=%lu, new SOH=%.2f%%", cycleCount, SOH_Get());
        diag_Log(DIAG_LEVEL_INFO, buf);
    }
        // Reset the cycle flag once the battery has recharged sufficiently.
    else if (packVoltage > (packVoltageMinThreshold + 1.0f)) {
        cycleCounted = 0;
    }
    // TODO: add more logic for fault conditions here as needed.
    //fault condition: if the pack voltage is out of the expected range.
    if ((packVoltage < packVoltageMinThreshold) || (packVoltage > NUM_CELLS * BMS_CELL_VOLTAGE_MAX)) {
        diag_Log(DIAG_LEVEL_ERROR, "Pack voltage out of range! Transitioning to FAULT state.");
        currentState = BMS_STATE_FAULT;
    }
}

/**
 * @brief Handle the FAULT state logic.
 */
static void HandleFaultState(void) {
    diag_Log(DIAG_LEVEL_ERROR, "FAULT state: transitioning to SHUTDOWN.");
    currentState = BMS_STATE_SHUTDOWN;
}

/**
 * @brief Handle the SHUTDOWN state logic.
 */
static void HandleShutdownState(void) {
    diag_Log(DIAG_LEVEL_WARNING, "SHUTDOWN state: system is shutting down.");
    // Implement any shutdown procedures here.
}

/**
 * @brief Periodic update function for the BMS state machine.
 *
 * This function should be called regularly from the BMS main task.
 */
void BMS_StateMachine_Update(void) {
    switch (currentState) {
        case BMS_STATE_INIT:
            HandleInitState();
            break;
        case BMS_STATE_IDLE:
            HandleIdleState();
            break;
        case BMS_STATE_ACTIVE:
            HandleActiveState();
            break;
        case BMS_STATE_FAULT:
            HandleFaultState();
            break;
        case BMS_STATE_SHUTDOWN:
            HandleShutdownState();
            break;
        default:
            diag_Log(DIAG_LEVEL_ERROR, "Error: Unknown state encountered!");
            currentState = BMS_STATE_FAULT;
            break;
    }
}
