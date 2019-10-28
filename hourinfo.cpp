#include "hourinfo.h"
#include <string>
#include <map>
#include <list>		
#include <climits>
			

SensorValues::SensorValues(){
	int nkeys = 7;
	std::string keys [] = {
		"temperature",
		"humidity",
		"light",
		"soilmoisture",
		"x",
		"y",
		"z"
	};
	for (int i = 0; i < nkeys; i++){
		m[keys[i]] = 0.0;
	}
}
				
float SensorValues::get(std::string key){
	return m[key];
}

void SensorValues::setvalues(float value){
	
}


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
	//samples_per_hour = (30/NORMAL_MODE_TIME);
}

void HourInfo::update(SensorValues v, char last_colour){
		update_max(v);
		update_min(v);
		update_mean(v);
}
void HourInfo::update_max(SensorValues v){
	for(auto it ){
		if(max.m.find(v_pair.first) != max.m.end()){
			if(max.m[v_pair.first] < v_pair.second){
				max.m[v_pair.first] = v_pair.second;
			}
		}
	}
}

void HourInfo::update_min(SensorValues v){
	for(const std::pair<std::string, float> v_pair: v){
		if(min.m.find(v_pair.first) != std::map::end){
			if(min.m[v_pair.first] > v_pair.second){
				min.m[v_pair.first] = v_pair.second;
			}
		}
	}
}

void HourInfo::update_mean(SensorValues v){
	nvalues++;
	for(const auto v_pair: v){
		if(mean.m.find(v_pair.first) != std::map::end){
			acc.m[v_pair.first] += v_pair.second;
			mean.m[v_pair.first] = acc.m[v_pair.first]/nvalues;
		}
	}
}

HourInfo hour_info;
