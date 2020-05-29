#pragma once

#include "Sensor.h"
#include <Arduino.h>


class Sensors
{
private:
    /* data */
    //array to hold references to sensors
    Sensor *sensorArray[8];
    //add a group of sensors at once 
     void add(unsigned int num);
     //keep track of connected sensors
     unsigned int connectedSensors = -1;
public:
    Sensors(unsigned int num);
    //add sensor at a port number (bus) on the multiplexer
    void addAtBus(uint8_t bus);
    //initialize all the sensors
    void begin();
    //get specific temperature reading for a particular sensor
    float getTemp(int sensorPort);
    //get averaged temperature fro all connected sensors
    float getTemp();
    //get specific humidity reading for a particular sensor
    float getHumidity(int sensorPort);
    //get average humidity reading 
    float getHumidity();
    
   //~Sensors();
};


