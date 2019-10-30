#ifndef SENSORVALUES_H
#define SENSORVALUES_H
#include <string>
//typedef unsigned short const int size_t;


class MbedString{
	private:
		const char * s;
	public:
		void operator=(const char*);
		bool compare(const char*) const;
		const char * c_str();
};

#define MAX_TEMP 25
#define MIN_TEMP 21
#define MAX_HUM 60
#define MIN_HUM 40
#define MAX_LIGHT 80
#define MIN_LIGHT 10
#define MAX_SM 100
#define MIN_SM 4
#define MIN_GREEN 2000
#define MAX_GREEN 3000
#define MAX_X 0.5
#define MIN_X -0.5
#define MAX_Y 0.5
#define MIN_Y -0.5
#define MAX_Z 2
#define MIN_Z -0.5
/* Indices del array de SensorValues
 * 0 = temperature
 * 1 = humidity
 * 2 = light
 * 3 = soilmoisture
 * 7 = green_value
 * 4 = x
 * 5 = y
 * 6 = z
 */
#define NSENSORVALUES 8
class SensorValues{
	float * v;
  float * max;
  float * min;
	MbedString * keys;
  char color;

	public:
	SensorValues();
	float get(size_t);
	const char* key(size_t);
	void set(size_t, float);
	
  int get_index_of_key(const char *) const;
	float& operator[](const size_t);
	float& operator[](const char*);
	void setvalues(float);
	
	void serial_print();
  void set_color(char);
  bool alarm(const size_t);
};
#endif
