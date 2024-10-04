#ifndef JUEGO_H
#define JUEGO_H

// #include "videojuego.h"
// #include "Variables.h"
#include "lcd_handler.h"

// extern uint8_t VERT_PIN  = 32;
// extern VERT_PIN 32;
// extern HORZ_PIN 35
// extern SEL_PIN 34

extern LCDHandler display;

class Juego{
    
    public:
        void movimiento( void );
        bool hasCrashed( void );

    private:
        int lastXValue = 2048;  // Valor inicial centrado
        int lastYValue = 2048;
        // Umbral de sensibilidad para detectar movimientos
        const int threshold = 300;

        // Variable global player para posicion de jugador
        // Columna (0 a 15)
        // Fila (0 a 1)
        // Variables para detectar si el joystick ya ha vuelto al centro
        bool joystickXReleased = true;
        bool joystickYReleased = true;
        void movePoint( int,  int );


};
#endif