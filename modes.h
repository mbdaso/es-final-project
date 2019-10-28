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

class HourInfo{
	public:
		SensorValues mean, max, min;
		char dominant_colour;
		int samples_per_hour;
		int nsamples;
		bool ready;
		
		HourInfo(): dominant_colour('n'), 
								samples_per_hour(30/NORMAL_MODE_TIME){}
		void clear();
		void update(SensorValues);
	private:
		void update_max(SensorValues);
		void update_min(SensorValues);
		void update_mean(SensorValues);
};

extern HourInfo hour_info;

#endif
