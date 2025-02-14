//
// Created by Ghassen on 2/12/2025.
//

#ifndef BMS_STATE_H
#define BMS_STATE_H

#ifdef __cplusplus
extern "C" {
#endif

// Define the possible states of the BMS
typedef enum {
    BMS_STATE_INIT,
    BMS_STATE_IDLE,
    BMS_STATE_ACTIVE,
    BMS_STATE_FAULT,
    BMS_STATE_SHUTDOWN
} BMS_State_t;

/**
 * @brief Initialize the BMS state machine.
 */
void BMS_StateMachine_Init(void);

/**
 * @brief Update the BMS state machine.
 * This function should be called periodically.
 */
void BMS_StateMachine_Update(void);

#ifdef __cplusplus
}
#endif

#endif /* BMS_STATE_H */

