#pragma once 
#include <Arduino.h>

//Written by Ganney A.Dortch

/* Class to hold commands that trigger an action given the commands name/key is a match
each command has a key/name and an action to perform if that key is a match
*/
template<typename V, class C_Obj, class S_Obj>

class Command{
    private:
    const char *command_name;
    public:

    Command (const char* name, void (*func)(V,C_Obj,S_Obj) )
    : command_name(name),command_func(func)
        {
            
        }   
    

    const char* getName(){
       return this->command_name;
    }
    void (*command_func)(V ,  C_Obj ,  S_Obj  );


};