#pragma once

/*********************************************************************
 * This class manages the Led
 * only pins 0 to 5 are used for LED control on the PCF8574 IC
 * 
*/

#include "../IOExpander/IOExpander.h"

class LED{

    private:

     IOExpander expander;
      boolean toggleArray[5] = {1,1,1,1,1};
    
    //extern IOExpander expander;
     //toggle pin off or on
    void toggle(int ledPin);
     
    public:
    //constructor for LED with default array that turns off all the lights
    LED();
    //set the state of the LED pins
    void begin();
    //overload the [] operator so we can access the led like an array to provide cleaner code
    void  operator[](int);
};