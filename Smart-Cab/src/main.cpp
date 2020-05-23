#include "Arduino.h"
#include <../lib/Bluetooth/Bluetooth.h>
#include "../lib/Sensor/Sensors.h"

bool prevPrint = false;


Bluetooth BT;

//Function to read and log temp and humidity readings from sensor
void readSensor(Sensor& sensor){
    Serial.print("Now reading from ");
    Serial.println(sensor.getBus());
    Serial.print("Temperature reading : ");
    Serial.println(sensor.readTemp());
    Serial.print("Humidity reading : ");
    Serial.println(sensor.readHumidity());
}
void setup(){
    //Initialize the bluetooth communicationa and specify the baudrate(speed to communicate at)
    BT.begin(BAUDRATE);

Serial.begin(BAUDRATE);



Serial.println("hey");

}

void loop(){

    // //Simple test to see if sensors are able to communicate properly via multiplexer
    // //sensor 1 
    //     readSensor(sensor_1);
    //     delay(2000);
    // //sensor 2
    //     readSensor(sensor_2);
    //             delay(2000);

    // //sensor 3
    //     readSensor(sensor_3);
    //             delay(2000);

    // //sensor 4
    //     readSensor(sensor_4);
    //             delay(2000);


    // //Simple test to see if inheritance worked, and see if anything is in the bluetooth's buffer
    // while(BT.available() >0){
    //     char c;
    //     String line;
    //     while (BT.available() >0){
    //         c = BT.read();
    //         line+=c;
    //     }
        
    //     Serial.println(line);
    // }
    // while(Serial.available() > 0){
    //     BT.println(Serial.read());
    // }

    // if(BT.isConnected() && !prevPrint){
    //     Serial.println("Bluetooth Connected");
    //     prevPrint=true;
    // }else if (!BT.isConnected() && prevPrint){
    //     Serial.println("Lost connection");
    //     prevPrint=false;
    // }
}