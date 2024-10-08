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

  while (true)
  {
  menuHandler.handleMenuNavigation();

<<<<<<< HEAD
    switch(currentState)
    {
      case IN_GAME_MENU:
        xTaskCreatePinnedToCore (
          obstacle1Task,            /* Función que controla la tarea. */
          "obstacle1Mov",               /* Etiqueta de la tarea.          */
          2500,                   /* Tamaño en memoria RAM.         */
          NULL,                   /* Parametros de la tarea.        */
          2,                      /* Prioridad de la tarea.         */
          &HiloObstaculo1,                 /* Seguimiento de la tarea.       */
          NUCLEO_PRINCIPAL        /* Número de núcleo.              */
        );
        xTaskCreatePinnedToCore (
          obstacle2Task,            /* Función que controla la tarea. */
          "obstacle2Mov",               /* Etiqueta de la tarea.          */
          2500,                   /* Tamaño en memoria RAM.         */
          NULL,                   /* Parametros de la tarea.        */
          2,                      /* Prioridad de la tarea.         */
          &HiloObstaculo2,                 /* Seguimiento de la tarea.       */
          NUCLEO_PRINCIPAL        /* Número de núcleo.              */
        );

        xTaskCreatePinnedToCore (
          playerMov,            /* Función que controla la tarea. */
          "playerMov",               /* Etiqueta de la tarea.          */
          4000,                   /* Tamaño en memoria RAM.         */
          NULL,                   /* Parametros de la tarea.        */
          3,                      /* Prioridad de la tarea.         */
          &HiloPlayerMov,                 /* Seguimiento de la tarea.       */
          NUCLEO_PRINCIPAL        /* Número de núcleo.              */
        );

        xTaskCreatePinnedToCore (
          checkingPause,            /* Función que controla la tarea. */
          "checkPause",               /* Etiqueta de la tarea.          */
          1000,                   /* Tamaño en memoria RAM.         */
          NULL,                   /* Parametros de la tarea.        */
          1,                      /* Prioridad de la tarea.         */
          &HiloPausa,                 /* Seguimiento de la tarea.       */
          NUCLEO_SECUNDARIO        /* Número de núcleo.              */
        );

        vTaskSuspend(NULL);
        break;
      
      case IN_GAME:
        vTaskResume(HiloPlayerMov);
        vTaskResume(HiloObstaculo2);
        vTaskResume(HiloObstaculo1);
        vTaskResume(HiloPausa);
        break;

      case MAIN_MENU:
        vTaskDelete(HiloPlayerMov);
        vTaskDelete(HiloObstaculo2);
        vTaskDelete(HiloObstaculo1);
        vTaskDelete(HiloPausa);
        break;
      
      default:
        break;

=======
    // Código comentado para crear tareas adicionales si el juego comienza
    /*
    if(startGame)
    {
      xTaskCreatePinnedToCore(obstacle1Task, "obstacle1Mov", 2500, NULL, 1, &HiloObstaculo1, NUCLEO_PRINCIPAL);
      xTaskCreatePinnedToCore(obstacle2Task, "obstacle2Mov", 2500, NULL, 1, &HiloObstaculo2, NUCLEO_PRINCIPAL);
      xTaskCreatePinnedToCore(playerMov, "playerMov", 4000, NULL, 3, &HiloPlayerMov, NUCLEO_PRINCIPAL);
      startGame = false;
      vTaskSuspend(NULL);
>>>>>>> 4452679eb9b58807d3a09c05d7a047e51d994a0b
    }
    */


    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

<<<<<<< HEAD

void ParallelTask :: obstacle2Task ( void * pvParameters ) {

  int8_t counter = 3;
  for(;;){

    display.moveObstacle(obstacle2, 2);
    obstacle2[0] = 15;
    obstacle2[1] = 1;

    if(counter == 0){
      break;
    }
    counter--;
  }
  Serial.println("Delete and create");
  vTaskDelete(NULL);
=======
// Implementación futura de otras tareas relacionadas con el videojuego
/*
void ParallelTask::obstacle1Task(void *pvParameters) {
  // Lógica para el movimiento del obstáculo 1
>>>>>>> 4452679eb9b58807d3a09c05d7a047e51d994a0b
}

void ParallelTask::obstacle2Task(void *pvParameters) {
  // Lógica para el movimiento del obstáculo 2
}

<<<<<<< HEAD
void ParallelTask :: checkingPause( void *pvParameters){

  //if isButtonPressed
  if(menuHandler.isButtonPressed())
  {
    vTaskSuspend(HiloPlayerMov);
    vTaskSuspend(HiloObstaculo2);
    vTaskSuspend(HiloObstaculo1);
    //Suspender cancion y demas tasks
    //activa o resume task menu in-game
    xTaskCreatePinnedToCore(
      ParallelTask::menuTask, // Función de la tarea
      "MenuTask",              // Nombre de la tarea
      10000,                   // Stack size
      NULL,                    // Parámetros de la tarea
      1,                       // Prioridad
      &HiloMenu,               // Handle de la tarea
      NUCLEO_PRINCIPAL        // Núcleo 1
    );                      
    vTaskSuspend(NULL);
  }

}

=======
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
>>>>>>> 4452679eb9b58807d3a09c05d7a047e51d994a0b
