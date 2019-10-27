#ifndef MODES_H
#define MODES_H
#include "rtos.h"

extern Thread testmode_thread; // 1K stack size
extern Thread normalmode_thread; // 1K stack size
extern Thread advancedmode_thread;

void normal_mode();
void test_mode();
void advanced_mode();

#define N 7
class SensorValues{
	public:
		float temperature;
		float humidity;
		float light;
		float soilmoisture;
		float x, y, z;
		
		SensorValues(): temperature(0), humidity(0),
										light(0), soilmoisture(0),
										x(0), y(0), z(0){}
											
		void clear();
};

struct HourInfo{
	SensorValues mean, max, min;
	char dominant_colour;
	
	HourInfo(): dominant_colour('n'){}
};

extern HourInfo hour_info;

#endif
