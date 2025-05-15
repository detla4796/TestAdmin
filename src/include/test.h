#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Test
{
    private:
    string name;
    vector<string> questions;
    vector<pair<string, int>> answers;
    public:
    Test(const string& name, const vector<string>& questions, const vector<pair<string,int>>& answers);
    void startTest();
    void displayResults() const;
    void addQuestion(const string& question, const string& answer);
};