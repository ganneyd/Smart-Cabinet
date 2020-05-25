#include "Bluetooth.h"

//Implent the function declared in the bluetooth header file 
bool Bluetooth::isConnected(){
    return digitalRead(STATEPIN);
}