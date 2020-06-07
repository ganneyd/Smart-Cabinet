#include "Sensor.h"


Sensor::Sensor(uint8_t bus):sensorPtr(SENOR_ADDR){
    
    this->sensorPtr= HDC2080(SENOR_ADDR);
    
    this->bus = bus;

}
Sensor::~Sensor(void){
   
}

void Sensor::moveToPort(void){
    
     //begin the transmission to the multiplexer
        Wire.beginTransmission(MULTIPLEXER_ADDR);
        //write the bus/port to be used 
        Wire.write(1<<this->bus);
        //close off the transmission
        Wire.endTransmission();
        
}

void Sensor::begin(void){
    
    
    //Move to the port the sensor is connected to on the multiplexer
    moveToPort();
    // Initialize I2C communication

    this->sensorPtr.begin();

  // Begin with a device reset

  this->sensorPtr.reset();

  
  // Configure Measurements
  this->sensorPtr.setMeasurementMode(TEMP_AND_HUMID);  // Set measurements to temperature and humidity
  
  this->sensorPtr.setRate(FIVE_SECONDS);                     // Set measurement frequency to MANUAL as we would like to get readings
                                                        // as often as we want
  this->sensorPtr.setTempRes(FOURTEEN_BIT);
 
  this->sensorPtr.setHumidRes(FOURTEEN_BIT);
 
  //begin measuring
  this->sensorPtr.triggerMeasurement();
}

float Sensor::getHumidity(void){
    
    //move to the port the sensor is on to get reliable reading
    moveToPort();
    //return the reading
    return this->sensorPtr.readHumidity();
}

float Sensor::getTemperature(void){
    
    //move to the port the sensor is on to get reliable reading
    moveToPort();
    //return the reading
    return this->sensorPtr.readTemp();
}


int Sensor::getBus(){
    return this->bus;
}

void  Sensor::setGroup(uint8_t groupNum){
    this->group_num = groupNum;
}

uint8_t Sensor::getGroup(){
    return this->group_num;
}