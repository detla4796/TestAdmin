#include "include/user.h"
#include "include/utils.h"

User::User(const string& name, const string& address, const string& phone, const string& login, const string& encrypted_pass)
    : name(name), address(address), phone(phone), login(login), encrypted_pass(encrypted_pass) {}

bool User::auth(const string& pass) const
{
    return encrypted_pass == encryptPass(pass);
}

void User::viewResults() const
{

}

void User::testTake() const
{

}