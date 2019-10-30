#include "common.h"
#include "sensorvalues.h"
#include "hourinfo.h"

extern SensorValues last;
void display_rgb(size_t r, size_t g, size_t b){
	ledR.write(r);
	ledG.write(g);
	ledB.write(b);
}
void alarm_callback(){
  while(true){
    if(current_mode == NORMAL_MODE){
			//Encontrar una manera de cambiar el color continuamente
      for(int i = 0; i < NSENSORVALUES ; i++){
				//Encender el color correspondiente al sensor i
				if(last.alarm(i)){
					pc.printf("\n\rAlarm in %s", last.key(i));
					/*keys[0] = "temperature"; color = 000
						keys[1] = "humidity"; color = 001
						keys[2] = "light"; color = 010
						keys[3] = "soilmoisture"; color = 011
						keys[4] = "green_value"; color = 100
						keys[5] = "x"; color = 101
						keys[6] = "y"; color = 101
						keys[7] = "z"; color = 101*/
					if(i < 5){//Alarm color = position of sensor
						display_rgb(i&1, i&2, i&4);
					}
					else {//last 3 positions are same
						display_rgb(1,0,1);
					}
					Thread::wait(800);
					display_rgb(1,1,1);
				}
			}
		}
    else
      event_flags.wait_any(NORMAL_MODE);
  }
}

