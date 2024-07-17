# ToDo List Maker

## Overview
ToDo List Maker is a simple C++ console application that allows users to manage their to-do list. The application supports adding, completing, and deleting to-do items, providing a clear and efficient way to keep track of tasks. It also ensures the security of the to-do list by encrypting it with a passkey.

## Features
- **Add ToDo Items:** Users can add new tasks to their to-do list.
- **Complete ToDo Items:** Users can mark tasks as completed.
- **Delete ToDo Items:** Users can remove tasks from their to-do list.
- **Passkey Protection:** The to-do list is encrypted and decrypted with a user-provided passkey.
- **Persistent Storage:** The to-do list is saved to a file and encrypted for security.
- **User-friendly Interface:** Clear console interface with options to manage tasks.

## Getting Started

### Prerequisites
- A C++ compiler (e.g., GCC)
- OpenSSL library for encryption and decryption

### Installation
1. Clone the repository:
    ```sh
    git clone https://github.com/alejandro-garf/ToDoList.git
    ```
2. Navigate to the project directory:
    ```sh
    cd ToDoList
    ```
3. Compile the project:
    ```sh
    g++ -std=c++11 -o todo_app main.cpp -L/opt/homebrew/opt/openssl@3/lib -I/opt/homebrew/opt/openssl@3/include -lssl -lcrypto
    ```

## Usage
Run the compiled program:
```sh
./todo_app
```

### Main Menu Options
- **[A]dd ToDo Item:** Prompts the user to enter a new to-do item.
- **[C]omplete a ToDo Item:** Marks a specified to-do item as completed.
- **[D]elete a ToDo Item:** Deletes a specified to-do item.
- **[Q]uit program:** Exits the application.

## License
This project is licensed under the MIT License.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Contact
Created by alejandro-garf - feel free to contact me at gaelfon1738@gmail.com
