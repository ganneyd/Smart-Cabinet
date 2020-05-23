#include "Arduino.h"
#include <../lib/Bluetooth/Bluetooth.h>

bool prevPrint = false;

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
        char c;
        String line;
        while (BT.available() >0){
            c = BT.read();
            line+=c;
        }
        
        Serial.println(line);
    }
    while(Serial.available() > 0){
        BT.println(Serial.read());
    }

    if(BT.isConnected() && !prevPrint){
        Serial.println("Bluetooth Connected");
        prevPrint=true;
    }else if (!BT.isConnected() && prevPrint){
        Serial.println("Lost connection");
        prevPrint=false;
    }
}