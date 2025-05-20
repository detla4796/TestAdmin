#include "include/user.h"
#include "include/utils.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

User::User(const string& name, const string& address, const string& phone, const string& login, const string& encrypted_pass)
    : name(name), address(address), phone(phone), login(login), encrypted_pass(encrypted_pass) {}

bool User::auth(const string& pass) const 
{
    return encrypted_pass == encryptPass(pass);
}

void User::viewResults() const 
{
    ifstream file("results.txt");
    if (!file.is_open()) 
    {
        cout << "Error: Unable to open results file." << endl;
        return;
    }

    string line;
    bool hasResults = false;

    cout << "\nYour Test Results:\n";
    while (getline(file, line)) 
    {
        stringstream ss(line);
        string username, category, testName, result, grade;
        getline(ss, username, ';');
        getline(ss, category, ';');
        getline(ss, testName, ';');
        getline(ss, result, ';');
        getline(ss, grade, ';');

        if (username == login) 
        {
            cout << "Category: " << category << endl;
            cout << "Test: " << testName << endl;
            cout << "Result: " << result << endl;
            cout << "Grade: " << grade << endl;
            cout << "--------------------------" << endl;
            hasResults = true;
        }
    }

    if (!hasResults) 
    {
        cout << "No results found for you." << endl;
    }

    file.close();
}

void User::testTake() const 
{

}