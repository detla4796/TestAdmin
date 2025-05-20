#include <iostream>
#include "include/test.h"
#include "include/auth.h"
#include "include/user.h"

using namespace std;

int main() 
{
    int choice;
    cout << "Welcome to the Testing System!" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    string currentLogin;

    switch (choice) 
    {
        case 1:
            registerUser();
            break;
        case 2:
            if (loginUser()) 
            {
                cout << "You are now logged in." << endl;
                cout << "Enter your login again to proceed: ";
                cin >> currentLogin;

                User currentUser("John Doe", "123 Main St", "555-1234", currentLogin, "encrypted_password");
                
                while (true) 
                {
                    cout << "\nWhat would you like to do?" << endl;
                    cout << "1. View Test Results" << endl;
                    cout << "2. Take a Test" << endl;
                    cout << "3. Logout" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice) 
                    {
                        case 1:
                            currentUser.viewResults();
                            break;
                        case 2:
                            // currentUser.testTake();
                            cout << "This feature is not implemented yet." << endl;
                            break;
                        case 3:
                            cout << "Logging out..." << endl;
                            return 0;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                    }
                }
            }
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }

    return 0;
}