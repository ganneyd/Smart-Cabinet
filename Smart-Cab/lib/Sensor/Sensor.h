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

    void moveToPort(uint8_t bus);
  

    public:

    Sensor(void);
 

    //initializes the sensor with default configurations
    void begin(uint8_t bus);

    //gets the humidity reading from the sensor and returns the value 
    float getHumidity(uint8_t bus );
    
    //gets the temperature reading from the sensor and returns the value
    float getTemperature(uint8_t bus);

};


