#include "mbed.h"
#include "rtos.h"

#ifndef GPS_H
#define GPS_H

//Variables del GPS

struct Gps_info{
	uint8_t nsats;
	float lat, lon, alt;
	uint8_t hour;
	uint8_t minute;
	uint8_t seconds;
};

//Thread gps_thread(osPriorityNormal, 2048); // 2K stack size

void gps_callback(); 

#endif