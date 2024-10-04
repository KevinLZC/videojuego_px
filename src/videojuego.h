#ifndef VIDEOJUEGO_H
#define VIDEOJUEGO_H

#include "lcd_handler.h"
#include "microsd.h"
#include "menu_handler.h"
#include "parallel_task.h"

MicroSD microSD;
LCDHandler display;
MenuHandler menuHandler;
ParallelTask parallelTask;

#endif