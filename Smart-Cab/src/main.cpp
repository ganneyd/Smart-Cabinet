#include "Arduino.h"
#include <../lib/Bluetooth/Bluetooth.h>
#include "../Config/Config.h"
#include "../Sensor/Sensors.h"
#include <Wire.h>
#include "../Led/Led.h"
#define INTERVAL 5000

Bluetooth BT;
Sensors sensors=Sensors(3);
extern LED LED_INSTANCE;

void setup(){
//Initialize the bluetooth communicationa and specify the baudrate(speed to communicate at)
BT.begin(BAUDRATE);
//Start I2C communication 
Wire.begin();
//Start communication between arduino and computer
Serial.begin(BAUDRATE);
sensors.begin();
LED_INSTANCE.begin();

}

void loop(){
   

  

}