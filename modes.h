#ifndef MODES_H
#define MODES_H
#include "rtos.h"
#include "common.h"

extern Thread testmode_thread; // 1K stack size
extern Thread normalmode_thread; // 1K stack size
extern Thread advancedmode_thread;

void normal_mode();
void test_mode();
void advanced_mode();



#endif
