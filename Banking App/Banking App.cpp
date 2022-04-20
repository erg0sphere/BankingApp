// Banking App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>       // std::cout, std::endl
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <string>

using std::cout; using std::cin;

const int delay = 2;

int getIntInput()                                      //Gets input from the console and converts it from a string into a interger.
{
    std::string input;
    std::size_t sizeOfStoi;                            //This stores how many characters have been converted to int.
    
    getline(std::cin, input);
    try {
        int inputAsInt = stoi(input, &sizeOfStoi); //The second argument takes the number of characters that can be coverted to int and store it in sizeOfStoi.
        if (sizeOfStoi != input.size()) {          //If the input was something like "123abc", stoi would only convert "123" to int while ignoring "abc". This is why this if statement is required.
            throw "error";                         //If the sizeOfstoi does not equal the total size of the input, it means that not all of the string input could be converted to a interger, thus an error is thrown.
        }
        return inputAsInt; 
    }
    catch (...) {
        return -1;
    }   
}
double getDouInput()                                   //same as getIntInput(), but instead it converts to doubles. Same algorithm with the exception of stod() instead of stoi()
{
    std::string input;
    std::size_t sizeOfStod;
   
    getline(std::cin, input);
    try {
        double inputAsDou = stod(input, &sizeOfStod);
        if (sizeOfStod != input.size()) {
            throw "error";
        }
        return inputAsDou;
    }
    catch (...) {
        return -1;
    }
}

std::string g_username;
std::string g_password;

int g_accNum; //0-3
std::string g_accUsernames[3];
std::string g_accPasswords[3];
double g_balance[3];
double g_history[3][10];

enum class Menus { mainMenu, login, createAcc, passwordReset, accOverview }; //enum stores all the different menus. Allows for easy switching between menus.


bool findAcc(std::string username)
{
    for (int i = 0; i < 3; i++) {
        if (username == g_accUsernames[i]) {
            g_accNum = i;
            return true;
        }
    }
    return false;
}

void displayUI(Menus menu) //Displays different menu-screens based on the selected menu.
{
    switch (menu) {
        case Menus::mainMenu: 
            system("cls"); //Use system{"clear") for linux
            g_username.clear();
            g_password.clear();

            cout << "[1]Login\n";
            cout << "[2]Create Account\n";
            cout << "[3]Reset Password\n";

            cout << "\nWaiting for input...\n";
            break;
        case Menus::login:
            system("cls"); 

            cout << "[1]Enter Username: " + g_username + "\n";
            cout << "[2]Enter Password: " + g_password + "\n";
            cout << "\033[1;34m[3]Log in\033[0m\n";

            cout << "\n[4]Return to main screen\n";
            break;
        case Menus::createAcc:
            system("cls");

            cout << "[1]Enter Username: " + g_username + "\n";
            cout << "[2]Enter Password: " + g_password + "\n";
            cout << "\033[1;34m[3]Create account\033[0m\n";

            cout << "\n[4]Return to main screen\n";
            break;
        case Menus::passwordReset:
            cout << "wIP\n";
            break;
        case Menus::accOverview:
            system("cls");

            cout << "Current balance: " << g_balance[g_accNum] << "\n";

            cout << "[1]Deposit\n";
            cout << "[2]Withdraw\n";

            cout << "\n[3]Return to main screen\n";
            break;

    }
}

Menus processInput(Menus menu, int selection) //Takes two args, currently selected menu and the user input, then it processes the what the user selected and switches to the next screen.
{
    switch (menu) {
        case Menus::mainMenu:
            switch (selection) {
                case 1:
                    return Menus::login; //For example, if the user selected 1, it will return the login menu so the in the next iteration login will be displayed instead of mainMenu.              
                case 2:
                    return Menus::createAcc;                 
                case 3:
                    return Menus::passwordReset;
                default:
                    cout << "\033[1;31mChoose only from selection\033[0m\n";
                    std::this_thread::sleep_for(std::chrono::seconds(delay));
                    return Menus::mainMenu;
            }
            break;
        case Menus::login: //login screen
            switch (selection) {
                case 1:
                    cout << "Enter your username\n";
                    getline(cin, g_username);
                    return Menus::login;
                    break;
                case 2:
                    cout << "Enter your password\n";
                    getline(cin, g_password);
                    return Menus::login;
                case 3:
                    if (findAcc(g_username)) {
                        return Menus::accOverview;
                    }
                    else {
                        cout << "\033[1;31mUsername does not exist\033[0m\n";
                        std::this_thread::sleep_for(std::chrono::seconds(delay));
                        g_username.clear();
                        g_password.clear();
                        return Menus::login;
                    }
                default:
                    cout << "\033[1;31mChoose only from selection\033[0m\n";
                    std::this_thread::sleep_for(std::chrono::seconds(delay));
                    return Menus::login;
            }
            break;
        case Menus::passwordReset:
            //WIP
            break;
        case Menus::accOverview:
            switch (selection) {
                case 1:
                    //
                    return Menus::accOverview;    
                case 2:
                    return Menus::accOverview;
                case 3:
                    return Menus::mainMenu;
                default:
                    cout << "\033[1;31mChoose only from selection\033[0m\n";
                    std::this_thread::sleep_for(std::chrono::seconds(delay));
                    return Menus::mainMenu;
            }
            break;
    }
}

int main()
{
    //int currentMenu = 0;
    Menus displayMenu;
    displayMenu = Menus::mainMenu;
  
 
    while (1) {
        displayUI(displayMenu);
        int userInput = getIntInput();
        if (userInput != -1) {    
            displayMenu = processInput(displayMenu, userInput);
        }
        else {
            cout << "\033[1;31mEnter only interger\033[0m\n";
            std::this_thread::sleep_for(std::chrono::seconds(delay));
        }
        
        
    }    
}
