#include "include/test.h"
#include <fstream>
#include <sstream>

Test::Test(const string& name, const vector<string>& questions, const vector<pair<string, int>>& answers)
    : name(name), questions(questions), answers(answers) {}

void Test::startTest() 
{
    cout << "Starting test: " << name << endl;
    for (size_t i = 0; i < questions.size(); i++) 
    {
        cout << "Question " << i + 1 << ": " << questions[i] << endl;
        cout << "Your answer: ";
        string userAnsw;
        cin >> userAnsw;
        if (userAnsw == answers[i].first) 
        {
            answers[i].second = 1;
            cout << "Correct!" << endl;
        } 
        else 
        {
            answers[i].second = 0;
            cout << "Incorrect! Correct answer: " << answers[i].first << endl;
        }
    }
}

void Test::displayResults() const 
{
    cout << "Results for test: " << name << endl;
    int correct = 0;
    for (size_t i = 0; i < questions.size(); i++) 
    {
        cout << "Question " << i + 1 << ": " << questions[i] << endl;
        cout << "Your answer: " << answers[i].first << endl;
        cout << "Result: " << (answers[i].second ? "Correct" : "Incorrect") << endl;
        if (answers[i].second) correct++;
    }
    double percent = (double)correct / questions.size() * 100.0;
    int grade = percent >= 90 ? 5 : percent >= 75 ? 4 : percent >= 60 ? 3 : 2;
    cout << "Score: " << correct << "/" << questions.size() << " (" << percent << "%) - Grade: " << grade << endl;
}

void Test::addQuestion(const string& question, const string& answer) 
{
    questions.push_back(question);
    answers.emplace_back(answer, 0);
}

vector<string> Test::getQuestions() const 
{
    return questions;
}

vector<pair<string, int>> Test::getAnswers() const 
{
    return answers;
}

map<string, map<string, Test>> TestManager::tests;

void TestManager::loadTests(const string& filename) 
{
    ifstream file(filename);
    string line;
    while (getline(file, line)) 
    {
        stringstream ss(line);
        string category, testName, question, correctAnswer;
        getline(ss, category, ';');
        getline(ss, testName, ';');
        getline(ss, question, ';');
        getline(ss, correctAnswer, ';');

        if (tests[category].count(testName) == 0)
        {
            tests[category][testName] = Test(testName, {}, {});
        }
        tests[category][testName].addQuestion(question, correctAnswer);
    }
}

void TestManager::showCategories() 
{
    cout << "\nTest Categories:\n";
    vector<string> categories;
    for (const auto& [cat, _] : tests)
    {
        categories.push_back(cat);
    }
    for (size_t i = 0; i < categories.size(); i++) 
    {
        cout << (i + 1) << ") " << categories[i] << endl;
    }
}

void TestManager::showTestsInCategory(const string& category) 
{
    auto it = tests.find(category);
    if (it != tests.end()) 
    {
        cout << "\nTests in category '" << category << "':\n";
        int i = 1;
        for (const auto& [name, _] : it->second)
        {
            cout << i++ << ") " << name << endl;
        }
    } 
    else 
    {
        cout << "Category not found." << endl;
    }
}

void TestManager::runTest(const string& category, const string& testName, const string& username) 
{
    if (tests.count(category) && tests[category].count(testName)) 
    {
        Test& t = tests[category][testName];
        t.startTest();
        t.displayResults();

        int correct = 0;
        for (auto& [_, isCorrect] : t.getAnswers()) 
        {
            if (isCorrect) correct++;
        }
        int total = t.getQuestions().size();
        double percent = (double)correct / total * 100.0;
        int grade = percent >= 90 ? 5 : percent >= 75 ? 4 : percent >= 60 ? 3 : 2;

        ofstream log("results.txt", ios::app);
        log << username << ";" << category << ";" << testName << ";" << correct << "/" << total << ";" << grade << endl;
    }    
    else 
    {
        cout << "Test not found." << endl;
    }
}

