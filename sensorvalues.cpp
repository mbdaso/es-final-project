#include "common.h"
#include "sensorvalues.h"
#include <string>


void MbedString::operator=(const char * s_){
	s = s_;
}

bool MbedString::compare(const char * rhs) const{
	char a = '0', b = '0';
	int i = 0;
	while(a != '\0' && b != '\0'){
		a = s[i];
		b = rhs[i];
		if(a != b)
			return false;
		i++;
	}
	return (a==b);
}

const char * MbedString::c_str(){
	return s;
}
			
SensorValues::SensorValues(){
	v = new float[NSENSORVALUES];
	keys = new MbedString [NSENSORVALUES];
	keys[0] = "temperature";
	keys[1] = "humidity";
	keys[2] = "light";
	keys[3] = "soilmoisture";
	keys[4] = "green_value";
	keys[5] = "x";
	keys[6] = "y";
	keys[7] = "z";
	setvalues(0.0);
	max = new float[NSENSORVALUES];
	max[0] = MAX_TEMP;
	max[1] = MAX_HUM;
	max[2] = MAX_LIGHT;
	max[3] = MAX_SM;
	max[4] = MAX_GREEN;
	max[5] = MAX_X;
	max[6] = MAX_Y;
	max[7] = MAX_Z;
	min = new float[NSENSORVALUES];
	min[0] = MIN_TEMP;
	min[1] = MIN_HUM;
	min[2] = MIN_LIGHT;
	min[3] = MIN_SM;
	min[4] = MIN_GREEN;
	min[5] = MIN_X;
	min[6] = MIN_Y;
	min[7] = MIN_Z;
}

float SensorValues::get(size_t i){
	return v[i];
}

const char * SensorValues::key(size_t i){
	return keys[i].c_str();
}

void SensorValues::setvalues(float value){
	for (int i = 0; i < NSENSORVALUES; i++){
		v[i] = value;
	}
}

void SensorValues::set(size_t i, float value){
	v[i] = value;
}

int SensorValues::get_index_of_key(const char* key) const{
  for(int i = 0; i < NSENSORVALUES; i++){
		if (keys[i].compare(key))
			return i;
	}
}

float & SensorValues::operator[](size_t i){
	return v[i];
}

float & SensorValues::operator[](const char* key){
  int i = get_index_of_key(key);
  if(i >= 0 && i < NSENSORVALUES){
    return v[i];
  }
}

void SensorValues::serial_print(){
	for(int i = 0; i < NSENSORVALUES; i++){
		pc.printf("\n\r%s: %f", keys[i].c_str(), v[i]);
	}
}

bool SensorValues::alarm(const size_t i){
	return (v[i] > max[i] || v[i] < min[i]);
}

void SensorValues::set_color(char color){
  this->color = color;
}
