
#ifndef Bluetooth_h
#define Bluetooth_h

#include "SoftwareSerial.h"
#include "Arduino.h"
#include "../Config/Config.h"
//Inherit the SoftwareSerial class and wrap in our Bluetooth config to add additional
// features such as changing the baudrate, pin and name etc of the bluetooth module and see if
//there is a connection.
class Bluetooth
 : public SoftwareSerial{
    
public:
//when bluetooth class is initialized it also initialize software serial with the serial pins to be communicated on

 Bluetooth()
 //default Sofware serial or rather constant since these pins will alwayse be used to communicate
 //to the bluetooth module
 :SoftwareSerial(RX,TX){
    pinMode(STATEPIN,INPUT);
 };
    
    //check and see if bluetooth module is connected
    bool isConnected();


};

#endif