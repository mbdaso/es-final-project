#include "common.h"
#include "sensorvalues.h"
#include <string>


void MbedString::operator=(const char * s_){
	s = s_;
}

bool MbedString::compare(const char * rhs){
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
	keys[4] = "x";
	keys[5] = "y";
	keys[6] = "z";
	setvalues(0.0);
}

float SensorValues::get(size_t i){
	return v[i];
}

void SensorValues::setvalues(float value){
	for (int i = 0; i < NSENSORVALUES; i++){
		v[i] = value;
	}
}

void SensorValues::set(size_t i, float value){
	v[i] = value;
}

int SensorValues::get_index_of_key(const char* key){
  for(int i = 0; i < NSENSORVALUES; i++){
		if (keys[i].compare(key))
			return i;
};

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

bool SensorValues::alarm(const char* key){
  int i = get_index_of_key(key);
  if(i >= 0 && i < NSENSORVALUES){
    return (v[i] > max[i] || v[i] < min[i]);
  }  
}

void SensorValues::set_color(char color){
  this->color = color;
}

bool SensorValues::alarm(const char* key){
  
}
