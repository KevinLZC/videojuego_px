/**
 * @file parallel_task.cpp
 * @brief Implementación de la clase ParallelTask para manejar tareas paralelas.
 *
 * Este archivo contiene la implementación de la clase ParallelTask, que se encarga de crear y manejar tareas
 * paralelas utilizando FreeRTOS en el videojuego. Controla la lógica del menú y las posibles tareas relacionadas
 * con el movimiento de obstáculos y el jugador.
 */

#include <Arduino.h>
#include "parallel_task.h"

#define NUCLEO_PRINCIPAL 1
#define NUCLEO_SECUNDARIO 0

/**
 * @brief Handle de la tarea del menú.
 *
 * Se utiliza para controlar la tarea del menú en el sistema multitarea.
 */
TaskHandle_t HiloMenu;

/**
 * @brief Inicia las tareas paralelas en el videojuego.
 *
 * Esta función crea la tarea asociada con la lógica del menú y la asigna al núcleo principal.
 */
void ParallelTask::startTasks()
{
  xTaskCreatePinnedToCore(
      ParallelTask::menuTask, // Función de la tarea
      "MenuTask",             // Nombre de la tarea
      10000,                  // Stack size
      NULL,                   // Parámetros de la tarea
      1,                      // Prioridad
      &HiloMenu,              // Handle de la tarea
      NUCLEO_PRINCIPAL);      // Núcleo 1
}

/**
 * @brief Tarea encargada de gestionar la lógica del menú.
 *
 * Esta tarea se ejecuta en paralelo, gestionando la navegación por el menú del videojuego
 * y comprobando si se inicia un nuevo juego. Si se inicia, se pueden crear otras tareas
 * paralelas, como el movimiento de obstáculos y del jugador.
 *
 * @param pvParameters Parámetros pasados a la tarea (no utilizados en este caso).
 */
void ParallelTask::menuTask(void *pvParameters)
{
  menuHandler.setup();

  bool startGame = false;
  while (true)
  {
    menuHandler.handleMenuNavigation(startGame);

    // Código comentado para crear tareas adicionales si el juego comienza
    /*
    if(startGame)
    {
      xTaskCreatePinnedToCore(obstacle1Task, "obstacle1Mov", 2500, NULL, 1, &HiloObstaculo1, NUCLEO_PRINCIPAL);
      xTaskCreatePinnedToCore(obstacle2Task, "obstacle2Mov", 2500, NULL, 1, &HiloObstaculo2, NUCLEO_PRINCIPAL);
      xTaskCreatePinnedToCore(playerMov, "playerMov", 4000, NULL, 3, &HiloPlayerMov, NUCLEO_PRINCIPAL);
      startGame = false;
      vTaskSuspend(NULL);
    }
    */

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

// Implementación futura de otras tareas relacionadas con el videojuego
/*
void ParallelTask::obstacle1Task(void *pvParameters) {
  // Lógica para el movimiento del obstáculo 1
}

void ParallelTask::obstacle2Task(void *pvParameters) {
  // Lógica para el movimiento del obstáculo 2
}

void ParallelTask::playerMov(void *pvParameters) {
  // Lógica para el movimiento del jugador
}

void ParallelTask::checkingPause(void *pvParameters) {
  // Lógica para pausar el juego
}

void ParallelTask::createGameTasks(void *pvParameters) {
  // Lógica para crear nuevas tareas relacionadas con el juego
}
*/