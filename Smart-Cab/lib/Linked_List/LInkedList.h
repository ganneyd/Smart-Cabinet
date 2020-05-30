#pragma once
#include "../Commands/Command.h"

//Implement sorted link list

template <>
class LinkedList<Command>{
private:
    //node to traverse ist
    Command command_obj;
    LinkedList<Command>* next;
    static LinkedList<Command>* head = NULL;
    //function to create new node
    LinkedList<Command> *newNode(Command obj){
        //allocate new node
        LinkedList<Command>* new_node = new LinkedList<Command>();
        new_node->command_obj = data;
        new_node->next = NULL;
        return new_node;


    }
public:

    void insert(Command obj){

        LinkedList<Command> *new_node = newNode(obj);
        LinkedList<Command>* current;
        if(*head == NULL || (*head)->command_obj.getName() >= new_node.getName()){
            new_node->next = *head;
            *head = new_node;
        }else{
           current = *head;
           while(current->next != NULL && current->next->command_obj.getName() < new_node->command_obj.getName()){
               current = current->next;
           } 
           new_node->next = current->next;
           current->next = new_node;
        }
    }

    void printList(){
        LinkedList<Command> *temp = head;
        while(temp != NULL){
            Serial.println(temp->command_obj.getName());
            temp = temp->next;
        }
    }
};


