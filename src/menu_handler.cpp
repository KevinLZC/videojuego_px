#include <Arduino.h>
#include "menu_handler.h"
#include "song.h"


// Nombre del jugador, limitado a 3 caracteres
char playerName[3] = "";
// Índice de la letra que el jugador está seleccionando
int currentLetterIndex = 0;

/**
 * @brief Configura el menú inicial del juego.
 *
 * Este método inicializa el puerto serie, configura la pantalla LCD,
 * y el pin del botón. También muestra la pantalla de bienvenida
 * y realiza la inicialización de la tarjeta microSD.
 */
soundtracks my_soundtrack;
void MenuHandler::setup()
{
  Serial.begin(115200);
  display.lcd_init_display();
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  display.showWelcomeScreen();
  microSD.init();
  my_soundtrack.fur_elise();
}

/**
 * @brief Verifica si el botón ha sido presionado.
 * @return true Si el botón ha sido presionado.
 * @return false Si el botón no ha sido presionado.
 *
 * Este método incluye un retardo de rebote para evitar múltiples
 * lecturas de un solo evento de presión de botón.
 */
bool MenuHandler::isButtonPressed()
{
  if (digitalRead(PIN_BUTTON) == LOW)
  {
    unsigned long currentMillis = millis();
    if (currentMillis - lastButtonPress > debounceDelay)
    {
      lastButtonPress = currentMillis;
      return true;
    }
  }
  return false;
}

/**
 * @brief Maneja la transición desde la pantalla de bienvenida al menú principal.
 * @param buttonPressed Indica si el botón ha sido presionado.
 *
 * Cambia el estado actual a MAIN_MENU si el botón es presionado.
 */
void welcomeHandler(bool buttonPressed)
{
  if (buttonPressed)
  {
    currentState = MAIN_MENU;
    display.showMainMenu(mainMenuIndex);
  }
}

/**
 * @brief Maneja la navegación en el menú principal.
 * @param yValue Valor analógico del joystick en el eje Y.
 * @param joystickMoved Indica si el joystick ha sido movido.
 * @param buttonPressed Indica si el botón ha sido presionado.
 * @param gameStartTime Tiempo de inicio del juego.
 *
 * Actualiza el índice del menú según el movimiento del joystick y
 * verifica si el botón ha sido presionado para entrar en diferentes
 * estados del juego.
 */
void mainMenuHandler(int yValue, bool joystickMoved, bool buttonPressed, unsigned long gameStartTime)
{
  if (DECREMENTO(yValue) && !joystickMoved)
  {
    //Función para sonido
    my_soundtrack.move();
    mainMenuIndex++;
    if (mainMenuIndex >= mainMenuItems)
      mainMenuIndex = 0;
    joystickMoved = true;
    display.showMainMenu(mainMenuIndex);
  }

  if (INCREMENTO(yValue) && !joystickMoved)
  {
    //Función para sonido
    my_soundtrack.move();
    mainMenuIndex--;
    if (mainMenuIndex < 0)
      mainMenuIndex = mainMenuItems - 1;
    joystickMoved = true;
    display.showMainMenu(mainMenuIndex);
  }

  if (!INCREMENTO(yValue) && !DECREMENTO(yValue))
  {
    joystickMoved = false;
  }

  if (buttonPressed)
  {
    if (mainMenuIndex == 0)
    {
      currentState = IN_GAME;
      display.lcd_clear_display();
      gameStartTime = millis();
    }
    else if (mainMenuIndex == 1)
    {
      currentState = HIGH_SCORES;
      display.showHighScores();
    }
    else if (mainMenuIndex == 2)
    {
      display.lcd_clear_display();
      mainMenuIndex = 0;
      currentState = WELCOME;
      display.showWelcomeScreen();
    }
  }
}

/**
 * @brief Maneja la navegación en la pantalla de puntajes altos.
 * @param buttonPressed Indica si el botón ha sido presionado.
 *
 * Regresa al menú principal si el botón es presionado.
 */
void highScoresHandler(bool buttonPressed)
{
  if (buttonPressed)
  {
    currentState = MAIN_MENU;
    display.showMainMenu(mainMenuIndex);
  }
}

/**
 * @brief Maneja la lógica del juego en curso.
 * @param buttonPressed Indica si el botón ha sido presionado.
 * @param gameStartTime Tiempo de inicio del juego.
 * @param startGameFlag Indica si se ha comenzado el juego.
 *
 * Cambia al estado de IN_GAME_MENU si se presiona el botón,
 * y controla el tiempo de juego para transitar a ENTER_NAME.
 */
