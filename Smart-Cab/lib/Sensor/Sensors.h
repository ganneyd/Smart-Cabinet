#pragma once

#include "Sensor.h"
#include <Arduino.h>


class Sensors
{
private:
    /* data */
    
    Sensor *sensorArray[8];
     void add(unsigned int num);
     unsigned int connectedSensors = -1;
public:
    Sensors(unsigned int num);
    void addAtBus(uint8_t bus);
    void begin();
    float getTemp(int sensorPort);
    float getTemp();
    
   //~Sensors();
};


