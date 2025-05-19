#include <iostream>
#include "include/test.h"

using namespace std;

int main()
{
    TestManager::loadTests("tests.txt");
    cout << "Tests successfully loaded from tests.txt" << endl;

    TestManager::showCategories();
    int categoryNum;
    cout << "Enter category number: ";
    cin >> categoryNum;
    
    vector<string> categories;
    for (const auto& [cat, _] : TestManager::tests) 
    {
        categories.push_back(cat);
    }
    
    if (categoryNum < 1 || categoryNum > categories.size()) 
    {
        cout << "Invalid category number!" << endl;
        return 1;
    }
    
    string category = categories[categoryNum - 1];
    
    TestManager::showTestsInCategory(category);
    int testNum;
    cout << "Enter test number: ";
    cin >> testNum;
    
    vector<string> tests;
    for (const auto& [name, _] : TestManager::tests[category]) 
    {
        tests.push_back(name);
    }
    
    if (testNum < 1 || testNum > tests.size()) 
    {
        cout << "Invalid test number!" << endl;
        return 1;
    }
    
    string testName = tests[testNum - 1];
    string username = "ivan";
    TestManager::runTest(category, testName, username);

    return 0;
}