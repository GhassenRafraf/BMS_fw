#ifndef DIAG_H
#define DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*==============================================================================
  Diagnostic and Logging Module
==============================================================================*/

/**
 * @brief Diagnostic log levels.
 */
typedef enum {
    DIAG_LEVEL_INFO,
    DIAG_LEVEL_WARNING,
    DIAG_LEVEL_ERROR
} DiagLevel_t;

/**
 * @brief Initialize the diagnostics/logging system.
 *
 * This function should be called during system initialization.
 */
void diag_Init(void);

/**
 * @brief Log a diagnostic message with a specific log level.
 *
 * @param level   The log level (INFO, WARNING, ERROR).
 * @param message The message string to log.
 */
void diag_Log(DiagLevel_t level, const char *message);

/**
 * @brief Convenience macro to log an informational message.
 *
 * @param msg The informational message.
 */
#define diag_Info(msg)    diag_Log(DIAG_LEVEL_INFO, msg)

/**
 * @brief Convenience macro to log a warning message.
 *
 * @param msg The warning message.
 */
#define diag_Warning(msg) diag_Log(DIAG_LEVEL_WARNING, msg)

/**
 * @brief Convenience macro to log an error message.
 *
 * @param msg The error message.
 */
#define diag_Error(msg)   diag_Log(DIAG_LEVEL_ERROR, msg)

#ifdef __cplusplus
}
#endif

#endif /* DIAG_H */
