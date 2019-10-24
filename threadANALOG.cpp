#include "mbed.h"
#include "rtos.h"

float valueSM=0.0;

Thread threadANALOG(osPriorityNormal, 512); // 1K stack size

void ANALOG_thread(); 

void ANALOG_thread() {
	
	AnalogIn soilmois(PA_0); 
		
	while (true) {
		valueSM=soilmois*100;

		Thread::wait(200);		  
  }
}
