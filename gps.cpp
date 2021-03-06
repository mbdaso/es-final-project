#include "gps.h"
#include "mbed.h"
#include "rtos.h"
#include "MBed_Adafruit_GPS.h"

/*struct Gps_info{
	uint8_t nsats;
	float lat, lon, alt;
	uint8_t hour;
	uint8_t minute;
	uint8_t seconds;
} gps_info;*/

Thread gps_thread(osPriorityNormal, 2048); // 2K stack size
Gps_info gps_info;
//void gps_callback(); 

void gps_callback(){
	Serial * gps_serial;
	gps_serial = new Serial(PA_9, PA_10);
	Adafruit_GPS gps(gps_serial);
	gps.begin(9600);  //sets baud rate for GPS communication; note this may be changed via Adafruit_GPS::sendCommand(char *)
                       //a list of GPS commands is available at http://www.adafruit.com/datasheets/PMTK_A08.pdf
	gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); //these commands are defined in MBed_Adafruit_GPS.h; a link is provided there for command creation
	gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
	gps.sendCommand(PGCMD_ANTENNA);
	
	Thread::wait(1000);
	
	uint16_t degrees;
	float minutes;
	
	
	while(true){
		gps.read();   //c = gps.read(); pc.printf(c);
		//check if we recieved a new message from GPS, if so, attempt to parse it,
		if ( gps.newNMEAreceived() ) {
			if ( !gps.parse(gps.lastNMEA()) ) {
				continue;   
			}    
		}
		
		gps_info.nsats = gps.satellites;
		
		degrees=gps.latitude/100.0;
		minutes=(gps.latitude/100)-degrees;
		gps_info.lat = degrees+(minutes*10.0/6.0);
		if (gps.lat =='S'){
			gps_info.lat=gps.lat*(-1);
		}
		
		degrees=gps.longitude/100.0;
		minutes=(gps.longitude/100)-degrees;
		gps_info.lon = degrees+(minutes*10.0/6.0);
		if (gps.lon=='W'){
			gps_info.lon=gps.longitude*(-1);
		}
		
		gps_info.alt = gps.altitude;
		
		if(gps.hour!=23)
			gps_info.hour = gps.hour+1;
		else
			gps_info.hour = 0;
		gps_info.minute = gps.minute;
		gps_info.seconds = gps.seconds;
   }
}
