#pragma once

/*********************************************************************
 * This class manages the Led
 * only pins 0 to 5 are used for LED control on the PCF8574 IC
 * 
*/

#include "../IOExpander/IOExpander.h"
#include "../Macros/ArdunioTrace.h"
#include "Define.h"


class LED{

    private:

     IOExpander expander;
      bool toggleArray[NUM_LEDS] = {true,true,true,true,true};
    
    //extern IOExpander expander;
    public:
     //toggle pin off or on
    void toggle(int ledPin);
     
    
    //constructor for LED with default array that turns off all the lights
    LED();
    //set the state of the LED pins
    void begin();
    //overload the [] operator so we can access the led like an array to provide cleaner code
    void  operator[](int);
    //function to turn off or on all connected led
    void turnOffOn(bool all_led_state);
};