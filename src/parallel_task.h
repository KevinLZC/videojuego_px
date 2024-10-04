#ifndef PARALLEL_TASK_H
#define PARALLEL_TASK_H

#include "menu_handler.h"

extern MenuHandler menuHandler;

class ParallelTask{
  public:
    static void startTasks();
    static void menuTask(void *pvParameters);
};

#endif