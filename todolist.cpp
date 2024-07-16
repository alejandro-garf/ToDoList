#include <iomanip>
#include <list>
#include <ctime>

#include "todolist.h"

using namespace std;

int main() {
    //Version of the program
    string version = "v0.2.0";

    //List of the ToDoItems and iterator it
    list<ToDoItem> todoItems;
    list<ToDoItem>::iterator it;

    //Clears the list
    todoItems.clear();

    //Seed for the random number generator
    srand(time(NULL));

    //Declare input option variable
    char input_option;

    //Declaring thr input string variable for option A
    string input_string;

    //Declaring the input id variable for option C
    int input_id;
    

    //Infinite loop
    while(1) 
    {
        system("cls"); // clears the system each loop 
        cout << "To Do List Maker - " << version << endl;
        cout << endl << endl;
    // begins at the start of the list and stops at the last item of the list
        for (it = todoItems.begin(); it != todoItems.end(); it++)
             {
                string completed = it->isCompleted() ? "Done" : "Not Done";
                std::cout << it->getId() << " | " << it->getDescription() << " | "
                << completed << endl << endl;
             }

    //Prompts user to add first to do list if it is empty
        if (todoItems.empty())
            {
                cout << "Enter your first to do item!!" << endl;
                cout << "=============================" << endl << endl;
            };

    // Menu Options for user to select from
        cout << "Options: " << endl;
        cout << "=============" << endl << endl;

        cout << "[A]dd ToDo Item" << endl << endl;
        cout << "[C]omplete a ToDo Item" << endl << endl;
        cout << "[D]elete a ToDo Item" << endl << endl;
        cout << "[Q]iut program" << endl << endl;

        cout << "==============" << endl;

    // Takes in the user input and ensures it is an uppercase
        cout << "Your Selection: ";
        cin >> input_option;
        input_option = toupper(input_option);

    // Quits program if q is chosen
        if (input_option == 'Q')
            {
                cout << "Have a productive day!" << endl;
                break;
            } 
            else if (input_option == 'C') // Changes "Not Done" to "Done"
            {
                cout << "Enter the ID of the item you want to mark as completed: ";
                cin >> input_id;
                for (it = todoItems.begin(); it != todoItems.end(); it++)
                {
                    if (input_id == it->getId())
                    {
                        it->setCompleted(true);
                        break;
                    }

                }

            } 
            else if (input_option == 'A') // Adds a new to do item
            {
                cout << "Enter the to do item that you would like to add: ";
                cin.clear();
                cin.ignore();
                getline(cin, input_string);

                ToDoItem newItem;
                newItem.create(input_string);
                todoItems.push_back(newItem);

            }
            else if (input_option == 'D') // Deletes a to do item
            {
                cout << "Enter the ID of the item that you would like to delete: ";
                cin >> input_id;

                for (it = todoItems.begin(); it != todoItems.end(); it++)
                {
                    if (input_id == it->getId())
                    {
                        todoItems.erase(it);
                        break;
                    }
                }
            }
            else // for if the user enters an invalid option
            {
                cout << "Invalid selection. Press enter to try again." << endl;
                cin.clear();
                cin.ignore();

                cin.get();
                continue;
            }

    }


    return 0;
};