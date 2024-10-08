// #include "juego.h"
// #include "song.h"

// soundtracks my_soundtrack;

// void Juego :: movimiento()
// {

// // Leer los valores del joystick
//   int xValue = analogRead(PIN_X);
//   int yValue = analogRead(PIN_Y);

//   // Verifica si el joystick en el eje X ha vuelto al centro
//   if (abs(xValue - 2048) < threshold) {
//     joystickXReleased = true;
//   }

//   // Verifica si el joystick en el eje Y ha vuelto al centro
//   if (abs(yValue - 2048) < threshold) {
//     joystickYReleased = true;
//   }

//   // Movimiento en el eje X
//   if (joystickXReleased) {
//     if (xValue > lastXValue + threshold && player[0] < 15) {  // Mover a la derecha
//       movePoint(player[0] + 1, player[1]);
//       joystickXReleased = false;  // Joystick no está en el centro
//     }
//     else if (xValue < lastXValue - threshold && player[0] > 0) {  // Mover a la izquierda
//       movePoint(player[0] - 1, player[1]);
//       joystickXReleased = false;  // Joystick no está en el centro
//     }
//   }

//   // Movimiento en el eje Y
//   if (joystickYReleased) {
//     if (yValue > lastYValue + threshold && player[1] < 1) {  // Mover hacia abajo
//       movePoint(player[0], player[1] + 1);
//       joystickYReleased = false;  // Joystick no está en el centro
//     }
//     else if (yValue < lastYValue - threshold && player[1] > 0) {  // Mover hacia arriba
//       movePoint(player[0], player[1] - 1);
//       joystickYReleased = false;  // Joystick no está en el centro
//     }
//   }

//   // Pequeño retraso para evitar que se mueva demasiado rápido
//   delay(150);
// };

// // Función para mover
// void Juego :: movePoint(int newX, int newY)
// {
//   // Borrar el punto anterior
//   lcdDisplay.print(32,player[0],player[1]);

<<<<<<< HEAD
// Función para mover
void Juego :: movePoint(int newX, int newY) 
{
  // Borrar el punto anterior
  display.print(32,player[0],player[1]);
=======
//   // Actualizar las coordenadas
//   player[0] = newX;
//   player[1] = newY;
>>>>>>> 4452679eb9b58807d3a09c05d7a047e51d994a0b

//   // Dibujar el nuevo punto

<<<<<<< HEAD
  // Dibujar el nuevo punto
  
  display.print(1,player[0],player[1]);
=======
//   lcdDisplay.print(1,player[0],player[1]);
>>>>>>> 4452679eb9b58807d3a09c05d7a047e51d994a0b

//   // Mostrar en el monitor serial
//   Serial.print("X Pos: ");
//   Serial.print(player[0]);
//   Serial.print(" Y Pos: ");
//   Serial.println(player[1]);
// }

// bool Juego :: hasCrashed(){
//   bool returnVal = false;

<<<<<<< HEAD
  return returnVal;
}

void Juego :: startPlayer(){
  display.print(5,player[0],player[1]);
}
=======
//   if(
//     (player[0] == obstacle1[0] && player[1] == obstacle1[1])
//     ||
//     (player[0] == obstacle2[0] && player[1] == obstacle2[1])
//     )
//   {
//     returnVal = true;
//     Serial.print("choco");
//     my_soundtrack.death_sound();
//   }

//   return returnVal;
// }
>>>>>>> 4452679eb9b58807d3a09c05d7a047e51d994a0b
