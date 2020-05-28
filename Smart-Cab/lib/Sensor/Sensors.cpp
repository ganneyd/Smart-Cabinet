#include "Sensors.h"

Sensors::Sensors(unsigned int num)
{
    add(num);
}
void Sensors::addAtBus(uint8_t bus){
    connectedSensors++;
    
    sensorArray[connectedSensors] =  new Sensor(bus);
}

void Sensors::add( unsigned int num){

    for(unsigned int i=0; i<num;i++){
        addAtBus(i);
    }
}
void Sensors::begin(){
    for(unsigned int i=0; i<= connectedSensors ; i++){
        sensorArray[i]->begin();
    }
}
float Sensors::getTemp(){
    float tempTotal = 0;
   for(unsigned int i=0; i <= connectedSensors ; i++){
        tempTotal += getTemp(i);
    }
    float tempAvg = tempTotal / (connectedSensors+1);
    return tempAvg;
}

float Sensors::getTemp(int sensorPort){
    return sensorArray[sensorPort]->getTemperature();
}

