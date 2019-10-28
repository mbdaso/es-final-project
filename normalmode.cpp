#include "mbed.h"
#include "rtos.h"
#include "common.h"
#include "modes.h"
#include "gps.h"

Thread normalmode_thread(osPriorityNormal, 1024); // 1K stack size


	
void SensorValues::clear(){
	temperature = 0;
	humidity = 0;
	light = 0;
	soilmoisture = 0;
	x = 0;
	y = 0;
	z = 0;
}

void HourInfo::clear(){
	mean.clear();
	max.clear();
	min.clear();
	dominant_colour = 'n';
}

void HourInfo::update(SensorValues v){
		update_max(v);
		update_min(v);
		update_mean(v);
}
/*struct SensorValues{
	float temperature;
	float humidity;
	float light;
	float soilmoisture;
	float x, y, z;*/
void HourInfo::update_max(SensorValues v){
	max.temperature = (v.temperature > max.temperature) ? v.temperature : max.temperature; 
	max.humidity = (v.humidity > max.humidity) ? v.humidity : max.humidity; 
	max.light = (v.light > max.light) ? v.light : max.light; 
	max.soilmoisture = (v.soilmoisture > max.soilmoisture) ? v.soilmoisture : max.soilmoisture; 
	max.x = (v.x > max.x) ? v.x : max.x; 
	max.y = (v.y > max.y) ? v.y : max.y; 
	max.z = (v.z > max.z) ? v.z : max.z; 
}

void HourInfo::update_min(SensorValues v){
	pc.printf("\n\rv.temperature %f ", v.temperature);
	min.temperature = (v.temperature < min.temperature) ? v.temperature : min.temperature; 
	min.humidity = (v.humidity < min.humidity) ? v.humidity : min.humidity; 
	min.light = (v.light < min.light) ? v.light : min.light; 
	min.soilmoisture = (v.soilmoisture < min.soilmoisture) ? v.soilmoisture : min.soilmoisture; 
	min.x = (v.x < min.x) ? v.x : min.x; 
	min.y = (v.y < min.y) ? v.y : min.y; 
	min.z = (v.z < min.z) ? v.z : min.z; 
}

void HourInfo::update_mean(SensorValues v){
	mean.temperature = v.temperature / samples_per_hour;
	mean.humidity = v.humidity / samples_per_hour;
	mean.light = v.light / samples_per_hour;
	mean.soilmoisture = v.soilmoisture / samples_per_hour;
	mean.x = v.x / samples_per_hour;
	mean.y = v.y / samples_per_hour;
	mean.z = v.z / samples_per_hour;
}

HourInfo hour_info;

void normal_mode(){
	int elapsed_t = 0, nsamples = 0;
	//int hour = 60*60;
	SensorValues last;
	SensorValues v[3];
	while(event_flags.wait_any(NORMAL_MODE)){
		pc.printf("\n\rNormal: Longitude: %f Latitude: %f", gps_info.lon, gps_info.lat);
		pc.printf("\n\rHour: %02d:%02d:%02d", gps_info.hour, gps_info.minute, gps_info.seconds);
		//TODO: Indicate if value limit with RGB LED
		last.temperature = temp;
		last.humidity = hum;
		last.light = valueLight;
		last.soilmoisture = valueSM;
		last.x = x;
		last.y = y;
		last.z = z;
		
		if(nsamples >= 5)
			hour_info.update(last);
		
		if(elapsed_t >= 30){
			//Si sabemos que en intervalos de 30 segundos van a ser 120 muestras 30*x = 60*60
			//Hacer la media, enviarla por serial, resetear acumulador
			v[0] = hour_info.min;
			v[1] = hour_info.max;
			v[2] = hour_info.mean;
			for(int i = 0; i < 3; i++) {
				if (i == 0) pc.printf("\n\rMin");
				if (i == 1) pc.printf("\n\rMax");
				if (i == 2) pc.printf("\n\rMean");
				
				SensorValues vv = v[i];
				pc.printf("\n\rTemp %f Hum %f Light%f \
					\n\rSoilmoisture %f x %f y %f z %f", 
					vv.temperature, vv.humidity, vv.light, 
					vv.soilmoisture, vv.x, vv.y, vv.z);
				hour_info.clear();
				elapsed_t = 0;
				nsamples = 0;
			}
		}
		
		elapsed_t += NORMAL_MODE_TIME;
		nsamples++;
	}
}
