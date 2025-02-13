#include "bms_state.h"
#include "diag.h"        // For logging with levels
#include "bms_config.h"  // For configuration parameters

// Static variable to hold the current state of the BMS
static BMS_State_t currentState;

/**
 * @brief Initialize the state machine.
 */
void BMS_StateMachine_Init(void) {
    // Begin with the INIT state
    currentState = BMS_STATE_INIT;

    // Log the initialization with the INFO level
    diag_Log(DIAG_LEVEL_INFO, "BMS State Machine Initialized: INIT state");
}

/**
 * @brief Handle the INIT state logic.
 */
static void HandleInitState(void) {
    // TODO:  Perform necessary initialization here (e.g., calibrations, self-tests)
    // After successful initialization, transition to the IDLE state
    diag_Log(DIAG_LEVEL_INFO, "Handling INIT state: transitioning to IDLE");
    currentState = BMS_STATE_IDLE;
}

/**
 * @brief Handle the IDLE state logic.
 */
static void HandleIdleState(void) {
    // In the IDLE state, the system may wait for conditions to start operation
    // For example, waiting for user input, a trigger from another module, etc.
    diag_Log(DIAG_LEVEL_INFO, "Handling IDLE state: transitioning to ACTIVE");
    // For this example, immediately transition to ACTIVE.
    currentState = BMS_STATE_ACTIVE;
}

/**
 * @brief Handle the ACTIVE state logic.
 */
static void HandleActiveState(void) {
    // In ACTIVE state, the BMS performs measurements, updates SOC/SOH, and manages balancing.
    // You would call functions from the Measurement, SOC, SOH, and Balancing modules here.
    // Also, check for any fault conditions.
    diag_Log(DIAG_LEVEL_INFO, "Handling ACTIVE state: normal operation");

    // Example fault check (placeholder):
    // if (fault_detected) {
    //     currentState = BMS_STATE_FAULT;
    // }

    // In this example, we remain in ACTIVE state.
    // You can add conditions to transition to SHUTDOWN if needed.
}

/**
 * @brief Handle the FAULT state logic.
 */
static void HandleFaultState(void) {
    // In FAULT state, take appropriate safety measures, log errors, and perhaps disable certain functionalities.
    diag_Log(DIAG_LEVEL_ERROR, "Handling FAULT state: transitioning to SHUTDOWN");
    // For this example, move directly to shutdown after detecting a fault.
    currentState = BMS_STATE_SHUTDOWN;
}

/**
 * @brief Handle the SHUTDOWN state logic.
 */
static void HandleShutdownState(void) {
    // In SHUTDOWN, the system is safely powered down or is waiting for a reset.
    diag_Log(DIAG_LEVEL_WARNING, "Handling SHUTDOWN state: system is shutting down");
    // Typically, you would not leave this state until a manual reset occurs.
}

/**
 * @brief Periodic update function for the BMS state machine.
 */
void BMS_StateMachine_Update(void) {
    switch(currentState) {
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
            // If an unknown state is encountered, log an error and set to FAULT.
            diag_Log(DIAG_LEVEL_ERROR, "Error: Unknown state encountered!");
            currentState = BMS_STATE_FAULT;
            break;
    }
}
