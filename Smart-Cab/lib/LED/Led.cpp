#include "Led.h"

LED::LED(boolean toggleArray[5]={1,1,1,1,1})
:LEDToggleArray(toggleArray),ledExpander(){
    begin();
}

void LED::toggle(int ledPin){
    //Change value of LED pin state in array
    LEDToggleArray[ledPin] = !LEDToggleArray[ledPin];
    //change led state on the IC 
    ledExpander.digitalWrite(ledPin, LEDToggleArray[ledPin]);
    
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
        ledExpander.digitalWrite(i,LEDToggleArray[i]);
    }
}