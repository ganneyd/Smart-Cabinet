#include "Arduino.h"
#include <../lib/Bluetooth/Bluetooth.h>
#include "../Config/Config.h"
#include "../Sensor/Sensors.h"
#include <Wire.h>
#include "../Led/Led.h"

#define INTERVAL 5000

Bluetooth BT;
Sensors sensors=Sensors(3);
LED led = LED();

void setup(){
//Initialize the bluetooth communicationa and specify the baudrate(speed to communicate at)
BT.begin(BAUDRATE);
//Start I2C communication 
Wire.begin();
//Start communication between arduino and computer
Serial.begin(BAUDRATE);
sensors.begin();
led.begin();
}

void loop(){
   for(int i =0; i < 4; i++){
       led[i];
       delay(100);
   }

}