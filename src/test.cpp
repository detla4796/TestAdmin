#include "include/test.h"

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
            cout << "Incorrect! The correct answer is: " << answers[i].first << endl;
        }
    }
}

void Test::displayResults() const
{
    cout << "Results for test: " << name << endl;
    for (size_t i = 0; i < questions.size(); i++)
    {
        cout << "Question " << i + 1 << ": " << questions[i] << endl;
        cout << "Your answer: " << answers[i].first << endl;
        cout << "Result: " << (answers[i].second ? "Correct" : "Incorrect") << endl;
    }
}

void Test::addQuestion(const string& question, const string& answer)
{
    questions.push_back(question);
    answers.emplace_back(answer, 0);
}