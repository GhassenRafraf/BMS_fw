#ifndef SOH_H
#define SOH_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the State-of-Health (SOH) estimation module.
 */
void SOH_Init(void);

/**
 * @brief Update the SOH estimation.
 *
 * @param cycleCount Number of full charge-discharge cycles completed.
 */
void SOH_Update(unsigned int cycleCount);

/**
 * @brief Get the current estimated SOH.
 *
 * @return SOH as a percentage (0 to 100).
 */
float SOH_Get(void);

#ifdef __cplusplus
}
#endif

#endif /* SOH_H */
