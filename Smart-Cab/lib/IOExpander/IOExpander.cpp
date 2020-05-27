#include "IOExpander.h"

IOExpander::IOExpander()
    :s_expander(EXPANDER_ADDR){
        //initialize the IC
        begin();
    }

IOExpander::begin(){
    for(int i=0; i<NUM_OF_IO_PINS; i++){
  s_expander.pinMode(i,OUTPUT);
 }
 
 //start up the i/o expander for use
 s_expander.begin();
}

IOExpander::digitalWrite(uint8_t pin, uint8_t value){
    if(pin<NUM_OF_IO_PINS){
    s_expander.digitalWrite(pin,value);
    }
}