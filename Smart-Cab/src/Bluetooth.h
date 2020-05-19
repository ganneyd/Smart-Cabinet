
#ifndef Bluetooth_h
#define Bluetooth_h

#include "SoftwareSerial.h"
#include "Arduino.h"
//Pins used by ardunio to recieve and transmit data to bluetooth module
#define RX 2 
#define TX 3
//Pin   connected to the state pin of the bluetooth module
#define STATEPIN 8
//Default baudrate to be used but can be changed in the JSON config
#define BAUDRATE 9600

//Inherit the SoftwareSerial class and wrap in our Bluetooth config to add additional
// features such as changing the baudrate, pin and name etc of the bluetooth module and see if
//there is a connection.
class Bluetooth : public SoftwareSerial{
    
public:
//when bluetooth class is initialized it also initialize software serial with the serial pins to be communicated on

 Bluetooth():SoftwareSerial(RX,TX){};
    
    //check and see if bluetooth module is connected
    bool isConnected(){};


};

#endif