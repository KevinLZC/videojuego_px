#include <Arduino.h>
#include "parallel_task.h"

#define NUCLEO_PRINCIPAL 0
#define NUCLEO_SECUNDARIO 1

void ParallelTask::startTasks()
{
  xTaskCreatePinnedToCore(
      ParallelTask::menuTask, // Función de la tarea
      "MenuTask",              // Nombre de la tarea
      10000,                   // Stack size
      NULL,                    // Parámetros de la tarea
      1,                       // Prioridad
      &HiloMenu,                    // Handle de la tarea
      NUCLEO_PRINCIPAL);                      // Núcleo 1
}

void ParallelTask::menuTask(void *pvParameters)
{
  menuHandler.setup();

  bool startGame = false;
  while (true)
  {
    menuHandler.handleMenuNavigation(startGame);

    if(startGame)
    {
      xTaskCreatePinnedToCore (
      obstacle1Task,            /* Función que controla la tarea. */
      "obstacle1Mov",               /* Etiqueta de la tarea.          */
      2500,                   /* Tamaño en memoria RAM.         */
      NULL,                   /* Parametros de la tarea.        */
      1,                      /* Prioridad de la tarea.         */
      &HiloObstaculo1,                 /* Seguimiento de la tarea.       */
      NUCLEO_PRINCIPAL        /* Número de núcleo.              */
      );
      xTaskCreatePinnedToCore (
        obstacle2Task,            /* Función que controla la tarea. */
        "obstacle2Mov",               /* Etiqueta de la tarea.          */
        2500,                   /* Tamaño en memoria RAM.         */
        NULL,                   /* Parametros de la tarea.        */
        1,                      /* Prioridad de la tarea.         */
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
        obstacle1Task,            /* Función que controla la tarea. */
        "obstacle1Mov",               /* Etiqueta de la tarea.          */
        2500,                   /* Tamaño en memoria RAM.         */
        NULL,                   /* Parametros de la tarea.        */
        1,                      /* Prioridad de la tarea.         */
        &HiloObstaculo1,                 /* Seguimiento de la tarea.       */
        NUCLEO_PRINCIPAL        /* Número de núcleo.              */
      );
      xTaskCreatePinnedToCore (
        obstacle2Task,            /* Función que controla la tarea. */
        "obstacle2Mov",               /* Etiqueta de la tarea.          */
        2500,                   /* Tamaño en memoria RAM.         */
        NULL,                   /* Parametros de la tarea.        */
        1,                      /* Prioridad de la tarea.         */
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

      startGame = false;
      vTaskSuspend(NULL);
    }

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}


void ParallelTask :: obstacle2Task ( void * pvParameters ) {

  int8_t counter = 3;
  for(;;){

    lcdDisplay.moveObstacle(obstacle2, 2);
    obstacle2[0] = 15;
    obstacle2[1] = 1;

    if(counter == 0){
      break;
    }
    counter--;
  }
  Serial.println("Delete and create");
  vTaskDelete(NULL);
}

void ParallelTask :: playerMov(void *pvParameters) {
  myJuego.startPlayer();

  for (;;) {
    if(myJuego.hasCrashed())
    {
      /** 
       * TODO 
       * eliminar las tareas
       * guardar el score
       * regresar a menu
       * 
       * 
       */
      vTaskDelete(HiloObstaculo1);
      vTaskDelete(HiloObstaculo2);
      vTaskDelete(NULL);
      
    }
    myJuego.movimiento();
  }
}

void ParallelTask :: checkingPause( void *pvParameters){

  //if isButtonPressed
  vTaskSuspend(HiloPlayerMov);
  vTaskSuspend(HiloObstaculo2);
  vtaskSuspend(HiloObstaculo1);
  //Suspender cancion y demas tasks
  //activa o resume task menu in-game
  vtaskSuspend(NULL);

  vtaskResume()
}

void ParallelTask :: createGameTasks( void *pvParameters){
  
}
