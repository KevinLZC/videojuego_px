#include <Arduino.h>
#include "videojuego.h"

/**
 * @brief Configura el entorno del juego.
 *
 * Este método se llama una vez al inicio del programa.
 * Inicializa las tareas paralelas y verifica el contenido
 * del archivo en la tarjeta microSD.
 */
void setup()
{
<<<<<<< HEAD
  display.createCharacters();
  microSD.checkFileContent(); ///< Verifica el contenido de los archivos en la tarjeta microSD.
  ParallelTask::startTasks();
=======
  ParallelTask::startTasks(); ///< Inicia las tareas paralelas definidas en la clase ParallelTask.
  microSD.checkFileContent(); ///< Verifica el contenido de los archivos en la tarjeta microSD.
>>>>>>> 4452679eb9b58807d3a09c05d7a047e51d994a0b
}

/**
 * @brief Ciclo principal del juego.
 *
 * Este método se ejecuta continuamente después de `setup()`.
 * En esta implementación, no se han agregado acciones específicas
 * en el bucle principal.
 */
void loop()
{
  // No se ha implementado ninguna funcionalidad en el bucle principal.
}