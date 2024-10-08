/**
 * @file lcd_handler.cpp
 * @brief Implementación de la clase LCDHandler para el manejo de la pantalla LCD en un videojuego.
 *
 * Este archivo contiene la implementación de la clase LCDHandler, que maneja las diferentes pantallas del juego
 * como la pantalla de bienvenida, menús, y la visualización de puntajes altos en un LCD con protocolo I2C.
 */

#include "lcd_handler.h"
#include <Arduino.h>

/**
 * @brief Objeto global para controlar la pantalla LCD.
 *
 * Este objeto configura el LCD en la dirección 0x27 con una pantalla de 16x2 caracteres.
 */
LiquidCrystal_I2C lcd(0x27, 16, 2);

/**
 * @brief Caracteres personalizados para esquinas del marco en la pantalla.
 */
byte topLeft[8] = {
    B01111,
    B10000,
    B10111,
    B10100,
    B10100,
    B10100,
    B10100,
    B10111};

byte topRight[8] = {
    B11110,
    B00001,
    B11101,
    B00101,
    B00101,
    B00101,
    B00101,
    B11101};

byte bottomRight[8] = {
    B00001,
    B00001,
    B01101,
    B00001,
    B11001,
    B00001,
    B00001,
    B11110};

byte bottomLeft[8] = {
    B10000,
    B10000,
    B10010,
    B10111,
    B10010,
    B10000,
    B10000,
    B01111};

/**
 * @brief Estado actual del juego.
 */
State currentState = WELCOME;

/**
 * @brief Puntuación actual del jugador.
 */
int score = 10;

/**
 * @brief Índices para la navegación de los menús.
 */
int mainMenuIndex = 0, inGameMenuIndex = 0, gameOverMenuIndex = 0;

/**
 * @brief Número de elementos en los menús.
 */
const int mainMenuItems = 3;
const int inGameMenuItems = 2;
const int gameOverMenuItems = 2;

/**
 * @brief Ítems de texto para los menús.
 */
const char *menuItems[] = {"Jugar", "Puntajes Altos", "Salir"};
const char *inGameItems[] = {"Reanudar", "Salir"};
const char *gameOverItems[] = {"Jugar de nuevo", "Salir"};

/**
 * @brief Inicializa la pantalla LCD.
 *
 * Configura el LCD con backlight encendido.
 */
void LCDHandler::lcd_init_display()
{
  lcd.init();
  lcd.backlight();
}

/**
 * @brief Limpia la pantalla LCD.
 *
 * Borra todo el contenido de la pantalla.
 */
void LCDHandler::lcd_clear_display()
{
  lcd.clear();
}

/**
 * @brief Establece el cursor en una posición específica.
 *
 * @param column Columna en la que se ubicará el cursor.
 * @param row Fila en la que se ubicará el cursor.
 */
void LCDHandler::lcd_set_cursor(int column, int row)
{
  lcd.setCursor(column, row);
}

/**
 * @brief Muestra la pantalla de bienvenida.
 *
 * Muestra un mensaje de bienvenida y un marco personalizado con caracteres creados
 * para las esquinas de la pantalla.
 */
void LCDHandler::showWelcomeScreen()
{
  lcd.setCursor(4, 0);
  lcd.print("Bienvenido!");
  lcd.setCursor(4, 1);
  lcd.print("Presiona");

  lcd.createChar(0, topLeft);
  lcd.createChar(1, topRight);
  lcd.createChar(2, bottomRight);
  lcd.createChar(3, bottomLeft);

  lcd.setCursor(1, 0);
  lcd.write(0);
  lcd.write(1);

  lcd.setCursor(1, 1);
  lcd.write(3);
  lcd.write(2);
}

/**
 * @brief Muestra el menú principal.
 *
 * Despliega el menú principal y resalta el ítem seleccionado en la pantalla.
 *
 * @param index Índice del ítem seleccionado en el menú.
 */
void LCDHandler::showMainMenu(int index)
{
  if (index == 2)
  {
    lcd_clear_display();
    lcd.setCursor(0, 0);
    lcd.print("> ");
    lcd.print(menuItems[2]);
  }
  else
  {
    lcd_clear_display();
    for (int i = 0; i < mainMenuItems; i++)
    {
      lcd.setCursor(0, i);
      if (i == index)
      {
        lcd.print("> ");
      }
      else
      {
        lcd.print("  ");
      }
      lcd.print(menuItems[i]);
    }
  }
}

/**
 * @brief Muestra el menú dentro del juego.
 *
 * Despliega el menú de pausa dentro del juego con el ítem seleccionado
 * y la puntuación actual del jugador.
 *
 * @param index Índice del ítem seleccionado en el menú.
 */
void LCDHandler::showInGameMenu(int index)
{
  lcd_clear_display();
  for (int i = 0; i < inGameMenuItems; i++)
  {
    lcd.setCursor(0, i);
    if (i == index)
    {
      lcd.print("> ");
    }
    else
    {
      lcd.print("  ");
    }
    lcd.print(inGameItems[i]);
  }

  lcd.setCursor(7, 1);
  lcd.print("|Score:");
  lcd.print(score);
}

/**
 * @brief Muestra el menú de Game Over.
 *
 * Despliega las opciones del menú cuando el jugador ha perdido el juego.
 *
 * @param index Índice del ítem seleccionado en el menú.
 */
void LCDHandler::showGameOverMenu(int index)
{
  lcd_clear_display();
  for (int i = 0; i < gameOverMenuItems; i++)
  {
    lcd.setCursor(0, i);
    if (i == index)
    {
      lcd.print("> ");
    }
    else
    {
      lcd.print("  ");
    }
    lcd.print(gameOverItems[i]);
  }
}

/**
 * @brief Guarda el puntaje del jugador en la tarjeta microSD.
 *
 * Guarda el nombre del jugador y su puntaje en un archivo de la tarjeta microSD y limpia el nombre del jugador.
 *
 * @param playerName Nombre del jugador.
 * @param score Puntuación del jugador.
 */
void LCDHandler::saveValue(char *playerName, int score)
{
  microSD.saveScore(playerName, score);
  playerName[0] = ' ';
  playerName[1] = ' ';
  playerName[2] = ' ';
}

/**
 * @brief Muestra los puntajes más altos.
 *
 * Despliega una lista de los puntajes más altos en la pantalla LCD. Si no hay puntajes,
 * muestra un mensaje correspondiente.
 */
void LCDHandler::showHighScores()
{
  lcd_clear_display();
  lcd.setCursor(0, 0);
  lcd.print("Puntajes Altos:");
  lcd.setCursor(0, 1);
  int topN = 4;
  String topScores[4];
  microSD.getTopScores(topScores, topN);
  if (topScores[0] == "No hay puntajes")
  {
    lcd.print("No hay puntajes");
    return;
  }
  else
  {
    String output;
    for (int i = 0; i < topN; i++)
    {
      if (topScores[i] == "")
      {
        break;
      }
      output += String(i + 1) + "." + String(topScores[i]) + "|";
    }
    lcd.print(output);
  }
}

/**
 * @brief Muestra el nombre del jugador en la pantalla LCD.
 *
 * Despliega el nombre del jugador a medida que se está ingresando.
 *
 * @param playerName Nombre del jugador.
 */
void LCDHandler::displayPlayerName(char *playerName)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nombre: ");
  lcd.setCursor(0, 1);
  lcd.print(playerName);
}