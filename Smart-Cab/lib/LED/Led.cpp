#include "Led.h"
//link to globalExpander defined in IOExpander.cpp
extern IOExpander globalExpander;
//pass globalExpander into our class constructor initializer list
LED::LED():expander(globalExpander)
{}
//toggle the pin (off or on, off if on previously etc)
void LED::toggle(int ledPin){
    //Change value of LED pin state in array
    toggleArray[ledPin] = !toggleArray[ledPin];
    //change led state on the IC 
    expander.IO_digitalWrite(ledPin, toggleArray[ledPin]);
    
}

void LED::operator[](int ledPin){
    //check and see if pin is valid 
    if(ledPin <NUM_LEDS){
    //toggle the LED 
    toggle(ledPin);
    }
}

void  LED::begin(){
    for(int i =0; i < NUM_LEDS; i++){
        //write to led pin and pass state (on or off)
        expander.IO_digitalWrite(i,toggleArray[i]);
    }
}