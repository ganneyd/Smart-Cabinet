#include "Arduino.h"
#include <../lib/Bluetooth/Bluetooth.h>
#include "../Config/Config.h"
#include "../Sensor/Sensors.h"
#include <Wire.h>
#include "../Led/Led.h"
#include "../Commands/Command.h"
#define INTERVAL 5000

Bluetooth BT;
Sensors sensors=Sensors(3);
LED led = LED();

Command<int,LED,HardwareSerial> led_command = Command<int,LED,HardwareSerial>("LT",
[](int ledPin,LED led_obj, HardwareSerial serial){
    led_obj[ledPin];
    serial.println("Successful in toggling led : " + ledPin);
    serial.flush();
});

void setup(){
//Initialize the bluetooth communicationa and specify the baudrate(speed to communicate at)
BT.begin(BAUDRATE);
//Start I2C communication 
Wire.begin();
//Start communication between arduino and computer
Serial.begin(BAUDRATE);
sensors.begin();
led.begin();
Serial.println(led_command.getName());
}

void loop(){
   for(int i =0; i < 3; i++){
    led_command.command_func(i,led,Serial);
    Serial.flush();
       delay(2000);
   }

  

}