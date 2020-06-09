#pragma once


#include <Bluetooth.h>
#include <SPI.h>
#include "../SD/SD.h"
#include "../Sensor/Sensor.h"


#include "../../src/ArduinoJson-v6.15.2.h"

//open file and extract saved config
//which light was turned on or  off
//save temperature / humidity range  based on emulsion type
//allow for history save on temperature/humidity reading history so we can use readings to plot graphs
//^^timestamp
extern Bluetooth BT_INSTANCE;
class Config
{
private:
    Bluetooth* l_BT;
    Sensor l_sensor = Sensor();
        //Hold the set frequency for the temperature 
    unsigned int temphumid_frequency;
    //The frequency at which the config state should be saved to the SD Card
    unsigned int save_frequency;
    const int chip_select=4;
    int default_group;
    const char* mode;
    float maxT,maxH;
    int sensorPort[8] = {0,1,2,3,4,5,6,7};
    int _sensorGroup[8] ={1,1,1,1,1,1,1,1};
    const size_t config_capacity = JSON_ARRAY_SIZE(8) + 8*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(5) + 180;
public:
    Config(unsigned int th_freq,unsigned int s_freq )
    :l_BT(&BT_INSTANCE), temphumid_frequency(th_freq),save_frequency(s_freq){

    }

    void begin(){

        while(!SD.begin(chip_select)){
            BT_INSTANCE.println("{res: \" Could not load SD\" }");
            delay(1000);
        }
        l_BT->println("{res: \" Loading Config... \" }");
        

        //go in the config file and load it
        //set the groups for the sensors
        //the group to check the range on
        //the mode to be used - get the default mode's name and search for it and load its values into the system
        //the frequency of the measurements and saves

    }

    void sensorBegin(){
        for(int port : sensorPort){
            l_sensor.begin(port);
        }
    }

    //Setters

    //set the temperature humidity readings interval 
    void setTHFreq(unsigned int th_freq){
        temphumid_frequency = th_freq;
    }
    //set the save frequency 
    void setSFreq(unsigned int s_freq){
        save_frequency = s_freq;
    }
    
    //set the drying mode 
    void setMode( const char* mode_name, unsigned int mode_t, unsigned int mode_h){
        
        this->mode = mode_name;
        this->maxT=mode_t;
        this->maxH = mode_h;
        
    }

    //getters

    const char* getMode(){
        return mode;
    }
    //get temperature and humidity reading frequency 
    unsigned int getTHFreq(){
        return temphumid_frequency;
    }

    //get save frequency 
    unsigned int getSFreq(){
        return save_frequency;
    }

    void setSensorGroup(int port, int group){
        _sensorGroup[port]=group;
    }
   
    //return the default group's number
    int getGroup(){
        return default_group;
    }

   //return the average temperature reading
float getTemp(int sensorGroup){
    //variable to keep track of sensors read
    int num;
    //variable to keep track of sensor temperature readings
    float tempTotal = 0;
    //iterate through connected Sensors and get temperature readings
   for(auto port : sensorPort){
       //check if sensor's group is equal to the group specified by the user
       if(_sensorGroup[port] == sensorGroup){
       //add temperature reading to total
        tempTotal += l_sensor.getTemperature(port);
        //increment num
        num++;
       }
    }
    //calculate the average temperature based on num of read sensors 
    float tempAvg = tempTotal / num;
    //check to see if temperature avg reading is in acceptable range 
   // checkRange(tempAvg);
    //return the average temperature
    return tempAvg;
}



float getHumidity(int sensorGroup){
    int num=0;
    //variable to add up readings from sensors
    float humidityTotal = 0;

    //iterate through all connected sensors and get humidity reading
    for(auto port:sensorPort){
        //check if sensor has same group as specified by the user
        if(_sensorGroup[port] == sensorGroup){  
            //add reading for sensor(i) to total
                 humidityTotal += l_sensor.getHumidity(port);
                 //keep track of how many sensor readings were taken
                 num++;
        }
        
    }

    //return the average based on number of connected sensors ( add one to reflect actual num of sensors)
    // as connectedSensors = 0 represents a connected sensor
    return humidityTotal / num;

}
 
//sets the max temperature and humidity range  as well as the mode it is on
void setRange(const char* dryingMode, float maxT, float maxH){
    this->mode = dryingMode;
    this->maxT = maxT;
    this->maxH= maxH;
}
//return a struct specifying if fans are to be turned on and/or dehumidifier as well
//returns -4 if both can be turned off
// 1 if fans should be turned on
// -1 if fans should be turned off 2 if fans turns off and dehumidifier stays on
//3 if dehumidifier should be turned on
//-3 if dehumidifier should be turned off  -2 if fans stay on and dehumidifier on
//4 if both should be turned on
int checkRange(int sensorGroup){
    int t,h;
    //check temperature 
    t = getTemp(sensorGroup) > maxT ? 1 :-1;
    h = getHumidity(sensorGroup) >maxH ? 3 : -3;

    
    return t+h;

    

}

    void loadConfig(const char* filename){
        File file = SD.open(filename);
        StaticJsonDocument< JSON_ARRAY_SIZE(8) + 8*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(5) + 180> config_doc;
        //rember nesting limit
        DeserializationError err = deserializeJson(config_doc,file);
        // const char* _msg ="{ res:\" "+ err.c_str() + " \" }";
        // if(err)
        //     BT_INSTANCE.println(_msg);
        
        //Load values into sensor class
        JsonArray sensors = config_doc["sensor"];

        for(JsonVariant value : sensors){
            _sensorGroup[value["port"].as<int>()] = value["group"].as<int>();
        }

        setTHFreq(config_doc["measurement-freq"]);
        setSFreq(config_doc["saving-freq"]);
        default_group = config_doc["check-group"];
        
        
    }
};



