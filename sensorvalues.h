#ifndef SENSORVALUES_H
#define SENSORVALUES_H
#include <string>
/* Indices del array de SensorValues
 * 0 = temperature
 *	1 = humidity
 * 2 = light
 * 3 = soilmoisture
 * 4 = x
 * 5 = y
 * 6 = z
 */
#define NSENSORVALUES 7

class MbedString{
	private:
		const char * s;
	public:
		void operator=(const char*);
		bool compare(const char*);
		const char * c_str();
};

class SensorValues{
	float * v;
	MbedString * keys;

	public:
	SensorValues();
	float get(size_t);
	void set(size_t, float);
	
	float& operator[](const size_t);
	float& operator[](const char*);
	void setvalues(float);
	
	void serial_print();
};
#endif
