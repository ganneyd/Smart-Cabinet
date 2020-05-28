#include "IOExpander.h"


IOExpander::IOExpander(){
    IOExpander::begin();
}

void IOExpander::begin(){
    for(int i=0; i<8;i++){
        pinMode(i,OUTPUT);
    }
}

void IOExpander:: IO_digitalWrite(uint8_t pin, uint8_t value){
    PCF8574::digitalWrite(pin,value);
}

IOExpander globalExpander = IOExpander();