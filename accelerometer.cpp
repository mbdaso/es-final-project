#include "mbed.h"
#include "rtos.h"
#include "MMA8451Q.h"

#define MMA8451_I2C_ADDRESS (0x1d<<1)

float x, y, z;

Thread accelerometer_thread(osPriorityNormal, 512); // 1K stack size

void accelerometer_callback();

void accelerometer_callback() {
  MMA8451Q acc(PB_9, PB_8, MMA8451_I2C_ADDRESS);
	
  while (true) {
		x = acc.getAccX();
    y = acc.getAccY();
    z = acc.getAccZ();
		wait(0.2);
		Thread::wait(200);
 }
}

