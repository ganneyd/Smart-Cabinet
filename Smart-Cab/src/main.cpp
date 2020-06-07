#include "Arduino.h"
 #include "header.h"
#include <Wire.h>
#include "ArduinoJson-v6.15.2.h"


#define INTERVAL 5000

const size_t req_capacity = JSON_OBJECT_SIZE(3)+30;
const size_t res_capacity = JSON_OBJECT_SIZE(4)+40;
//Json document that handles the request sent by the user
StaticJsonDocument<req_capacity> req_doc;
//Json document that handles the response that is sent to the user
//specifying if the request was valid or not
StaticJsonDocument<res_capacity> res_doc;


Config config = Config(INTERVAL,INTERVAL);
extern Bluetooth BT_INSTANCE;
extern LED LED_INSTANCE;
extern Sensors SENSORS_INSTANCE;
Commands comms = Commands();

/*
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
    
});*/

//command that sets emulsion being used
Command *s_mode_command = new Command("SE","Sets the mode  being used to dry the screens",[](const void* modeName, const void* getMode){
    //in the future we will look for the mode's name in the mode.config.txt but
    //for now just take the mode's info from user
    int _getMode = (int) getMode;
    if(_getMode > 0){
       res_doc["mode"].set(config.getMode());
    }else{
    config.setMode((const char*)modeName,50,20);
    }
    
     

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
       res_doc["h"].set(SENSORS_INSTANCE.getHumidity());
    }

    if(_temperature){
        Serial.print("Temperature  is : ");
        Serial.println(SENSORS_INSTANCE.getTemp());
        res_doc["t"].set(SENSORS_INSTANCE.getTemp());
    }

});
unsigned long previousMillis_1, previousMillis_2;




void setup(){
//Begin communication on I2C bus
Wire.begin();
//Start communication between arduino and computer
//For debugging only
Serial.begin(BAUDRATE);
//Initialize the bluetooth communicationa and specify the baudrate(speed to communicate at)
BT_INSTANCE.begin(BAUDRATE); 
//Initialize the sensors 
SENSORS_INSTANCE.begin();

LED_INSTANCE.begin();

    comms.addCommand(g_sensor_command);
    comms.addCommand(led_command);
    comms.addCommand(s_mode_command);
    //comms.addCommand(np_bt_command);  
}

void loop(){

//Check if anyting is available in the buffer
if(BT_INSTANCE.available()){
    req_doc.to<JsonObject>();
    //deserialize json document
  DeserializationError err = deserializeJson(req_doc,BT_INSTANCE);
  //check if its successful
  if(err){
      //if not successful do nothing
  }else{
      bool found;
      if(req_doc.containsKey("var_name")){
         found = comms.findCommand(req_doc["cmd"].as<char *>(),(const void*) req_doc["var_name"].as<char *>(),(const void*) req_doc["var2"].as<int>());
         
      }else{
        found = comms.findCommand(req_doc["cmd"].as<char *>(),(const void*) req_doc["var1"].as<int>(),(const void*) req_doc["var2"].as<int>());
      }
      //tell user if command was found or not
    res_doc["cmd"].set(found);
  }
    
    //if  successful or not send response with err code  
    res_doc["res"].set(err.c_str());
  serializeJsonPretty(res_doc,BT_INSTANCE);
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



  

