/*#pragma once is accepted for compatibility with other compilers, 
+and enables you to use other forms of header guard coding. 
However, ARM recommends to use #ifndef and #define coding 
because this is more portable.*/

#ifndef COMMON_H
#define COMMON_H

#include "rtos.h"

//https://os.mbed.com/docs/mbed-os/v5.14/apis/eventflags.html
#define TEST_MODE (1UL << 0)
#define NORMAL_MODE (1UL << 1)
#define ADVANCED_MODE (1UL << 2)
#define ERROR_MODE (1UL << 3)

#define TEST_MODE_TIME 2
#define NORMAL_MODE_TIME 3
#define ADVANCED_MODE_TIME 0.5



extern int current_mode; 
extern Thread soilmoisture_thread;
extern void soilmoisture_callback();
extern float valueSM;

extern Thread lightsensor_thread;
extern void lightsensor_callback();
extern float valueLight;



extern struct Gps_info gps_info;
extern Thread gps_thread;
//extern void gps_callback();

extern Thread i2c_thread;
extern void i2c_callback();
extern float hum, temp;
extern int clear_value, red_value, green_value, blue_value;
extern char dominant_colour;
extern float x, y, z;


extern Serial pc;

extern EventFlags event_flags;

//TODO: arreglar
extern DigitalOut ledR; //RGB led - red light
extern DigitalOut ledG;  //RGB led - green light 
extern DigitalOut ledB;  //RGB led - blue light
#endif
