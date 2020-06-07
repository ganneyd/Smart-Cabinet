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
     //duration for how long heaters are enabled for
     int duration =3000;
     float max_temp, max_humidity;
     const char* drying_mode;
     int num_groups;
public:
    Sensors(unsigned int num);
    //add sensor at a port number (bus) on the multiplexer
    void addAtBus(uint8_t bus);
    //initialize all the sensors
    void begin();
    //activate heating element
    void setRange(const char* dryingMode, float maxTemp, float maxHumidity);
    //checks if readings are within range set
    int checkRange(int sensorGroup);
    //returns the drying mode
    const char* getMode();
    //set group for sensor
    void setGroup(int sensorPort, uint8_t groupNum);
    //get specific temperature reading for a particular sensor group
    float getTemp(int sensorGroup);
    //get specific humidity reading for a particular sensor
    float getHumidity(int sensorGroup);
    
    ~Sensors();
};


