#include "mbed.h"
#include "rtos.h"



float hum, temp;

Thread humiditytemperature_thread(osPriorityNormal, 512); // 1K stack size

void humiditytemperature_callback(); 

void humiditytemperature_callback() {
  I2C misensor(PB_9,PB_8);
	misensor.frequency(100000);
	char tx_buff[2];
	char rx_buff[2];
	
   
  while (true) {

    // READ MEASURES
			
		tx_buff[0] = 0xF3;  // CMD: Measure Temperature, No Hold Master Mode
				
    misensor.write(0x80, (char *) tx_buff, 1);	// Device ADDR: 0x80 = SI7021 7-bits address shifted one bit left.
    Thread::wait(100);
    misensor.read(0x80, (char*) rx_buff, 2);		// Receive MSB = rx_buff[0], then LSB = rx_buff[1]
  
    temp = (((rx_buff[0] * 256 + rx_buff[1]) * 175.72) / 65536.0) - 46.85;	// Conversion based on Datasheet

    tx_buff[0] = 0xF5;  // CMD: Measure Relative Humidity, No Hold Master Mode
    
    misensor.write(0x80, (char *) tx_buff, 1);
    Thread::wait(100);
    misensor.read(0x80, (char*) rx_buff, 2);		// Receive MSB first, then LSB
  
    hum = (((rx_buff[0] * 256 + rx_buff[1]) * 125.0) / 65536.0) - 6;				// Conversion based on Datasheet
  
  Thread::wait(200);
 }
}




  