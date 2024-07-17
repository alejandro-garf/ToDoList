#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

using namespace std;

// Encrypts the data using XOR encryption
string encrypt(const string& data, const string& passkey)
    {
        //Copy of the input data which is then stored in string
        string encrypted = data;
        for (size_t i = 0; i < data.size(); ++i) //iterate over each chacter in the string
            {
                encrypted[i] = data[i] ^ passkey[i % passkey.size()]; // XORs the data character with the passkey character
            }
            return encrypted; //returns encrypted string
    }

// Decrypts the string using the same XOR encryption with the passkey
    string decrypt(const string& data, const string& passkey)
        {
            return encrypt(data, passkey); //reuse the encryption function
            //XOR encryption is symmetric
        }

    #endif // ENCRYPTION_H