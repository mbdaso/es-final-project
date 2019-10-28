#include "hourinfo.h"
#include "common.h"

HourInfo::HourInfo(){
	clear();
}
void HourInfo::clear(){ 
	nvalues = 0;
	mean.setvalues(0.0);
	acc.setvalues(0.0);
	max.setvalues(-9999999);
	min.setvalues(9999999); 
	dominant_colour = 'n';
	//samples_per_hour = (30/NSENSORVALUESORMAL_MODE_TIME);
}

void HourInfo::update(SensorValues v, char last_colour){
		update_max(v);
		update_min(v);
		update_mean(v);
}
void HourInfo::update_max(SensorValues v){
	for(int i = 0; i < NSENSORVALUES; i++){
		if(max[i] < v[i])
			max[i] = v[i];
	}
}

void HourInfo::update_min(SensorValues v){
	for(int i = 0; i < NSENSORVALUES; i++){
		if(min[i] > v[i])
			min[i] = v[i];
	}
}

void HourInfo::update_mean(SensorValues v){
	nvalues++;
	for(int i = 0; i < NSENSORVALUES; i++){
		acc[i] += v[i];
		mean[i] = acc[i] / nvalues;
	}
}

void HourInfo::serial_print(){
	pc.printf("\n\r++++++++++++++++++MAX++++++++++++++++++++");
	max.serial_print();
	pc.printf("\n\r------------------MIN--------------------");
	min.serial_print();
	pc.printf("\n\r==================MEAN====================");
	mean.serial_print();
	pc.printf("\n\r··················COLOR···················");
	pc.printf("\n\r%c", this->dominant_colour);
}

HourInfo hour_info;
