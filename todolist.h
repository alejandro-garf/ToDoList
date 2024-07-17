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

        bool create(string new_description)
            {
                //Generates a random integer between 1 and 100
                id = rand() % 100 + 1;
                description = new_description;
                return true;
            }

        int getId() { return id; }
        string getDescription() {return description; }
        bool isCompleted() {return completed; }

        void setCompleted(bool val) { completed = val; }

        friend ostream& operator<<(ostream& os, const ToDoItem& item) 
            {
                os << item.id << "\n " << item.description << "\n " << item.completed << "\n";
                return os;
            }
        
        friend istream& operator>>(istream& is, ToDoItem& item)
            {
                is >> item.id;
                is.ignore();
                getline(is, item.description);
                is >> item.completed;
                is.ignore();
                return is;
            }
};

#endif // TODOLIST_H