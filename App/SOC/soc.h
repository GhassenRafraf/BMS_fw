#ifndef SOC_H
#define SOC_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the State-of-Charge (SOC) estimation module.
 */
void SOC_Init(void);

/**
 * @brief Update the SOC estimation.
 *
 * @param current   Measured current (Amps). Positive for discharge, negative for charge.
 * @param deltaTime Time elapsed since the last update (seconds).
 */
void SOC_Update(float current, float deltaTime);

/**
 * @brief Get the current estimated SOC.
 *
 * @return SOC as a percentage (0 to 100).
 */
float SOC_Get(void);

#ifdef __cplusplus
}
#endif

#endif /* SOC_H */
