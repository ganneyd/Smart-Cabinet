#pragma once
//Buadrate we plan to use by default 
#define BAUDRATE 9600
//PCF8574 I/O Expander address 
#define EXPANDER_ADDR 0x3E
//number of leds we plan to drive
#define NUM_LEDS 6
//address for the HDC2080 Temperature/Humidity Sensor
#define SENOR_ADDR 0x40
#define MULTIPLEXER_ADDR 0x70
//Pins used by arduino to receive and transmit data to bluetooth module
#define RX 2 
#define TX 3
//Pin   connected to the state pin of the bluetooth module
#define STATEPIN 8


//open file and extract saved config
//which light was turned on or  off
//save temperature / humidity range  based on emulsion type
//allow for history save on temperature/humidity reading history so we can use readings to plot graphs
//^^timestamp

