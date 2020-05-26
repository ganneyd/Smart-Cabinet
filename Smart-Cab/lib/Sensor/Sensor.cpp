#include "Sensor.h"


Sensor::Sensor(uint8_t bus):sensorPtr(0x40){
    ARDUINOTRACE_INIT(BAUDRATE);
    TRACE();
    this->sensorPtr= HDC2080(0x40);
    DUMP(this->bus);
    this->bus = bus;
    DUMP(this->bus);
}
Sensor::~Sensor(void){
   
}

void Sensor::moveToPort(void){
    TRACE();
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
    TRACE();
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
    TRACE();
    //move to the port the sensor is on to get reliable reading
    moveToPort();
    //return the reading
    return this->sensorPtr.readTemp();
}

void Sensor::performHeatCycle(int duration){
    //move to the port for this sensor on the multiplexer to ensure the correct sensor's 
    //heating element is enabled
    moveToPort();
    //enable the heating element
    this->sensorPtr.enableHeater();
    //pause for the duration 
    //******************
    //change this to something better;
    delay(duration);
    //disable the heating element 
    this->sensorPtr.disableHeater();
}

int Sensor::getBus(){
    return this->bus;
}