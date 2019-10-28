#ifndef HOURINFO_H
#define HOURINFO_H
#include "sensorvalues.h"

class HourInfo{
	public:
		SensorValues mean, max, min, acc;
		char dominant_colour;
		int nvalues;
		int * rgb_acc;
	
		HourInfo();
		void clear();
		void update(SensorValues, char last_colour);
		void serial_print();
	private:
		void update_max(SensorValues);
		void update_min(SensorValues);
		void update_mean(SensorValues);
		void update_dominant_colour(char last_colour);
		char maximum(int rgb[3]);
};

extern HourInfo hour_info;
#endif
