#include "mbed.h"
#include "rtos.h"
#include "common.h"
#include "modes.h"

Thread advancedmode_thread(osPriorityNormal, 1024); // 1K stack size
void advanced_mode(){
	while(event_flags.wait_any(ADVANCED_MODE)){
		
		pc.printf("\n\rAdvanced mode !");
	}
}
