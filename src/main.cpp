#include <iostream>
#include "include/test.h"
#include "include/auth.h"
#include "include/user.h"
#include "include/admin.h"
#include "include/utils.h"

using namespace std;

int main() 
{
    int choice;
    cout << "Welcome to the Testing System!" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Admin menu" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    string currentLogin;

    switch (choice) 
    {
        case 1:
            registerUser();
            break;
        case 2:
        {
            if (loginUser()) 
            {
                cout << "You are now logged in." << endl;
                cout << "Enter your login again to proceed: ";
                cin >> currentLogin;

                User currentUser("Danil", "main street", "123456789", currentLogin, "user");
                
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
                            currentUser.testTake();
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
        }
        case 3:
        {
            cout << "Enter admin password: ";
            string admPass;
            cin >> admPass;
            Admin admin ("admin", encryptPass("admin"));
            if (admin.auth(admPass)) 
            {
                cout << "Ypu are now logged in as an admin." << endl;
                while (true)
                {
                    cout << "\nAdmin Menu: " << endl;
                    cout << "1. Manage tests" << endl;
                    cout << "2. View stats" << endl;
                    cout << "3. Manage users" << endl;
                    cout << "4. Logout" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice)
                    {
                        case 1:
                            admin.manageTests();
                            break;
                        case 2:
                            admin.viewStats();
                            break;
                        case 3:
                            admin.manageUsers();
                            break;
                        case 4:
                            cout << "Logging out..." << endl;
                            return 0;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                    }
                }
            }
            else
            {
                cout << "Invalid password. Access denied." << endl;
            }
            break;
        }
        case 4:
            cout << "Exiting the program. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
    return 0;
}