void inGameHandler(bool buttonPressed, unsigned long gameStartTime)
{
  
  if (buttonPressed)
  {
    currentState = IN_GAME_MENU;
    inGameMenuIndex = 0;
    display.showInGameMenu(inGameMenuIndex);
  }

  
  // if (millis() - gameStartTime > 15000)
  // {
  //   gameStartTime = millis();
  //   currentState = GAME_OVER;
  //   gameOverMenuIndex = 0;
  //   display.showGameOverMenu(gameOverMenuIndex);
  // }
}

/**
 * @brief Maneja la navegación en el menú del juego.
 * @param yValue Valor analógico del joystick en el eje Y.
 * @param joystickMoved Indica si el joystick ha sido movido.
 * @param buttonPressed Indica si el botón ha sido presionado.
 * @param gameStartTime Tiempo de inicio del juego.
 *
 * Actualiza el índice del menú del juego y verifica las acciones del botón.
 */
void inGameMenuHandler(int yValue, bool joystickMoved, bool buttonPressed, unsigned long gameStartTime)
{
  if (DECREMENTO(yValue) && !joystickMoved)
  {
    //Función para sonido
    my_soundtrack.move();
    inGameMenuIndex++;
    if (inGameMenuIndex >= inGameMenuItems)
      inGameMenuIndex = 0;
    joystickMoved = true;
    display.showInGameMenu(inGameMenuIndex);
  }

  if (INCREMENTO(yValue) && !joystickMoved)
  {
    //Función para sonido
    my_soundtrack.move();
    inGameMenuIndex--;
    if (inGameMenuIndex < 0)
      inGameMenuIndex = inGameMenuItems - 1;
    joystickMoved = true;
    display.showInGameMenu(inGameMenuIndex);
  }

  if (!INCREMENTO(yValue) && !DECREMENTO(yValue))
  {
    joystickMoved = false;
  }

  if (buttonPressed)
  {
    if (inGameMenuIndex == 0)
    {
      currentState = IN_GAME;
      display.lcd_clear_display();
      gameStartTime = millis();
    }
    else if (inGameMenuIndex == 1)
    {
      currentState = MAIN_MENU;
      display.showMainMenu(mainMenuIndex);
    }
  }
}

/**
 * @brief Maneja la lógica del menú de "Game Over".
 * @param yValue Valor analógico del joystick en el eje Y.
 * @param joystickMoved Indica si el joystick ha sido movido.
 * @param buttonPressed Indica si el botón ha sido presionado.
 * @param gameStartTime Tiempo de inicio del juego.
 *
 * Actualiza el índice del menú de "Game Over" y maneja la
 * transición a otros estados del juego según la entrada del botón.
 */
void gameOverHandler(int yValue, bool joystickMoved, bool buttonPressed, unsigned long gameStartTime)
{
  if (DECREMENTO(yValue) && !joystickMoved)
  {
    //Función para sonido
    my_soundtrack.move();
    gameOverMenuIndex++;
    if (gameOverMenuIndex >= gameOverMenuItems)
      gameOverMenuIndex = 0;
    joystickMoved = true;
    display.showGameOverMenu(gameOverMenuIndex);
  }

  if (INCREMENTO(yValue) && !joystickMoved)
  {
    //Función para sonido
    my_soundtrack.move();
    gameOverMenuIndex--;
    if (gameOverMenuIndex < 0)
      gameOverMenuIndex = gameOverMenuItems - 1;
    joystickMoved = true;
    display.showGameOverMenu(gameOverMenuIndex);
  }

  if (!INCREMENTO(yValue) && !DECREMENTO(yValue))
  {
    joystickMoved = false;
  }

  if (buttonPressed)
  {
    if (gameOverMenuIndex == 0)
    {
      currentState = IN_GAME;
      display.lcd_clear_display();
      gameStartTime = millis();
    }
    else if (gameOverMenuIndex == 1)
    {
      currentState = MAIN_MENU;
      display.showMainMenu(mainMenuIndex);
    }
  }
}

/**
 * @brief Maneja la entrada del nombre del jugador.
 * @param yValue Valor analógico del joystick en el eje Y.
 * @param joystickMoved Referencia que indica si el joystick ha sido movido.
 * @param buttonPressed Indica si el botón ha sido presionado.
 *
 * Cambia las letras del nombre del jugador y maneja la
 * transición al estado GAME_OVER cuando se ingresa el nombre completo.
 */
