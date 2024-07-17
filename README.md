# ToDo List Maker

## Overview
ToDo List Maker is a simple C++ console application that allows users to manage their to-do list. The application supports adding, completing, and deleting to-do items, providing a clear and efficient way to keep track of tasks.

## Features
- **Add ToDo Items:** Users can add new tasks to their to-do list.
- **Complete ToDo Items:** Users can mark tasks as completed.
- **Delete ToDo Items:** Users can remove tasks from their to-do list.
- **User-friendly Interface:** Clear console interface with options to manage tasks.

## Getting Started

### Prerequisites
- A C++ compiler (e.g., GCC)
- Standard C++ library

### Installation
1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/todo-list-maker.git
    ```
2. Navigate to the project directory:
    ```sh
    cd todo-list-maker
    ```
3. Compile the project:
    ```sh
    g++ -o todolist main.cpp todolist.cpp
    ```

## Usage
Run the compiled program:
```sh
./todolist
```

### Main Menu Options
- **[A]dd ToDo Item:** Prompts the user to enter a new to-do item.
- **[C]omplete a ToDo Item:** Marks a specified to-do item as completed.
- **[D]elete a ToDo Item:** Deletes a specified to-do item.
- **[Q]uit program:** Exits the application.

## File Structure
```
├── main.cpp
├── todolist.h
└── todolist.cpp
```

## Code Explanation

### `main.cpp`
The main application logic, handling user input and displaying the to-do list.

### `todolist.h`
Header file defining the `ToDoItem` class.

```cpp
#ifndef TODOLIST_H
#define TODOLIST_H

#include <iostream>
#include <string>

using namespace std;

// Creating ToDoItem class
class ToDoItem {
    private:
        int id;
        string description;
        bool completed;

    public:
        ToDoItem(): id(0), description(""), completed(false) {}
        ~ToDoItem() = default;

        bool create(string new_description){
            // Generates a random integer between 1 and 100
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
```

### `todolist.cpp`
Implementation file for the `ToDoItem` class (if additional implementation is needed).

## License
This project is licensed under the MIT License.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Contact
Created by [Your Name] - feel free to contact me at [your-email@example.com]
