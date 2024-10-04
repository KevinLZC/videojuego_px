#ifndef JSON_H
#define JSON_H

#include <ArduinoJson.h>

class JSON
{
public:
  JSON() {}
  String createScoreJson(int score);
  void readScoreFromJson(const String &jsonStr, int &score);
};

#endif