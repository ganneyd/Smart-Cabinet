#pragma once
#include "../Commands/Command.h"


class SortedArray{
    private:
     Command* t_array[10];
     int elmNum;

     int binarySearch(const char* key,int left, int right){
        if( right >= left){

            int mid = (left + right)/2;
            DUMP(mid);
            if(strcmp(t_array[mid]->getName(),key)==0){
                return mid;
                TRACE();
            }

            if(strcmp(key,t_array[mid]->getName()) <0){
                return binarySearch(key,left,mid-1);
                DUMP(mid-1);
            }
            DUMP(mid+1);
            return binarySearch(key,mid+1, right);

        }
        return -1;
    }
    public:

    SortedArray()
    :elmNum(0){}
    

    void insertObj(Command* new_obj){
        
        if (elmNum >= 10){
                    return; 

        }
        int i; 
        for (i = elmNum - 1; (i >= 0 && (strcmp(new_obj->getName(),t_array[i]->getName())) < 0);i--){
                    t_array[i + 1] = t_array[i];
        } 
        
        t_array[i + 1] = new_obj; 
        elmNum++;
    }
    

    Command* findCommand(const char* command_name){
        int obj_pos = binarySearch(command_name,0, elmNum);
        DUMP(command_name);
        DUMP(sizeof(command_name));
        DUMP(obj_pos);
        DUMP(elmNum);

        for(int i=0; i < elmNum; i++){
           DUMP(t_array[i]->getName());
        }
        if (obj_pos == -1){

            return new  Command("ERR","Error",[](const void* param, const void* param_2){
            
            });
        }
        return t_array[obj_pos];
    }

    ~SortedArray(){
        for(int i=0; i <elmNum+1; i++){
            delete t_array[i];
        }
    }
};
