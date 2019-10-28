#ifndef HOURINFO_H
#define HOURINFO_H
#define N 7
#include <map>
#include <string>
#include <utility> // TODO: quitar
/* Indices del array de SensorValues
 * 0 = temperature
 *	1 = humidity
 * 2 = light
 * 3 = soilmoisture
 * 4 = x
 * 5 = y
 * 6 = z
 */
class SensorValues{
	public:
	std::map<std::string, float> m;

	SensorValues();
	float get(std::string);
	void setvalues(float);
};

class HourInfo{
	public:
		SensorValues mean, max, min, acc;
		char dominant_colour;
		int nvalues;
	
		HourInfo();
		void clear();
		void update(SensorValues, char last_colour);
	private:
		void update_max(SensorValues);
		void update_min(SensorValues);
		void update_mean(SensorValues);
};

extern HourInfo hour_info;
#endif
