#pragma once

#include "HDC2080.h"
#include <Wire.h>
#include "ArdunioTrace.h"
#include "Define.h"

class Sensor{

    private:

    //Save a pointer to the HDC2080 (Humidity sensor) class as all of the sensor share the same address and 
    //with the help of the multiplexer we can use the same instance to communicate to the sensors with;
    HDC2080 sensorPtr;

    //save bus/port number that the sensor is on
    uint8_t bus;

    //Enable to change the port we are currently communicating to on the multiplexer so we can distinguish the 
    //sensors currently attached to it 

    void moveToPort(void);
    //group the sensor belongs to
    uint8_t group_num;
    public:

    Sensor(void);
    //Constructor pass sensor by reference instead of by value to reduce overhead
    Sensor(uint8_t bus);
    ~Sensor(void);

    //initializes the sensor with default configurations
    void begin(void);

    //gets the humidity reading from the sensor and returns the value 
    float getHumidity(void);
    
    //gets the temperature reading from the sensor and returns the value
    float getTemperature(void);

    //sets the group number of the sensor
    void setGroup(uint8_t groupNum);

    //returns the group number of the sensor
    uint8_t getGroup();
    

    int getBus();

};