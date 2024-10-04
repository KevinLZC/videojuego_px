#include "menu_handler.h"
#include <Arduino.h>

extern JSON json;

void MenuHandler::setup()
{
  display.lcd_init_display();
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  display.showWelcomeScreen();
  microSD.init();
}

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

void welcomeHandler(bool buttonPressed)
{
  if (buttonPressed)
  {
    currentState = MAIN_MENU;
    display.showMainMenu(mainMenuIndex);
  }
}

void mainMenuHandler(int yValue, bool joystickMoved, bool buttonPressed, unsigned long gameStartTime)
{
  if (DECREMENTO(yValue) && !joystickMoved)
  {
    mainMenuIndex++;
    if (mainMenuIndex >= mainMenuItems)
      mainMenuIndex = 0;
    joystickMoved = true;
    display.showMainMenu(mainMenuIndex);
  }

  if (INCREMENTO(yValue) && !joystickMoved)
  {
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

void highScoresHandler(bool buttonPressed)
{
  if (buttonPressed)
  {
    currentState = MAIN_MENU;
    display.showMainMenu(mainMenuIndex);
  }
}

void inGameHandler(bool buttonPressed, unsigned long gameStartTime)
{
  if (buttonPressed)
  {
    currentState = IN_GAME_MENU;
    inGameMenuIndex = 0;
    display.showInGameMenu(inGameMenuIndex);
  }

  if (millis() - gameStartTime > 5000)
  {
    currentState = GAME_OVER;
    gameOverMenuIndex = 0;
    display.showGameOverMenu(gameOverMenuIndex);
  }
}

void inGameMenuHandler(int yValue, bool joystickMoved, bool buttonPressed, unsigned long gameStartTime)
{
  if (DECREMENTO(yValue) && !joystickMoved)
  {
    inGameMenuIndex++;
    if (inGameMenuIndex >= inGameMenuItems)
      inGameMenuIndex = 0;
    joystickMoved = true;
    display.showInGameMenu(inGameMenuIndex);
  }

  if (INCREMENTO(yValue) && !joystickMoved)
  {
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

void gameOverHandler(int yValue, bool joystickMoved, bool buttonPressed, unsigned long gameStartTime)
{
  if (DECREMENTO(yValue) && !joystickMoved)
  {
    gameOverMenuIndex++;
    if (gameOverMenuIndex >= gameOverMenuItems)
      gameOverMenuIndex = 0;
    joystickMoved = true;
    display.showGameOverMenu(gameOverMenuIndex);
  }

  if (INCREMENTO(yValue) && !joystickMoved)
  {
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

void MenuHandler::handleMenuNavigation()
{
  int yValue = analogRead(PIN_Y);
  bool joystickMoved = false;
  buttonPressed = isButtonPressed();
  switch (currentState)
  {
  case WELCOME:
    welcomeHandler(buttonPressed);
    break;

  case MAIN_MENU:
    mainMenuHandler(yValue, joystickMoved, buttonPressed, gameStartTime);
    break;

  case HIGH_SCORES:
    highScoresHandler(buttonPressed);
    break;

  case IN_GAME:
    inGameHandler(buttonPressed, gameStartTime);
    break;

  case IN_GAME_MENU:
    inGameMenuHandler(yValue, joystickMoved, buttonPressed, gameStartTime);
    break;

  case GAME_OVER:
    gameOverHandler(yValue, joystickMoved, buttonPressed, gameStartTime);
    break;
  }
}