#include "Sensor.h"


Sensor::Sensor(void):sensorPtr(SENOR_ADDR){
    
    this->sensorPtr= HDC2080(SENOR_ADDR);

}


void Sensor::moveToPort(uint8_t bus){
    
     //begin the transmission to the multiplexer
        Wire.beginTransmission(MULTIPLEXER_ADDR);
        //write the bus/port to be used 
        Wire.write(1<<bus);
        //close off the transmission
        Wire.endTransmission();
        
}

void Sensor::begin(uint8_t bus){
    
    
    //Move to the port the sensor is connected to on the multiplexer
    moveToPort(bus);
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

float Sensor::getHumidity(uint8_t bus){
    
    //move to the port the sensor is on to get reliable reading
    moveToPort(bus);
    //return the reading
    return this->sensorPtr.readHumidity();
}

float Sensor::getTemperature(uint8_t bus){
    
    //move to the port the sensor is on to get reliable reading
    moveToPort(bus);
    //return the reading
    return this->sensorPtr.readTemp();
}