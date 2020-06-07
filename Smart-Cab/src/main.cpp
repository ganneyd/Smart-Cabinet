#include "Arduino.h"
 #include "header.h"
#include <Wire.h>
#include "ArduinoJson-v6.15.2.h"


#define INTERVAL 5000

const size_t capacity = JSON_OBJECT_SIZE(3)+20;
StaticJsonDocument<capacity> doc;



Config config = Config(INTERVAL,INTERVAL);
extern Bluetooth BT_INSTANCE;
extern LED LED_INSTANCE;
extern Sensors SENSORS_INSTANCE;

//command that changes the pin or name of the the bluetooth module
Command *np_bt_command = new Command("CB","Changes the name and or pin of the bluetooth module",[](const void* newBTName, const void* newPin){
    const char* name = (const char*)newBTName;
    unsigned int pin = (unsigned int)newPin;
    const char* validPin = (const char*) pin;

    if(name != NULL){
        BT_INSTANCE.setName(name);
    }
    if(sizeof(validPin) == 4)
        BT_INSTANCE.setPin(pin);
    
});

//command that sets emulsion being used
Command *s_mode_command = new Command("SE","Sets the mode  being used to dry the screens",[](const void* modeName, const void* notUsed){
    //in the future we will look for the mode's name in the mode.config.txt but
    //for now just take the mode's info from user
    config.setMode((const char*)modeName,50,20);
    
     

});
//command to toggle leds
Command *led_command =  new Command("LT","Toggles led on or off, whether specific or toggle all on/off",[](const void* port, const void* turnAllOffOn){
        int _port = (int)port;
        bool _turnAllOffOn = (bool)turnAllOffOn;


        if(_port != -1){  
         LED_INSTANCE[_port];
        return;
        }
        else{
            LED_INSTANCE.turnOffOn(_turnAllOffOn);
        }
        
    });

//Commands that gets temp and humidity reading or just one of them
Command *g_sensor_command = new Command("GS", "Description", [](const void* humidity, const void* temperature){
    bool _humidity = (bool)humidity;
    bool _temperature = (bool)temperature;
    if(_humidity){
        Serial.print("Humidity is : ");
        Serial.println(SENSORS_INSTANCE.getHumidity());
    }

    if(_temperature){
        Serial.print("Temperature  is : ");
        Serial.println(SENSORS_INSTANCE.getTemp());
    }

});
unsigned long previousMillis_1, previousMillis_2;

Commands comms = Commands();


void setup(){
Wire.begin();
Serial.begin(BAUDRATE);
//Initialize the bluetooth communicationa and specify the baudrate(speed to communicate at)
BT_INSTANCE.begin(BAUDRATE);  
SENSORS_INSTANCE.begin();

//Start I2C communication 
Wire.begin();
//Start communication between arduino and computer

 

LED_INSTANCE.begin();

comms.addCommand(g_sensor_command);
comms.addCommand(led_command);
comms.addCommand(s_mode_command);
comms.addCommand(np_bt_command);



   
}

void loop(){
if(BT_INSTANCE.available()){
  deserializeJson(doc,BT_INSTANCE);
  comms.findCommand(doc["cmd"].as<char *>(),(const void*) doc["var1"].as<int>(),(const void*) doc["var2"].as<int>());
  while(BT_INSTANCE.available()>0){
  BT_INSTANCE.read();
}
}
}


  
//  unsigned long currentMillis= millis();

//     if(  currentMillis - previousMillis_1 >= 3000){
//       comms.findCommand("GS",(const void*)true,(const void*)true);
//       previousMillis_1 = currentMillis;
//     }

//      if(  currentMillis - previousMillis_2 >= 1000){
//       comms.findCommand("LT",(const void*)0,(const void*)true);
//       delay(500);
//       previousMillis_2 = currentMillis;
//     }



  

