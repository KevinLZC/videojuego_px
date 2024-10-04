#ifndef MICROSD_H
#define MICROSD_H

#include <SD.h>
#include <SPI.h>
#include "json.h"

#define MICROSD_PIN 5
extern JSON json;

class MicroSD
{
  public:
    String filename = "/scores.txt"; // Archivo donde se guardarán los puntajes
    void init();
    void saveScore(const String &jsonData);
    void getTopScores(String topScores[], int topN);
};

#endif