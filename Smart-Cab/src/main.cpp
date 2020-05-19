#include "Arduino.h"
#include "Bluetooth.h"


Bluetooth BT;
void setup(){
    //Initialize the bluetooth communicationa and specify the baudrate(speed to communicate at)
    BT.begin(BAUDRATE);

Serial.begin(BAUDRATE);



Serial.println("hey");

}

void loop(){
    //Simple test to see if inheritance worked, and see if anything is in the bluetooth's buffer
    while(BT.available() >0){
        Serial.println(BT.read());
    }
    while(Serial.available() > 0){
        BT.println(Serial.read());
    }
}