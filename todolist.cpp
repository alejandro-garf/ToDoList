#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <openssl/evp.h>
#include "todolist.h"
#include "encryption.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <cstdio>
#endif

using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

string hashPasskey(const string& passkey) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;
    
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    if(context != nullptr) {
        if(EVP_DigestInit_ex(context, EVP_sha256(), nullptr)) {
            if(EVP_DigestUpdate(context, passkey.c_str(), passkey.size())) {
                if(EVP_DigestFinal_ex(context, hash, &lengthOfHash)) {
                    EVP_MD_CTX_free(context);
                    
                    stringstream ss;
                    for(unsigned int i = 0; i < lengthOfHash; ++i) {
                        ss << hex << setw(2) << setfill('0') << (int)hash[i];
                    }
                    return ss.str();
                }
            }
        }
        EVP_MD_CTX_free(context);
    }
    
    return "";
}

void deleteFile(const string& filename) {
    if (remove(filename.c_str()) != 0) {
        perror("Error deleting file");
    } else {
        cout << "File successfully deleted." << endl;
    }
}

int main() {
    // Version of the program
    string version = "v0.2.0";

    // List of the ToDoItems and iterator it
    list<ToDoItem> todoItems;
    list<ToDoItem>::iterator it;

    // Seed for the random number generator
    srand(time(NULL));

    // Declare input option variable
    char input_option;

    // Declaring the input string variable for option A
    string input_string;

    // Declaring the input id variable for option C
    int input_id;

    // User's passkey
    string passkey;

    cout << "Thanks for using Garftech's To-Do List Program!" << endl;
    cout << "==========================" << endl;
    cout << "PLEASE WRITE DOWN YOUR PASSKEY" << endl;
    cout << "Your data will be lost if you forget it!" << endl;
    cout << "==========================" << endl;

    // Check if the file exists
    ifstream infile("todolist.dat", ios::binary);
    bool fileExists = infile.good();

    // If the file doesn't exist, prompt for the initial passkey and create the file
    if (!fileExists) {
        cout << "No existing data found. Please set your initial passkey: ";
        cin >> passkey;

        // Hash the passkey
        string hashedPasskey = hashPasskey(passkey);

        // Create the file and store the hashed passkey
        ofstream outfile("todolist.dat", ios::binary);
        if (outfile) {
            outfile << hashedPasskey << endl;
            outfile.close();
        }
    } else {
        // Allow up to 3 attempts to enter the correct passkey
        int attempts = 0;
        const int maxAttempts = 3;
        while (attempts < maxAttempts) {
            cout << "Please enter your passkey: ";
            cin >> passkey;

            // Hash the passkey
            string hashedPasskey = hashPasskey(passkey);

            // Read the stored hashed passkey
            string storedHash;
            getline(infile, storedHash);

            if (storedHash != hashedPasskey) {
                attempts++;
                cerr << "Invalid passkey. " << (maxAttempts - attempts) << " attempts remaining." << endl;
                if (attempts >= maxAttempts) {
                    cerr << "Maximum attempts reached. Deleting file and exiting." << endl;
                    infile.close();
                    deleteFile("todolist.dat");
                    return 1;
                }
                infile.clear(); // Clear the error state
                infile.seekg(0, ios::beg); // Rewind the file to read the hash again
            } else {
                break;
            }
        }

        // Read and decrypt the existing to-do list from file
        stringstream buffer;
        buffer << infile.rdbuf();
        string encrypted_data = buffer.str();
        string decrypted_data = decrypt(encrypted_data, passkey);
        stringstream data_stream(decrypted_data);

        while (data_stream.good()) {
            ToDoItem item;
            data_stream >> item;
            if (data_stream.good()) {
                todoItems.push_back(item);
            }
        }
        infile.close();
    }

    // Infinite loop
    while (1) {
        clearScreen(); // clears the system each loop
        cout << "To Do List Maker - " << version << endl;
        cout << endl;

        // Display to-do list items
        for (it = todoItems.begin(); it != todoItems.end(); it++) {
            string completed = it->isCompleted() ? "Done" : "Not Done";
            cout << setw(4) << it->getId() << " | " << setw(10) << it->getDescription() << " | " << completed << endl;
        }

        cout << endl;

        // Prompts user to add first to-do list if it is empty
        if (todoItems.empty()) {
            cout << "Enter your first to-do item!!" << endl;
            cout << "=============================" << endl << endl;
        }

        // Menu Options for user to select from
        cout << "Options:" << endl;
        cout << "[A]dd ToDo Item" << endl;
        cout << "[C]omplete a ToDo Item" << endl;
        cout << "[D]elete a ToDo Item" << endl;
        cout << "[Q]uit program" << endl;
        cout << "Your Selection: ";
        cin >> input_option;
        input_option = toupper(input_option);

        // Quits program if Q is chosen
        if (input_option == 'Q') {
            cout << "Have a productive day!" << endl;
            break;
        } else if (input_option == 'C') { // Changes "Not Done" to "Done"
            cout << "Enter the ID of the item you want to mark as completed: ";
            cin >> input_id;
            for (it = todoItems.begin(); it != todoItems.end(); it++) {
                if (input_id == it->getId()) {
                    it->setCompleted(true);
                    break;
                }
            }
        } else if (input_option == 'A') { // Adds a new to-do item
            cout << "Enter the to-do item that you would like to add: ";
            cin.clear();
            cin.ignore();
            getline(cin, input_string);

            ToDoItem newItem;
            newItem.create(input_string);
            todoItems.push_back(newItem);
        } else if (input_option == 'D') { // Deletes a to-do item
            cout << "Enter the ID of the item that you would like to delete: ";
            cin >> input_id;

            for (it = todoItems.begin(); it != todoItems.end(); it++) {
                if (input_id == it->getId()) {
                    todoItems.erase(it);
                    break;
                }
            }
        } else { // for if the user enters an invalid option
            cout << "Invalid selection. Press enter to try again." << endl;
            cin.clear();
            cin.ignore();
            cin.get();
            continue;
        }

        // Save and encrypt the to-do list to file
        ofstream outfile("todolist.dat", ios::binary);
        if (outfile) {
            outfile << hashPasskey(passkey) << endl;
            stringstream data_stream;
            for (it = todoItems.begin(); it != todoItems.end(); it++) {
                data_stream << *it;
            }
            string data = data_stream.str();
            string encrypted_data = encrypt(data, passkey);
            outfile << encrypted_data;
            outfile.close();
        }
    }

    return 0;
}
