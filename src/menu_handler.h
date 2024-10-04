#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include "lcd_handler.h"
#include "microsd.h"

// Declaraciones externas
extern LCDHandler display; // No necesita instancia aquí
extern MicroSD microSD;    // Declaración externa de MicroSD
extern JSON json;          // Declaración externa de JSON

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
  void handleMenuNavigation();
};

#endif