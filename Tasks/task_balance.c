#include "FreeRTOS.h"
#include "task.h"
#include "cell_balance.h"

void Task_Balance(void *argument)
{
    // Initialize the balancing system.
    Cell_Balance_Init();

    for (;;)
    {
        // Update balancing logic periodically.
        Cell_Balance_Update();

        // Adjust the delay as needed (e.g., 500ms between updates).
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
