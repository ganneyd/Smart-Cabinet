#pragma once
//make abstract class so that we can use various classes in sorted array and be certain that they 
//have this method
class SortedArrayInterface{
    //classes that inherit this class has to implement this function
    virtual const char* getName() = 0;
}