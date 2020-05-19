#include <Bluetooth.h>
//Implent the function declared in the bluetooth header file 
Bluetooth:: Bluetooth():SoftwareSerial(RX,TX){
    pinMode(STATEPIN,INPUT);
}

bool Bluetooth::isConnected(){
    return digitalRead(STATEPIN);
}