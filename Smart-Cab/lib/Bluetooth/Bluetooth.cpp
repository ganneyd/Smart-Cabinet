#include "Bluetooth.h"
#include <Arduino.h>

//Implent the function declared in the bluetooth header file 
bool Bluetooth::isConnected(){
    return digitalRead(STATEPIN);
}

//send new name to bluetooth module
void Bluetooth::setName(const char* name){
    char buffer[40];
    strncpy(buffer, "AT+NAME=", sizeof(buffer));
    strncpy(buffer,name, sizeof(buffer));
    sendMsg(buffer);
}
//send new pin to bluetooth module 
void Bluetooth::setPin(unsigned int pin){
    char buffer[40];
    strncpy(buffer, "AT+PSWD=", sizeof(buffer));
    strncpy(buffer,(const char*)pin, sizeof(buffer));
    sendMsg(buffer);
}
//enter AT+mode
void Bluetooth::sendMsg(const char* msg){
   end();
   begin(BLUETOOTH_BAUD);
   write(msg);
   const char* response;
   if(available() >0){
       char c;
       while(available()>0){
           c = read();
           response += c;
       }
   }
   end();
   begin(BAUDRATE);
   Serial.end();
   Serial.begin(BAUDRATE);
   Serial.println(response);
   Serial.end();
   Serial.begin(BAUDRATE);
   Serial.println(response);

}

Bluetooth BT_INSTANCE = Bluetooth();