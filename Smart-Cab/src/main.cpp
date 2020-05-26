#include "Arduino.h"
#include <../lib/Bluetooth/Bluetooth.h>
#include "../Config/Config.h"
#include "../Sensor/Sensor.h"
#include <Wire.h>

#define INTERVAL 5000

// HDC2080 sensor = HDC2080(0x40);
 Sensor sensor_0 = Sensor(0);
// Sensor sensor_1 = Sensor(sensor,7);
// Sensor sensor_2 = Sensor(sensor,2);
float sen0,sen1,sen2;
unsigned long prevMillis =0;

//Bluetooth BT;

void setup(){
    //Initialize the bluetooth communicationa and specify the baudrate(speed to communicate at)
    //BT.begin(BAUDRATE);
Wire.begin();
Serial.begin(BAUDRATE);
Serial.println("hey");

sensor_0.begin();
// sensor_1.begin();
// sensor_2.begin();

}

void loop(){
   unsigned long currentMillis= millis();

    if(  currentMillis - prevMillis >= INTERVAL){
       sen0 = sensor_0.getTemperature();
        Serial.print("Temperature reading from sensor : "); Serial.println(sen0);
        prevMillis =  currentMillis;
    }

}