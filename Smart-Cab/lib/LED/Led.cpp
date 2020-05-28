#include "Led.h"
extern IOExpander globalExpander;
LED::LED():expander(globalExpander)
{}

void LED::toggle(int ledPin){
    //Change value of LED pin state in array
    toggleArray[ledPin] = !toggleArray[ledPin];
    //change led state on the IC 
    expander.IO_digitalWrite(ledPin, toggleArray[ledPin]);
    
}

void LED::operator[](int ledPin){
    //check and see if pin is valid 
    if(ledPin <5){
    //toggle the LED 
    toggle(ledPin);
    }
}

void  LED::begin(){
    for(int i =0; i < 5 ; i++){
        //write to led pin and pass state (on or off)
        expander.IO_digitalWrite(i,toggleArray[i]);
    }
}