#pragma once
#include <string>
#include <iostream>

using namespace std;

class User
{
    private:
    string name;
    string address;
    string phone;
    string login;
    string encrypted_pass;
    public:
    User(const string& name, const string& address, const string& phone, const string& login, const string& encrypted_pass);
    bool auth(const string& pass) const;
    void viewResults() const;
    void testTake() const;
};