#include "Arduino.h"

#define onboard 8

void setup(){
pinMode(onboard, OUTPUT);

}

void loop(){
    digitalWrite(onboard,HIGH);
    delay(100);
    digitalWrite(onboard,LOW);
    delay(100);
}