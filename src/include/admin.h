#pragma once
#include <iostream>
#include <string>

using namespace std;

class Admin
{
    string login;
    string encrypted_pass;
    public:
    Admin(const string& login, const string& encrypted_pass);
    bool auth(const string& pass) const;
    void viewStats() const;
    void manageUsers() const;
    void manageTests() const;
};