void enterNameHandler(int yValue, bool &joystickMoved, bool buttonPressed)
{
  // Cambiar la letra actual en función del movimiento del joystick
  if (DECREMENTO(yValue) && !joystickMoved)
  {
    playerName[currentLetterIndex]++;
    if (playerName[currentLetterIndex] > 'Z')
      playerName[currentLetterIndex] = 'A';
    joystickMoved = true;
  }
  else if (INCREMENTO(yValue) && !joystickMoved)
  {
    playerName[currentLetterIndex]--;
    if (playerName[currentLetterIndex] < 'A')
      playerName[currentLetterIndex] = 'Z';
    joystickMoved = true;
  }

  // Si el joystick no se mueve, reseteamos el flag
  if (!INCREMENTO(yValue) && !DECREMENTO(yValue))
  {
    joystickMoved = false;
  }

  // Cambiar al siguiente carácter cuando se presiona el botón
  if (buttonPressed)
  {
    currentLetterIndex++;
    if (currentLetterIndex > 2)
    {
      // Cuando se ha ingresado todo el nombre, pasar al estado GAME_OVER
      currentState = GAME_OVER;
      gameOverMenuIndex = 0;
      display.lcd_clear_display(); // Aseguramos que se limpie la pantalla

      // Mostrar el menú de Game Over
      display.saveValue(playerName, score);
      display.showGameOverMenu(gameOverMenuIndex);
    }
    else
    {
      // Si no se ha ingresado todo el nombre, mostrar el nombre actualizado
      display.displayPlayerName(playerName);
    }
  }
  else
  {
    // Mientras no se presione el botón, mostrar el nombre actual en pantalla
    display.displayPlayerName(playerName);
  }
}

/**
 * @brief Maneja la navegación del menú en el videojuego.
 *
 * Esta función se encarga de gestionar la lógica de navegación del menú en función del estado actual del juego.
 * Se utilizan entradas del joystick y botones para navegar a través de diferentes estados del menú.
 *
 * @param startGameFlag Bandera que indica si se debe iniciar un nuevo juego.
 *                      Esta variable puede ser modificada en la función según la lógica del menú.
 *
 * La función realiza lo siguiente:
 * - Lee el valor analógico del eje Y del joystick.
 * - Verifica si un botón ha sido presionado.
 * - Dependiendo del estado actual del menú (`currentState`), llama a la función de manejo correspondiente para ese estado.
 *
 * Los estados posibles son:
 * - WELCOME: Muestra la pantalla de bienvenida.
 * - MAIN_MENU: Maneja la navegación en el menú principal del juego.
 * - HIGH_SCORES: Muestra las puntuaciones más altas.
 * - IN_GAME: Maneja la lógica durante el juego.
 * - IN_GAME_MENU: Maneja la navegación en el menú del juego en curso.
 * - GAME_OVER: Muestra la lógica cuando el juego ha terminado.
 * - ENTER_NAME: Maneja la entrada del nombre del jugador.
 *
 * Ejemplo de uso:
 * ```cpp
 * MenuHandler menuHandler;
 * menuHandler.handleMenuNavigation(startGameFlag);
 * ```
 */


void MenuHandler::handleMenuNavigation()
{
  int yValue = analogRead(PIN_Y);    // Lee el valor del eje Y del joystick
  bool joystickMoved = false;        // Bandera para indicar si el joystick se ha movido
  buttonPressed = isButtonPressed(); // Verifica si el botón ha sido presionado

  // Manejo del menú basado en el estado actual
  switch (currentState)
  {
  case WELCOME:
    welcomeHandler(buttonPressed); // Maneja la pantalla de bienvenida
    break;

  case MAIN_MENU:
    mainMenuHandler(yValue, joystickMoved, buttonPressed, gameStartTime); // Maneja el menú principal
    break;

  case HIGH_SCORES:
    highScoresHandler(buttonPressed); // Maneja la visualización de las puntuaciones más altas
    break;

  case IN_GAME:
    inGameHandler(buttonPressed, gameStartTime); // Maneja la lógica del juego
    break;

  case IN_GAME_MENU:
    inGameMenuHandler(yValue, joystickMoved, buttonPressed, gameStartTime); // Maneja el menú en el juego
    break;

  case GAME_OVER:
    gameOverHandler(yValue, joystickMoved, buttonPressed, gameStartTime); // Maneja la lógica de fin de juego
    break;

  case ENTER_NAME:
    enterNameHandler(yValue, joystickMoved, buttonPressed); // Maneja la entrada del nombre
    break;
  }
}