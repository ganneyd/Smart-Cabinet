#pragma once

#include <HDC2080.h>
#include <Wire.h>
#include "../Macros\ArdunioTrace.h"
#include "../Config/Config.h"

class Sensor{
    
    private:

    //Save a pointer to the HDC2080 (Humidity sensor) class as all of the sensor share the same address and 
    //with the help of the multiplexer we can use the same instance to communicate to the sensors with;
    HDC2080 *sensorPtr;

    //save bus/port number that the sensor is on
    uint8_t bus;

    //Enable to change the port we are currently communicating to on the multiplexer so we can distinguish the 
    //sensors currently attached to it 
    void moveToPort();
    
    public:
    //Constructor pass sensor by reference instead of by value to reduce overhead
    Sensor(HDC2080 &sensor,uint8_t bus);
    ~Sensor();
    void begin();

    

};