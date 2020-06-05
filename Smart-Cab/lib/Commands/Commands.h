#pragma once

#include "Command.h"
#include <Arduino.h>
#include "../SortedLinkedList/SortedLinkedList.h"

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

    void findCommand(const char* command_name , const void* firstParam, const void* secondParam){
            commandArray.findCommand(command_name)->action(firstParam,secondParam);
        }
    
};


//Commands s_Command_Instance = Commands();

