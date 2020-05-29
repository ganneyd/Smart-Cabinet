#include "Sensors.h"
//constructor
Sensors::Sensors(unsigned int num)
{
    //add number of sensors specified by num param 
    add(num);
}
//add sensor at specfic bus
void Sensors::addAtBus(uint8_t bus){
    //add one to connectedSensors
    connectedSensors++;
    //add sensor to array and specify bus as passed in the function
    sensorArray[connectedSensors] =  new Sensor(bus);
}
//add a number of sensors at once
void Sensors::add( unsigned int num){
    //iterate for num times and add a sensor
    for(unsigned int i=0; i<num;i++){
        addAtBus(i);
    }
}
//initialize the sensor
void Sensors::begin(){
    //iterate through sensors and initialize each
    for(unsigned int i=0; i<= connectedSensors ; i++){
        sensorArray[i]->begin();
    }
}

//return the average temperature reading
float Sensors::getTemp(){
    //variable to keep track of sensor temperature readings
    float tempTotal = 0;
    //iterate through connected Sensors and get temperature readings
   for(unsigned int i=0; i <= connectedSensors ; i++){
       //add temperature reading to total
        tempTotal += getTemp(i);
    }
    //calculate the average temperature based on num of connected sensors , add 1 to the connectedSensors
    //since when connectedSensors = 0 it represents a connected sensor but adding 1 represnet actual 
    //numeric value of connected sensors
    float tempAvg = tempTotal / (connectedSensors+1);
    //check to see if temperature avg reading is in acceptable range 
   // checkRange(tempAvg);
    //return the average temperature
    return tempAvg;
}
//return temperature reading for specific sensor
float Sensors::getTemp(int sensorPort){
    return sensorArray[sensorPort]->getTemperature();
}

float Sensors::getHumidity(){
    //variable to add up readings from sensors
    float humidityTotal = 0;

    //iterate through all connected sensors and get humidity reading
    for(unsigned int i; i <= connectedSensors; i++){
        //add reading for sensor(i) to total
        humidityTotal +=getHumidity(i);
    }

    //return the average based on number of connected sensors ( add one to reflect actual num of sensors)
    // as connectedSensors = 0 represents a connected sensor
    return humidityTotal / (connectedSensors +1);

}
 float Sensors::getHumidity(int sensorPort){
     //check if connected
     //return humidity reading for sensor at port specified by sensorPort variable param
     return sensorArray[sensorPort]->getHumidity();
 }

