#include "mbed.h"
#include "rtos.h"
#include "common.h"
#include "modes.h"
#include "gps.h"

Thread normalmode_thread(osPriorityNormal, 1024); // 1K stack size

/*struct SensorValues{
	float temperature;
	float humidity;
	float light;
	float soilmoisture;
	float x, y, z;*/
	
void SensorValues::clear(){
	temperature = 0;
	humidity = 0;
	light = 0;
	soilmoisture = 0;
	x = 0;
	y = 0;
	z = 0;
}

void normal_mode(){
	int elapsed_t = 0;
	while(event_flags.wait_any(NORMAL_MODE)){
		
		
		
		// The global location of the plant (coordinates) is sent to the computer every 30
//seconds. This should include the GPS time (UTC) converted to local time.
		//TODO: Indicate 
		pc.printf("\n\rNormal : Longitude: %f Latitude: %f", gps_info.lon, gps_info.lat);
		pc.printf("\n\rHour: %d:%d:%d", gps_info.hour, gps_info.minute, gps_info.seconds);
		
		//Indicate value limit with RGB LED
		
		elapsed_t += 30;
	}
}
