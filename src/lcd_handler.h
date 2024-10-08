/**
 * @file lcd_handler.h
 * @brief Definición de la clase LCDHandler y variables relacionadas para el manejo de una pantalla LCD en el videojuego.
 *
 * Este archivo contiene la definición de la clase LCDHandler, que gestiona la pantalla LCD para mostrar diferentes
 * estados del videojuego como el menú principal, el juego en curso y la pantalla de Game Over.
 */
<<<<<<< HEAD
=======

>>>>>>> 4452679eb9b58807d3a09c05d7a047e51d994a0b
#ifndef LCD_HANDLER_H
#define LCD_HANDLER_H

#include <LiquidCrystal_I2C.h>
#include "microsd.h"

/**
 * @brief Instancia del sistema de manejo de la microSD.
 */
extern MicroSD microSD;

#define VALOR_INICIAL 2048 ///< Valor inicial para control de lectura del joystick.
#define VALOR_TOPE 4095    ///< Valor tope de lectura del joystick.
#define PWM_MIN 0          ///< Valor mínimo para la señal PWM.
#define PWM_MAX 255        ///< Valor máximo para la señal PWM.

#define INCREMENTO(a) (a > VALOR_INICIAL + 200 ? 1 : 0) ///< Macro para verificar incremento en joystick.
#define DECREMENTO(a) (a < VALOR_INICIAL - 200 ? 1 : 0) ///< Macro para verificar decremento en joystick.

#define PIN_X 34      ///< Pin para el eje X del joystick.
#define PIN_Y 35      ///< Pin para el eje Y del joystick.
#define PIN_BUTTON 32 ///< Pin para el botón del joystick.

/**
 * @enum State
 * @brief Enumeración de los diferentes estados del videojuego.
 *
 * Esta enumeración define los diferentes estados que pueden existir en el videojuego,
 * tales como el menú de bienvenida, el juego en curso, el menú de pausa, entre otros.
 */
enum State
{
  WELCOME,      ///< Estado de pantalla de bienvenida.
  MAIN_MENU,    ///< Estado de menú principal.
  HIGH_SCORES,  ///< Estado de pantalla de puntajes altos.
  IN_GAME,      ///< Estado del juego en curso.
  IN_GAME_MENU, ///< Estado del menú en el juego.
  GAME_OVER,    ///< Estado de pantalla de fin de juego.
  ENTER_NAME    ///< Estado de ingresar nombre de jugador.
};

/**
 * @brief Estado actual del videojuego.
 */
extern State currentState;

/**
 * @brief Puntuación del jugador.
 */
extern int score;

/**
 * @brief Índices para la navegación de los menús.
 */
extern int mainMenuIndex, inGameMenuIndex, gameOverMenuIndex;

/**
 * @brief Número de elementos en los menús.
 */
extern const int mainMenuItems, inGameMenuItems, gameOverMenuItems;
<<<<<<< HEAD
=======

>>>>>>> 4452679eb9b58807d3a09c05d7a047e51d994a0b
/**
 * @brief Ítems de texto para los menús.
 */
extern const char *menuItems[], *inGameItems[], *gameOverItems[];

/**
 * @brief Nombre del jugador.
 */
extern char playerName[3];

/**
 * @class LCDHandler
 * @brief Clase para el manejo de la pantalla LCD.
 *
 * Esta clase gestiona las diferentes pantallas y menús del videojuego, como el menú principal,
 * la pantalla de Game Over, y la entrada del nombre del jugador.
 */
class LCDHandler
{
public:
  /**
   * @brief Inicializa la pantalla LCD.
   *
   * Configura los parámetros iniciales de la pantalla LCD, como la dirección y el tamaño.
   */
  void lcd_init_display();

<<<<<<< HEAD
    /**
=======
  /**
>>>>>>> 4452679eb9b58807d3a09c05d7a047e51d994a0b
   * @brief Limpia la pantalla LCD.
   *
   * Borra el contenido actual de la pantalla.
   */
  void lcd_clear_display();

  /**
   * @brief Establece el cursor en una posición específica de la pantalla.
   *
   * @param column Columna en la que se ubicará el cursor.
   * @param row Fila en la que se ubicará el cursor.
   */
  void lcd_set_cursor(int column, int row);
<<<<<<< HEAD
  
  void createCharacters(void);
=======

>>>>>>> 4452679eb9b58807d3a09c05d7a047e51d994a0b
  /**
   * @brief Muestra la pantalla de bienvenida.
   *
   * Despliega el mensaje de bienvenida en la pantalla LCD.
   */
  void showWelcomeScreen();

  /**
   * @brief Muestra el menú principal.
   *
   * Despliega el menú principal en la pantalla, basado en el índice seleccionado.
   *
   * @param index Índice del ítem seleccionado en el menú.
   */
  void showMainMenu(int index);

  /**
   * @brief Muestra el menú dentro del juego.
   *
   * Despliega el menú de pausa durante el juego.
   *
   * @param index Índice del ítem seleccionado en el menú.
   */
  void showInGameMenu(int index);

  /**
   * @brief Muestra el menú de Game Over.
   *
   * Despliega el menú cuando el jugador ha perdido el juego.
   *
   * @param index Índice del ítem seleccionado en el menú.
   */
  void showGameOverMenu(int index);
<<<<<<< HEAD
  
=======

>>>>>>> 4452679eb9b58807d3a09c05d7a047e51d994a0b
  /**
   * @brief Muestra los puntajes más altos.
   *
   * Despliega una lista de los puntajes más altos en la pantalla LCD.
   */
  void showHighScores();

  /**
   * @brief Muestra el nombre del jugador.
   *
   * Despliega el nombre del jugador en la pantalla LCD.
   *
   * @param playerName Nombre del jugador a mostrar.
   */
  void displayPlayerName(char *playerName);

  /**
   * @brief Guarda el puntaje del jugador en la tarjeta SD.
   *
   * Guarda el nombre del jugador y su puntaje en un archivo de la tarjeta microSD.
   *
   * @param playerName Nombre del jugador.
   * @param score Puntuación del jugador.
   */
  void saveValue(char *playerName, int score);
<<<<<<< HEAD
  void print(int, uint8_t, bool);
  void moveObstacle(int8_t[2], uint8_t);
=======
>>>>>>> 4452679eb9b58807d3a09c05d7a047e51d994a0b
};

#endif // LCD_HANDLER_H