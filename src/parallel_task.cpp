#include <Arduino.h>
#include "parallel_task.h"

void ParallelTask::startTasks()
{
  xTaskCreatePinnedToCore(
      ParallelTask::menuTask, // Función de la tarea
      "MenuTask",              // Nombre de la tarea
      10000,                   // Stack size
      NULL,                    // Parámetros de la tarea
      1,                       // Prioridad
      NULL,                    // Handle de la tarea
      1);                      // Núcleo 1
}

void ParallelTask::menuTask(void *pvParameters)
{
  menuHandler.setup();

  while (true)
  {
    menuHandler.handleMenuNavigation();
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
