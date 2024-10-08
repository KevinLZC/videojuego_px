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
  display.createCharacters();
  microSD.checkFileContent(); ///< Verifica el contenido de los archivos en la tarjeta microSD.
  ParallelTask::startTasks();
}

void loop()
{

}