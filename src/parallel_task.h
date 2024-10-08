#ifndef PARALLEL_TASK_H
#define PARALLEL_TASK_H

#include "menu_handler.h"
#include "juego.h"
#include "lcd_handler.h"

extern MenuHandler menuHandler;
extern Juego myJuego;
extern LCDHandler display;

TaskHandle_t HiloMenu;
TaskHandle_t HiloObstaculo1;
TaskHandle_t HiloObstaculo2;
TaskHandle_t HiloPlayerMov;
TaskHandle_t HiloPausa;

class ParallelTask{
  public:
    static void startTasks();
    static void menuTask(void *pvParameters);
    static void obstacle1Task( void *pvParameters );
    static void obstacle2Task( void *pvParameters );
    static void playerMov( void *pvParameters );
    static void checkingPause( void *pvParameters );
    static void createGameTask( void *pvParameters );
};

#endif