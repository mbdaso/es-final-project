#include "mbed.h"
#include "rtos.h"
#include "common.h"
#include "modes.h"
#include "gps.h"
#include "hourinfo.h"

Thread normalmode_thread(osPriorityNormal, 1024); // 1K stack size

void normal_mode(){
	int nsamples = 0;
	SensorValues last;
	while(event_flags.wait_any(NORMAL_MODE)){
		//Recoger ultima muestra
		last["temperature"] = temp;
		last["humidity"] = hum;
		last["light"] = valueLight;
		last["soilmoisture"] = valueSM;
		last["x"] = x;
		last["y"] = y;
		last["z"] = z;
		//Actualizar hour_info
		if(nsamples > 2)
			hour_info.update(last, dominant_color);
		//Imprimir datos del gps
		//pc.printf("\n\rNormal: Longitude: %f Latitude: %f", gps_info.lon, gps_info.lat);
		pc.printf("\n\rHour: %02d:%02d:%02d - %d", gps_info.hour, gps_info.minute, gps_info.seconds, nsamples);
		//Imprimir hour_info si han pasado 10 *NORMAL_MODE_TIME
		if(!(nsamples % 10)){
			hour_info.serial_print();
			//nsamples = 0;
		}
		nsamples++;
	}
}
