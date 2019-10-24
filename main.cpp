#include "mbed.h"
#include "rtos.h"
#include "gps.h"
#include "MMA8451Q.h"


Serial pc(USBTX,USBRX,19200);

extern Thread threadANALOG;
extern void ANALOG_thread();
extern float valueSM;

extern Thread lightsensor_thread;
extern void lightsensor_callback();
extern float valueLight;

extern Thread humiditytemperature_thread;
extern void humiditytemperature_callback();
extern float hum, temp;

extern Thread accelerometer_thread;
extern void accelerometer_callback();
extern float x, y, z;

extern struct Gps_info gps_info;
extern Thread gps_thread;
//extern void gps_callback();
// main() runs in its own thread in the OS

extern Thread colorsensor_thread;
extern void colorsensor_callback();
extern int clear_value, red_value, green_value, blue_value;
extern char dominant_color;

/*
Dudas: 
¿Cómo funciona la memoria de un Thread?
¿Qué es mejor: usar extern, ficheros de cabecera (.h) o clases?
*/


int main() {

  threadANALOG.start(ANALOG_thread);
  humiditytemperature_thread.start(humiditytemperature_callback);
	lightsensor_thread.start(lightsensor_callback);
	accelerometer_thread.start(accelerometer_callback);
	gps_thread.start(gps_callback);
	colorsensor_thread.start(colorsensor_callback);

  pc.printf("mbed-os-rev: %d.%d.%d\r\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);	
  
	while(true){ 
		
		pc.printf("\n\rSoil Moisture: %.2f%%", valueSM);
    pc.printf("\n\rLIGHT: %.2f%%", valueLight);  
		pc.printf("\n\rACCELEROMETER: X_axis: %.2f, Y_axis: %.2f, Z_axis: %.2f", x, y, z);
		pc.printf("\n\rTEMP/HUM: Temperature: %.2f C. Relative Humidity: %.4f%", temp, hum);
		pc.printf("\n\r#Sats: %d, Lat(UTC): %.6f, Long(UTC): %.6f, Altitude: %.1f, GPS_time: %2d:%2d:%2d",
								gps_info.nsats, gps_info.lat, gps_info.lon, gps_info.alt,
								gps_info.hour, gps_info.minute, gps_info.seconds);
		pc.printf("\n\rClear (%d), Red (%d), Green (%d), Blue (%d), Dominant Color: %c", clear_value, red_value, green_value, blue_value, dominant_color);
		pc.printf("\n");
    wait(2);
  }
}

