#pragma once 


/*
This class manages the I/O Expander and handles all outputs/inputs 
to/from the PCF8574 IC. 
Class provides a reliable way to communicate with the IC 

0 to 5 are reserved for LED
6 & 7 are reserved for Fan and Dehumidifier 

*/

#define EXPANDER_ADDR 0x3E
#define NUM_OF_IO_PINS 8
//include Libray for IC
#include "PCF8574.h"

class IOExpander{
    private:

    //All instance of the class will share the same IC
    static PCF8574 s_expander;
     //Set all pinmodes (8) to output as all are going to be desinated outputs
    void begin();
    public:

    //Constructor
    IOExpander();

  

    //Function to toggle pins
    void digitalWrite(uint8_t pin, uint8_t value);
};