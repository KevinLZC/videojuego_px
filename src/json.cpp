#include "json.h"

String JSON::createScoreJson(int score)
{
  DynamicJsonDocument doc(1024);
  doc["score"] = score;

  String output;
  serializeJson(doc, output);
  return output;
}

void JSON::readScoreFromJson(const String &jsonStr, int &score)
{
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, jsonStr);

  if (!error)
  {
    score = doc["score"].as<int>();
  }
}