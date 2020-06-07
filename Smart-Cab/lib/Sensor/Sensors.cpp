#include "Sensors.h"

 

//constructor
Sensors::Sensors(unsigned int num)
//default range
: max_temp(25),max_humidity(45),drying_mode("Normal")
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
    for(unsigned int i=0; i < connectedSensors+1 ; i++){
        
        sensorArray[i]->begin();
    }
    
}

//return the average temperature reading
float Sensors::getTemp(void){
    
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

float Sensors::getHumidity(void){
    
    //variable to add up readings from sensors
    float humidityTotal = 0;

    //iterate through all connected sensors and get humidity reading
    for(unsigned int i=0; i <= connectedSensors; i++){
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
//sets the max temperature and humidity range  as well as the mode it is on
void Sensors::setRange(const char* dryingMode, float maxT, float maxH){
    this->drying_mode = dryingMode;
    this->max_temp = maxT;
    this->max_humidity= maxH;
}
//return a struct specifying if fans are to be turned on and/or dehumidifier as well
//returns -4 if both can be turned off
// 1 if fans should be turned on
// -1 if fans should be turned off 2 if fans turns off and dehumidifier stays on
//3 if dehumidifier should be turned on
//-3 if dehumidifier should be turned off  -2 if fans stay on and dehumidifier on
//4 if both should be turned on
int Sensors::checkRange(){
    int t,h;
    //check temperature 
    t = getTemp() > max_temp ? 1 :-1;
    h = getHumidity() >max_humidity ? 3 : -3;

    
    return t+h;

    

}
//returns the mode the sensors range are set to ex fast slow etc (user defined in config json files)
const char* Sensors::getMode(){
    return this->drying_mode;
}

Sensors::~Sensors(){
    for(unsigned int i=0; i <connectedSensors +1 ; i++){
        delete sensorArray[i];
    }
}


Sensors SENSORS_INSTANCE = Sensors(NUM_SENSORS);