#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include "lcd_handler.h"

extern LCDHandler display;

class MenuHandler
{
private:
  unsigned long gameStartTime = 0;
  unsigned long lastButtonPress = 0;
  const unsigned long debounceDelay = 200;
  bool buttonPressed = false;

public:
  void setup();
  bool isButtonPressed();
  void handleMenuNavigation(bool);
};

#endif