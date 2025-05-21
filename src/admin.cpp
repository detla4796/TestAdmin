#include "include/admin.h"
#include "include/utils.h"
#include "include/test.h"
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>
#include <algorithm>



Admin::Admin(const string& login, const string& encrypted_pass)
    : login(login), encrypted_pass(encrypted_pass) {}

bool Admin::auth(const string& pass) const
{
    return encrypted_pass == encryptPass(pass);
}

void Admin::viewStats() const 
{
    ifstream file("results.txt");
    if (!file.is_open()) 
    {
        cout << "Error: Unable to open results file." << endl;
        return;
    }
    map<string, int> categoryStats;
    map<string, int> testStats;
    map<string, int> userStats;
    map<string, double> userAverageGrades;

    string line;
    while (getline(file, line)) 
    {
        stringstream ss(line);
        string username, category, testName, result, gradeStr;
        getline(ss, username, ';');
        getline(ss, category, ';');
        getline(ss, testName, ';');
        getline(ss, result, ';');
        getline(ss, gradeStr, ';');

        int grade = stoi(gradeStr);
        categoryStats[category]++;
        testStats[testName]++;
        userStats[username]++;
        userAverageGrades[username] += grade;
    }

    file.close();
    cout << "\nStatistics:\n";
    cout << "Category Statistics:\n";
    for (const auto& [category, count] : categoryStats) 
    {
        cout << "- " << category << ": " << count << " tests taken" << endl;
    }
    cout << "\nTest Statistics:\n";
    for (const auto& [testName, count] : testStats) 
    {
        cout << "- " << testName << ": " << count << " times taken" << endl;
    }
    cout << "\nUser Statistics:\n";
    for (const auto& [username, count] : userStats) 
    {
        double averageGrade = userAverageGrades[username] / count;
        cout << "- " << username << ": " << count << " tests taken, average grade: " << fixed << setprecision(2) << averageGrade << endl;
    }
}

void Admin::manageUsers() const 
{
    int choice;
    while (true) 
    {
        cout << "\nUser Management Menu:" << endl;
        cout << "1. Add User" << endl;
        cout << "2. Delete User" << endl;
        cout << "3. Modify User" << endl;
        cout << "4. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1: 
            {
                string name, address, phone, login, password;
                cout << "Enter full name: ";
                cin.ignore();
                getline(cin, name);

                cout << "Enter address: ";
                getline(cin, address);

                cout << "Enter phone number: ";
                getline(cin, phone);

                cout << "Enter unique login: ";
                getline(cin, login);
                ifstream file("users.txt");
                string line;
                bool isUnique = true;
                while (getline(file, line)) 
                {
                    stringstream ss(line);
                    string storedLogin;
                    getline(ss, storedLogin, ';');
                    if (storedLogin == login) 
                    {
                        isUnique = false;
                        break;
                    }
                }
                file.close();
                if (!isUnique) 
                {
                    cout << "Error: Login already exists." << endl;
                    break;
                }
                cout << "Enter password: ";
                getline(cin, password);
                string encryptedPassword = encryptPass(password);
                ofstream outFile("users.txt", ios::app);
                outFile << login << ";" << encryptedPassword << ";" << name << ";" << address << ";" << phone << endl;
                outFile.close();
                cout << "User added successfully!" << endl;
                break;
            }
            case 2: 
            {
                string login;
                cout << "Enter the login of the user to delete: ";
                cin >> login;

                ifstream inFile("users.txt");
                ofstream tempFile("temp_users.txt");

                bool found = false;
                string line;
                while (getline(inFile, line)) 
                {
                    stringstream ss(line);
                    string storedLogin;
                    getline(ss, storedLogin, ';');

                    if (storedLogin != login) 
                    {
                        tempFile << line << endl;
                    } 
                    else 
                    {
                        found = true;
                    }
                }

                inFile.close();
                tempFile.close();

                remove("users.txt");
                rename("temp_users.txt", "users.txt");

                if (found) 
                {
                    cout << "User deleted successfully!" << endl;
                } 
                else 
                {
                    cout << "Error: User not found." << endl;
                }
                break;
            }
            case 3: 
            {
                string login;
                cout << "Enter the login of the user to modify: ";
                cin >> login;
                ifstream inFile("users.txt");
                ofstream tempFile("temp_users.txt");
                bool found = false;
                string line;
                while (getline(inFile, line)) 
                {
                    stringstream ss(line);
                    string storedLogin, encryptedPassword, name, address, phone;
                    getline(ss, storedLogin, ';');
                    getline(ss, encryptedPassword, ';');
                    getline(ss, name, ';');
                    getline(ss, address, ';');
                    getline(ss, phone, ';');
                    if (storedLogin == login) 
                    {
                        found = true;
                        cout << "Enter new password: ";
                        string newPassword;
                        cin >> newPassword;
                        encryptedPassword = encryptPass(newPassword);
                        cout << "User modified successfully!" << endl;
                    }
                    tempFile << storedLogin << ";" << encryptedPassword << ";" << name << ";" << address << ";" << phone << endl;
                }
                inFile.close();
                tempFile.close();
                remove("users.txt");
                rename("temp_users.txt", "users.txt");
                if (!found) 
                {
                    cout << "Error: User not found." << endl;
                }
                break;
            }
            case 4:
                cout << "Returning to main menu..." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void Admin::manageTests() const 
{
    int choice;
    while (true) 
    {
        cout << "\nTest Management Menu:" << endl;
        cout << "1. Add Category" << endl;
        cout << "2. Add Test to Category" << endl;
        cout << "3. Add Question to Test" << endl;
        cout << "4. Export Tests to File" << endl;
        cout << "5. Import Tests from File" << endl;
        cout << "6. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1: 
            {
                cout << "This method is not implemented yet." << endl;
                break;
            }
            case 2: 
            {
                cout << "This method is not implemented yet." << endl;
                break;
            }
            case 3: 
            {
                cout << "This method is not implemented yet." << endl;
                break;
            }
            case 4: 
            {
                ofstream file("exported_tests.txt");
                cout << "This method is not implemented yet." << endl;
                break;
            }
            case 5: 
            {
                TestManager::loadTests("imported_tests.txt");
                cout << "This method is not implemented yet." << endl;
                break;
            }
            case 6:
                cout << "Returning to main menu..." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}