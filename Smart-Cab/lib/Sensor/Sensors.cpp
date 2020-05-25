#include "Sensors.h"


Sensor::Sensor(HDC2080 &sensor,uint8_t bus){
    ARDUINOTRACE_INIT(BAUDRATE);
    TRACE();
    this->sensorPtr = &sensor;
    DUMP(this->bus);
    this->bus = bus;
    DUMP(this->bus);
}
Sensor::~Sensor(){
    delete sensorPtr;
}

void Sensor::moveToPort(){
    DUMP(this->bus);
     //begin the transmission to the multiplexer
        Wire.beginTransmission(0x70);
        //write the bus/port to be used 
        Wire.write(1<<this->bus);
        //close off the transmission
        Wire.endTransmission();
}



