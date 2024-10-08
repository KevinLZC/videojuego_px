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

/**
 * @brief Instancia externa de MenuHandler utilizada en las tareas paralelas.
 *
 * Esta instancia global se utiliza para interactuar con el menú desde las tareas paralelas.
 */
extern MenuHandler menuHandler;

/**
 * @brief Handle de la tarea del menú.
 *
 * Este objeto se utiliza para gestionar la tarea que controla el menú dentro del sistema de tareas paralelas.
 */
extern TaskHandle_t HiloMenu;

/**
 * @class ParallelTask
 * @brief Clase que gestiona las tareas paralelas en el videojuego.
 *
 * Esta clase define métodos estáticos para iniciar y manejar las tareas concurrentes dentro del videojuego.
 * Utiliza FreeRTOS para ejecutar diferentes aspectos del juego en paralelo.
 */
class ParallelTask
{
public:
  /**
   * @brief Inicia todas las tareas paralelas.
   *
   * Este método estático se encarga de iniciar las tareas que se ejecutarán de manera concurrente
   * dentro del videojuego.
   */
  static void startTasks();

  /**
   * @brief Tarea encargada de gestionar el menú del videojuego.
   *
   * Esta tarea se ejecuta en paralelo y se encarga de manejar la lógica relacionada con el menú
   * del videojuego, como la navegación y la selección de opciones.
   *
   * @param pvParameters Parámetros pasados a la tarea (no utilizados en este caso).
   */
  static void menuTask(void *pvParameters);

  // Declaraciones de otras posibles tareas a implementar
  // static void obstacle1Task( void *pvParameters );
  // static void obstacle2Task( void *pvParameters );
  // static void playerMov( void *pvParameters );
  // static void checkingPause( void *pvParameters );
  // static void createGameTask( void *pvParameters );
};

#endif // PARALLEL_TASK_H