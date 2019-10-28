#include "mbed.h"
#include "rtos.h"
#include "common.h"
#include "modes.h"
#include "gps.h"

Thread normalmode_thread(osPriorityNormal, 1024); // 1K stack size

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
