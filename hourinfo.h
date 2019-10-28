#ifndef HOURINFO_H
#define HOURINFO_H
#include "sensorvalues.h"

class HourInfo{
	public:
		SensorValues mean, max, min, acc;
		char dominant_colour;
		int nvalues;
	
		HourInfo();
		void clear();
		void update(SensorValues, char last_colour);
		void serial_print();
	private:
		void update_max(SensorValues);
		void update_min(SensorValues);
		void update_mean(SensorValues);
};

extern HourInfo hour_info;
#endif
