#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Test 
{
private:
    string name;
    vector<string> questions;
    vector<pair<string, int>> answers;
    int questionIndex;

public:
    Test() : name(""), questions(), answers(), questionIndex(0) {} 
    Test(const string& name, const vector<string>& questions, const vector<pair<string, int>>& answers);
    void startTest();
    void displayResults() const;
    void addQuestion(const string& question, const string& answer);
    vector<string> getQuestions() const;
    vector<pair<string, int>> getAnswers() const;
    void saveProgress(const string& username) const;
    bool loadProgress(const string& username);
};
namespace TestManager 
{
    void loadTests(const string& filename);
    void showCategories();
    void showTestsInCategory(const string& category);
    void runTest(const string& category, const string& testName, const string& username);
    void showUserResults(const string& username);


    extern map<string, map<string, Test>> tests;
}
