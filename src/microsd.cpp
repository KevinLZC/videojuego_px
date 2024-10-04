#include "microsd.h"

void MicroSD::init()
{
  if (!SD.begin(MICROSD_PIN))
  {
    Serial.println("Error al inicializar la microSD");
  }
  else
  {
    Serial.println("MicroSD inicializada correctamente");
  }
}

void MicroSD::saveScore(const String &jsonData)
{
  File file = SD.open(filename, FILE_APPEND);
  if (file)
  {
    file.println(jsonData);
    file.close();
  }
  else
  {
    Serial.println("Error al abrir el archivo para escribir");
  }
}

void MicroSD::getTopScores(String topScores[], int topN)
{
  File file = SD.open(filename, FILE_READ);

  if (!file)
  {
    topScores[0] = "No hay puntajes";
    return;
  }

  String allScores[100]; // Almacenar hasta 100 puntajes
  int scoreValues[100];  // Para ordenar los puntajes
  int count = 0;

  // Leer cada línea (un JSON) y deserializarla
  while (file.available() && count < 100)
  {
    allScores[count] = file.readStringUntil('\n');
    json.readScoreFromJson(allScores[count], scoreValues[count]);
    count++;
  }
  file.close();

  // Ordenar los puntajes en orden descendente (método burbuja)
  for (int i = 0; i < count - 1; i++)
  {
    for (int j = i + 1; j < count; j++)
    {
      if (scoreValues[i] < scoreValues[j])
      {
        int tempScore = scoreValues[i];
        scoreValues[i] = scoreValues[j];
        scoreValues[j] = tempScore;
      }
    }
  }

  // Guardar los primeros `topN` puntajes en el array `topScores`
  for (int i = 0; i < topN && i < count; i++)
  {
    topScores[i] = scoreValues[i];
  }
}