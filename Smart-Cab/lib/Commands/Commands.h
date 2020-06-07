#pragma once

#include "Command.h"
#include <Arduino.h>
#include "../SortedArray/SortedArray.h"

class Commands
{
private:
   SortedArray commandArray;
public:
    Commands(){
        commandArray = SortedArray();
    }

    void addCommand (Command* command){
        commandArray.insertObj(command);
    }

    bool findCommand(const char* command_name , const void* firstParam, const void* secondParam){
            return commandArray.findCommand(command_name,firstParam,secondParam);
        }
    
};


