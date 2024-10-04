#ifndef MICROSD_H
#define MICROSD_H

#include <SD.h>
#include <SPI.h>

#define MICROSD_PIN 5

class MicroSD
{
  public:
    String filename = "/scores.txt"; // Archivo donde se guardarán los puntajes
    void init();
    void saveScore(int score);
    void getTopScores(String topScores[], int topN);
};

#endif