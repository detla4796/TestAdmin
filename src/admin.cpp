#include "include/admin.h"
#include "include/utils.h"


Admin::Admin(const string& login, const string& encrypted_pass)
    : login(login), encrypted_pass(encrypted_pass) {}

bool Admin::auth(const string& pass) const
{
    return encrypted_pass == encryptPass(pass);
}

void Admin::viewStats() const
{

}

void Admin::manageUsers() const
{

}

void Admin::manageTests() const
{
    
}