#ifndef CELL_BALANCE_H
#define CELL_BALANCE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Initialize the cell balancing system.
 */
void Cell_Balance_Init(void);

/**
 * @brief Update the cell balancing logic.
 *
 * This function should be called periodically to evaluate the cell voltages
 * and enable or disable passive balancing circuitry as needed.
 */
void Cell_Balance_Update(void);

/**
 * @brief Enable or disable balancing for a specific cell.
 *
 * @param cell   Index of the cell (0 to NUM_CELLS - 1).
 * @param enable True to enable balancing, false to disable.
 */
void Cell_Balance_Set(uint8_t cell, bool enable);

#ifdef __cplusplus
}
#endif

#endif /* CELL_BALANCE_H */
