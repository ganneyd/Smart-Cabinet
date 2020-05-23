#include "Sensors.h"


Sensor::Sensor(uint8_t bus){
    this->bus = bus;
    Multiplexer(this->bus);
    sensorInit();

}

void Sensor::sensorInit(){
    //Initializing the sensor
    this->sensor.reset();//begin with a reset
    this->sensor.begin();
    this->sensor.setMeasurementMode(TEMP_AND_HUMID);//we want to read  both temperature and humidity so we set that
    this->sensor.setRate(MANUAL);//we'll set an interupt to read perodically but if the user wants to read at anytime MANUAL would be our best option
    this->sensor.setTempRes(NINE_BIT);//we dpn't need a lot of resolution so nine bits will do
    this->sensor.setHumidRes(NINE_BIT);//"""""
}
//Setters- set values belonging to the class

//Sets the lower and upper threshold for the Temperature readings
void Sensor::setTempRange( float lowTemp, float highTemp){
    this->lowTemp= lowTemp;
    this->highTemp = highTemp;
}

//Sets the lower and upper threshold for the humidity readings that will trigger an action when too high or low   
void Sensor::setHumidityRange(float lowHumidity, float highHumidity){
    this->lowHumidity = lowHumidity;
    this->highHumidity = highHumidity;
}


//Getters - values being returned 
//read temperature from sensor and return it via Sensor's class function
 float Sensor::readTemp(){

     return this->sensor.readTemp();
 }
//read humidity from sensor and return it via Sensor's class function
 float Sensor::readHumidity(){
     float humidity = this->sensor.readHumidity();
     if(lowHumidity<humidity<highHumidity){
         //flag
     }
     return humidity;
 }
 
 void Sensor::refreshSensor(uint8_t duration){
     this->sensor.enableHeater();
     delay(duration);
     this->sensor.disableHeater();
 }
