#include "include/utils.h"
#include <iostream>
#include <algorithm>

using namespace std;

string encryptPass(const string& pass)
{
    string enc = pass;
    reverse(enc.begin(), enc.end());
    return enc;
}