#include <Arduino.h>
#include "videojuego.h"

void setup()
{
  Serial.begin(115200);
  menuHandler.setup();
  microSD.saveScore(json.createScoreJson(100));
  microSD.saveScore(json.createScoreJson(120));
  microSD.saveScore(json.createScoreJson(130));
  microSD.saveScore(json.createScoreJson(130));
}

void loop()
{
  menuHandler.handleMenuNavigation();
}