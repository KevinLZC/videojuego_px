#ifndef LCD_HANDLER_H
#define LCD_HANDLER_H

#include <LiquidCrystal_I2C.h>
#include "microsd.h"

extern MicroSD microSD;

#define VALOR_INICIAL 2048
#define VALOR_TOPE 4095
#define PWM_MIN 0
#define PWM_MAX 255

#define INCREMENTO(a) (a > VALOR_INICIAL + 200 ? 1 : 0)
#define DECREMENTO(a) (a < VALOR_INICIAL - 200 ? 1 : 0)

#define PIN_X 34
#define PIN_Y 35
#define PIN_BUTTON 32

enum State
{
  WELCOME,
  MAIN_MENU,
  IN_GAME,
  IN_GAME_MENU,
  GAME_OVER,
  HIGH_SCORES
};

extern State currentState;
extern int score;
extern int mainMenuIndex, inGameMenuIndex, gameOverMenuIndex;
extern const int mainMenuItems, inGameMenuItems, gameOverMenuItems;
extern const char *menuItems[], *inGameItems[], *gameOverItems[];

class LCDHandler
{
public:
  void lcd_init_display();
  void lcd_clear_display();
  void lcd_set_cursor(int column, int row);
  void showWelcomeScreen();
  void showMainMenu(int index);
  void showInGameMenu(int index);
  void showGameOverMenu(int index);
  void showHighScores();
};

#endif