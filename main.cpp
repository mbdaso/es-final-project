#include "mbed.h"
#include "rtos.h"
#include "common.h"
#include "gps.h"
#include "modes.h"
#include "MMA8451Q.h"

//Preguntas:
// 1) 
// a) Usar señales para los threads:
// Pros: no hay que crearlos y destruirlos
// Contras: no se puede "resetear" el thread, hay que mantenerlos ejecutandose
// b) Alternativa: thread.start() thread.terminate()
// Cuál es mejor??
// 2) Cómo funcionan las señales? Siempre hay que mandar 0x01?

Serial pc(USBTX,USBRX,19200);
int current_mode = TEST_MODE;

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

Ticker mode_ticker;

EventFlags event_flags;

void mode_signal_sender(){ //Send current mode to all modes
	event_flags.set(current_mode);
}

void userButton_isr(){
	mode_ticker.detach();
	switch(current_mode){
		case TEST_MODE:
			current_mode = NORMAL_MODE;
			mode_ticker.attach(mode_signal_sender, NORMAL_MODE_TIME);
			break;
		case NORMAL_MODE:
			current_mode = ADVANCED_MODE;
			mode_ticker.attach(mode_signal_sender, ADVANCED_MODE_TIME);
			break;
		default:
			current_mode = TEST_MODE;
			mode_ticker.attach(mode_signal_sender, TEST_MODE_TIME);
			break;
		/*default:
			current_mode = ERROR_MODE;*/
	}	
	led1 = static_cast<int>(current_mode == TEST_MODE);
	led2 = static_cast<int>(current_mode == NORMAL_MODE);
	led3 = static_cast<int>(current_mode == ADVANCED_MODE);
}

int main(){
	//Setup things
	soilmoisture_thread.start(soilmoisture_callback);
	lightsensor_thread.start(lightsensor_callback);
	gps_thread.start(gps_callback);
	i2c_thread.start(i2c_callback);
	
//  humiditytemperature_thread.start(humiditytemperature_callback);	
//	accelerometer_thread.start(accelerometer_callback);
//	colorsensor_thread.start(colorsensor_callback);

	testmode_thread.start(test_mode);
	normalmode_thread.start(normal_mode);
	advancedmode_thread.start(advanced_mode);
	
	pc.printf("\n\rTest thread id: %x", testmode_thread.gettid());
	pc.printf("\n\rNormal thread id: %x", normalmode_thread.gettid());

  pc.printf("\n\rmbed-os-rev: %d.%d.%d\r\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);	
	
	InterruptIn userButton(PB_2);	
	userButton.rise(&userButton_isr);
	
	current_mode = NORMAL_MODE;	
	mode_ticker.attach(mode_signal_sender, NORMAL_MODE_TIME);
	
	//current_mode = ERROR_MODE;	
	//pc.printf("\n\rPress user button to start");
		
	while(true){ //Job done
		wait(osWaitForever);
	}
}
