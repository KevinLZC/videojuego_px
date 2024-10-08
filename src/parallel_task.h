/**
 * @file parallel_task.h
 * @brief Declaración de la clase ParallelTask para manejar tareas paralelas.
 *
 * Este archivo contiene la definición de la clase ParallelTask, que gestiona tareas paralelas
 * dentro del videojuego utilizando FreeRTOS. También declara las tareas específicas relacionadas con el menú.
 */

#ifndef PARALLEL_TASK_H
#define PARALLEL_TASK_H

#include "menu_handler.h"
#include "juego.h"
#include "lcd_handler.h"

/**
 * @brief Instancia externa de MenuHandler utilizada en las tareas paralelas.
 *
 * Esta instancia global se utiliza para interactuar con el menú desde las tareas paralelas.
 */
extern MenuHandler menuHandler;
extern Juego myJuego;
extern LCDHandler display;

TaskHandle_t HiloMenu;
TaskHandle_t HiloObstaculo1;
TaskHandle_t HiloObstaculo2;
TaskHandle_t HiloPlayerMov;

class ParallelTask{
  public:
    static void startTasks();
    static void menuTask(void *pvParameters);
    static void obstacle1Task( void *pvParameters );
    static void obstacle2Task( void *pvParameters );
    static void playerMov( void *pvParameters );
    static void checkingPause( void *pvParameters );
    static void createGameTask( void *pvParameters );
};

#endif // PARALLEL_TASK_H