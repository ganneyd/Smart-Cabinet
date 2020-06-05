#pragma once

#include "../LED/Led.h"

extern LED LED_INSTANCE;
class Command
{
private:
 
    const char* command_name;
    const char* command_description;

public:

    Command(const char* name, const char* description, void (*func)(const void* param_1,const void* param_2))
    :command_name(name),command_description(description),l_instance(LED_INSTANCE), action(func){

    }
    LED l_instance;

     void (*action)(const void* param_1, const void* param_2);
    //virtual float getActionF(const void* param_1, const void* param_2);
    const char* getName(){
        return command_name;
    }
    const char* getDescription(){
        return command_description;
    }
};

