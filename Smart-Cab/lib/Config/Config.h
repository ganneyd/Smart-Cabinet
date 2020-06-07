#pragma once


#include <Bluetooth.h>

#include "Sensors.h"

//open file and extract saved config
//which light was turned on or  off
//save temperature / humidity range  based on emulsion type
//allow for history save on temperature/humidity reading history so we can use readings to plot graphs
//^^timestamp
extern Bluetooth BT_INSTANCE;

extern Sensors SENSORS_INSTANCE;

class Config
{
private:
        
        //Save pointer to sensors class 
        Sensors* l_Sensors;
        //Hold the set frequency for the temperature 
    unsigned int temphumid_frequency;
    //The frequency at which the config state should be saved to the SD Card
    unsigned int save_frequency;
public:
    Config(unsigned int th_freq,unsigned int s_freq )
    :l_Sensors(&SENSORS_INSTANCE), temphumid_frequency(th_freq),save_frequency(s_freq){

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
        l_Sensors->setRange(mode_name,mode_t,mode_h);
        
    }

    //getters

    const char* getMode(){
        return l_Sensors->getMode();
    }
    //get temperature and humidity reading frequency 
    unsigned int getTHFreq(){
        return temphumid_frequency;
    }

    //get save frequency 
    unsigned int getSFreq(){
        return save_frequency;
    }

    
    ~Config(){
        
        delete l_Sensors;
    }
};



