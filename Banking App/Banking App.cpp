// Banking App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>       // std::cout, std::endl
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <string>
#include <iomanip>

using std::cout; using std::cin;

const int delay = 1;

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
double g_history[3][10]; //the first set of brakets represent the account number, the sencond set of brakets stores an array of the last 10 transactions.

enum class Menus { mainMenu, login, createAcc, passwordReset, accOverview, history }; //enum stores all the different menus. Allows for easy switching between menus.


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
int findEmptyAcc() 
{
    for (int i = 0; i < 3; i++) {
        if (g_accUsernames[i].empty()) {
            return i;
        }
    }
    return -1;
}
void logTransaction(bool type, double amount) // type signifies whether is a deposit or withdraw.
{
    if (type == 1) {
        for (int i = 9; i > 0; i--) {
            g_history[g_accNum][i] = g_history[g_accNum][i - 1];
            g_history[g_accNum][0] = 0 - amount;
        }
    }
    else if (type == 0) {
        for (int i = 9; i > 0; i--) {
            g_history[g_accNum][i] = g_history[g_accNum][i - 1];
            g_history[g_accNum][0] = 0 - amount;
        }
    }
}

void displayUI(Menus menu) //Displays different menu-screens based on the selected menu.
{
    switch (menu) {
        case Menus::mainMenu: 
            system("cls"); //Use system{"clear") for linux
            g_username.clear();
            g_password.clear();
            g_accNum = -1;

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
            cout << "Logged in to " << "\033[1;35m" << g_accUsernames[g_accNum] << "\033[0m\n";
            cout << "Current balance: ";
            cout << std::setprecision(2) << std::fixed << g_balance[g_accNum] << "\n";

            cout << "\n[1]Deposit\n";
            cout << "[2]Withdraw\n";
            cout << "[3]History\n";

            cout << "\n[4]Return to main screen\n";
            break;
    }
}

Menus processInput(Menus menu, int selection) //Takes two args, currently selected menu and the user input, then it processes what the user selected based on the current menu and switches to the next screen.
{
    double amount;
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
                case 2:
                    cout << "Enter your password\n";
                    getline(cin, g_password);
                    return Menus::login;
                case 3:
                    if (!g_username.empty() && !g_password.empty()) {
                        if (findAcc(g_username) && g_password == g_accPasswords[g_accNum]) {
                            cout << "\033[1;32mLogin successful\033[0m\n";
                            std::this_thread::sleep_for(std::chrono::seconds(delay));
                            return Menus::accOverview;
                        }
                        else {
                            cout << "\033[1;31mUsername or password incorrect\033[0m\n";
                            std::this_thread::sleep_for(std::chrono::seconds(delay));
                            g_username.clear();
                            g_password.clear();
                            return Menus::login;
                        }
                    }
                    else {
                        cout << "\033[1;31mInput cannot be blank\033[0m\n";
                        std::this_thread::sleep_for(std::chrono::seconds(delay));
                        return Menus::login;
                    }   
                case 4:
                    return Menus::mainMenu;
                default:
                    cout << "\033[1;31mChoose only from selection\033[0m\n";
                    std::this_thread::sleep_for(std::chrono::seconds(delay));
                    return Menus::login;
            }
            break;
        case Menus::createAcc:
            switch (selection) {
                case 1:
                    cout << "Enter a username\n";
                    getline(cin, g_username);
                    return Menus::createAcc;
                case 2:
                    cout << "Enter a password\n";
                    getline(cin, g_password);
                    return Menus::createAcc;
                case 3:
                    if (!g_password.empty() && !g_username.empty()) {
                        if (!findAcc(g_username)) {
                            int emptySpace = findEmptyAcc();
                            if (emptySpace == -1) {
                                cout << "\033[1;31mStorage full\033[0m\n";
                                std::this_thread::sleep_for(std::chrono::seconds(delay));
                                g_username.clear();
                                g_password.clear();
                                return Menus::mainMenu;
                            }
                            g_accUsernames[emptySpace] = g_username;
                            g_accPasswords[emptySpace] = g_password;
                            cout << "\033[1;32mAccount Created\033[0m\n";
                            std::this_thread::sleep_for(std::chrono::seconds(delay));
                            return Menus::mainMenu;
                        }
                        else {
                            cout << "\033[1;31mUsername already exist\033[0m\n";
                            std::this_thread::sleep_for(std::chrono::seconds(delay));
                            g_username.clear();
                            g_password.clear();
                            return Menus::createAcc;
                        }
                    }
                    else {
                        cout << "\033[1;31mInput cannot be blank\033[0m\n";
                        std::this_thread::sleep_for(std::chrono::seconds(delay));
                        return Menus::createAcc;
                    }
                case 4:
                    return Menus::mainMenu;
                default:
                    cout << "\033[1;31mChoose only from selection\033[0m\n";
                    std::this_thread::sleep_for(std::chrono::seconds(delay));
                    return Menus::createAcc;
            }
            break;
        case Menus::passwordReset:
            //WIP
            break;
        case Menus::accOverview:
            switch (selection) {
                case 1:
                    cout << "Enter amount: ";
                    amount = getDouInput();
                    if (amount != -1) {
                        g_balance[g_accNum] = g_balance[g_accNum] + amount;

                        logTransaction(1, amount);

                        cout << "\033[1;32mAmmount added to balance\033[0m\n";
                        std::this_thread::sleep_for(std::chrono::seconds(delay));
                        return Menus::accOverview;
                    }
                    else {
                        cout << "\033[1;31mEnter a number\033[0m\n";
                        std::this_thread::sleep_for(std::chrono::seconds(delay));
                        return Menus::accOverview;
                    }
                    
                case 2:
                    cout << "Enter amount: ";
                    amount = getDouInput();
                    if (amount != -1) {
                        if (amount < g_balance[g_accNum]) {
                            g_balance[g_accNum] = g_balance[g_accNum] - amount;

                            logTransaction(0, amount);

                            cout << "\033[1;32mAmmount subtracted to balance\033[0m\n";
                            std::this_thread::sleep_for(std::chrono::seconds(delay));
                            return Menus::accOverview;
                        }  
                        else {
                            cout << "\033[1;31mNot enough money to withdraw\033[0m\n";
                            std::this_thread::sleep_for(std::chrono::seconds(delay));
                            return Menus::accOverview;
                        }
                    }
                    else {
                        cout << "\033[1;31mEnter a number\033[0m\n";
                        std::this_thread::sleep_for(std::chrono::seconds(delay));
                        return Menus::accOverview;
                    }
                case 3:
                    return Menus::history;
                case 4:
                    return Menus::mainMenu;
                default:
                    cout << "\033[1;31mChoose only from selection\033[0m\n";
                    std::this_thread::sleep_for(std::chrono::seconds(delay));
                    return Menus::mainMenu;
            }
            break;
               
    }
    return Menus::mainMenu;
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
