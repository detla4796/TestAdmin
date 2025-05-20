#include "include/auth.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "include/encryption.h"

using namespace std;

bool isLoginUnique(const string& login) 
{
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) 
    {
        stringstream ss(line);
        string storedLogin;
        getline(ss, storedLogin, ';');
        if (storedLogin == login) 
        {
            return false;
        }
    }
    return true;
}

void registerUser() 
{
    string name, address, phone, login, password;
    cout << "Enter your full name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter your address: ";
    getline(cin, address);
    cout << "Enter your phone number: ";
    getline(cin, phone);
    cout << "Enter a unique login: ";
    getline(cin, login);
    if (!isLoginUnique(login)) 
    {
        cout << "Error: Login already exists. Please try again." << endl;
        return;
    }
    cout << "Enter a password: ";
    getline(cin, password);
    string encryptedPassword = encrypt(password);
    ofstream file("users.txt", ios::app);
    file << login << ";" << encryptedPassword << ";" << name << ";" << address << ";" << phone << endl;
    file.close();
    cout << "Registration successful!" << endl;
}

bool loginUser() 
{
    string login, password;
    cout << "Enter your login: ";
    cin >> login;
    cout << "Enter your password: ";
    cin >> password;
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) 
    {
        stringstream ss(line);
        string storedLogin, storedEncryptedPassword;
        getline(ss, storedLogin, ';');
        getline(ss, storedEncryptedPassword, ';');
        if (storedLogin == login) 
        {
            string decryptedPassword = decrypt(storedEncryptedPassword);
            if (decryptedPassword == password) 
            {
                cout << "Login successful!" << endl;
                return true;
            } 
            else 
            {
                cout << "Error: Incorrect password." << endl;
                return false;
            }
        }
    }
    cout << "Error: User not found." << endl;
    return false;
}