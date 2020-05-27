#include "Arduino.h"
#include <../lib/Bluetooth/Bluetooth.h>
#include "../Config/Config.h"
#include "../Sensor/Sensors.h"
#include <Wire.h>

#define INTERVAL 5000
Sensors sensors = Sensors(3);
float avg;
unsigned long prevMillis =0;

Bluetooth BT;

void setup(){
//Initialize the bluetooth communicationa and specify the baudrate(speed to communicate at)
BT.begin(BAUDRATE);
Wire.begin();
Serial.begin(BAUDRATE);
sensors.begin();
}

void loop(){
   unsigned long currentMillis= millis();

    if(  currentMillis - prevMillis >= INTERVAL){
        avg = sensors.getTemp();
        Serial.print("Avg Temp  : "); Serial.print(avg); Serial.println( " (C)");
        prevMillis =  currentMillis;
    }

}