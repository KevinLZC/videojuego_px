#include "lcd_handler.h"
#include <Arduino.h>
#include "microsd.h"
#include "json.h"

MicroSD microSD;
JSON json;

LiquidCrystal_I2C lcd(0x27, 16, 2);

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

State currentState = WELCOME;
int score = 10;
int mainMenuIndex = 0, inGameMenuIndex = 0, gameOverMenuIndex = 0;

const int mainMenuItems = 3;
const int inGameMenuItems = 2;
const int gameOverMenuItems = 2;

const char *menuItems[] = {"Jugar", "Puntajes Altos", "Salir"};
const char *inGameItems[] = {"Reanudar", "Salir"};
const char *gameOverItems[] = {"Jugar de nuevo", "Salir"};

void LCDHandler::lcd_init_display()
{
  lcd.init();
  lcd.backlight();
}

void LCDHandler::lcd_clear_display()
{
  lcd.clear();
}

void LCDHandler::lcd_set_cursor(int column, int row)
{
  lcd.setCursor(column, row);
}

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

void LCDHandler::showGameOverMenu(int index)
{
  microSD.saveScore(json.createScoreJson(score));
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