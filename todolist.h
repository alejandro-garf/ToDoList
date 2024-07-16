#ifndef TODOLIST_H
#define TODOLIST_H

#include <iostream>
#include <string>

using namespace std;

//Creating ToDoItem class
class ToDoItem {
    private:
        int id;
        string description;
        bool completed;

    public:
        ToDoItem(): id(0), description(""), completed(false) {}
        ~ToDoItem() = default;

        bool create(string new_description){
            //Generates a random integer between 1 and 100
            id = rand() % 100 + 1;
            description = new_description;
            return true;
        }

        int getId() {return id; }
        string getDescription() {return description; }
        bool isCompleted() {return completed; }

        bool setCompleted(bool val) { completed = val; return completed; }

};

#endif // TODOLIST_H