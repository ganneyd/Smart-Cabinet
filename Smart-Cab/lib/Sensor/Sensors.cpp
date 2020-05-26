#include "Sensors.h"


Sensor::Sensor(HDC2080 &sensor,uint8_t bus){
    ARDUINOTRACE_INIT(BAUDRATE);
    TRACE();
    this->sensorPtr = &sensor;
    DUMP(this->bus);
    this->bus = bus;
    DUMP(this->bus);
}
Sensor::~Sensor(void){
    delete sensorPtr;
}

void Sensor::moveToPort(void){
    DUMP(this->bus);
     //begin the transmission to the multiplexer
        Wire.beginTransmission(0x70);
        //write the bus/port to be used 
        Wire.write(1<<this->bus);
        //close off the transmission
        Wire.endTransmission();
}

void Sensor::begin(void){
    //Move to the port the sensor is connected to on the multiplexer
    moveToPort();
    // Initialize I2C communication
    this->sensorPtr->begin();
  // Begin with a device reset
  this->sensorPtr->reset();
  
  
  // Configure Measurements
  this->sensorPtr->setMeasurementMode(TEMP_AND_HUMID);  // Set measurements to temperature and humidity
  this->sensorPtr->setRate(MANUAL);                     // Set measurement frequency to MANUAL as we would like to get readings
                                                        // as often as we want
  this->sensorPtr->setTempRes(FOURTEEN_BIT);
  this->sensorPtr->setHumidRes(FOURTEEN_BIT);
  
  //begin measuring
  this->sensorPtr->triggerMeasurement();
}

float Sensor::getHumidity(void){
    //move to the port the sensor is on to get reliable reading
    moveToPort();
    //return the reading
    return this->sensorPtr->readHumidity();
}

float Sensor::getTemperature(void){
    //move to the port the sensor is on to get reliable reading
    moveToPort();
    //return the reading
    return this->sensorPtr->readTemp();
}

void Sensor::performHeatCycle(int duration){
    //enable the heating element
    this->sensorPtr->enableHeater();
    //pause for the duration 
    //******************
    //change this to something better;
    delay(duration);
    //disable the heating element 
    this->sensorPtr->disableHeater();
}

