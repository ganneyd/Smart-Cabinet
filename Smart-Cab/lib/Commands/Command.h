#pragma once


class Command
{
private:
 
    const char* command_name;
    const char* command_description;

public:

    Command(const char* name, const char* description, void (*func)(const void* param_1,const void* param_2))
    :command_name(name),command_description(description), action(func){

    }


     void (*action)(const void* param_1, const void* param_2);
    //virtual float getActionF(const void* param_1, const void* param_2);
    const char* getName(){
        return command_name;
    }
    const char* getDescription(){
        return command_description;
    }
};

