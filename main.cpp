#include <iostream>
#include "ATM.h"

void showMenu(bool loggedIn) {
    std::cout << "\n--- ATM Menu ---\n";
    if (!loggedIn) {
        std::cout << "1. Create User (Set PIN)\n";
        std::cout << "2. Login\n";
        std::cout << "0. Exit\n";
    } else {
        std::cout << "1. Deposit\n";
        std::cout << "2. Withdraw\n";
        std::cout << "3. Check Balance\n";
        std::cout << "4. Change PIN\n";
        std::cout << "5. Delete User\n";
        std::cout << "6. Logout\n";
        std::cout << "0. Exit\n";
    }
}

int main() {
    ATM atm;
    bool running = true;
    while (running) {
        showMenu(atm.isLoggedIn());
        std::cout << "Select option: ";
        int choice;
        std::cin >> choice;
        if (!atm.isLoggedIn()) {
            switch (choice) {
                case 1: {
                    std::string pin;
                    std::cout << "Set new PIN: ";
                    std::cin >> pin;
                    if (atm.createUser(pin))
                        std::cout << "User created.\n";
                    else
                        std::cout << "PIN already exists.\n";
                    break;
                }
                case 2: {
                    std::string pin;
                    std::cout << "Enter PIN: ";
                    std::cin >> pin;
                    if (atm.login(pin))
                        std::cout << "Login successful.\n";
                    else
                        std::cout << "Invalid PIN.\n";
                    break;
                }
                case 0:
                    running = false;
                    break;
                default:
                    std::cout << "Invalid option.\n";
            }
        } else {
            switch (choice) {
                case 1: {
                    double amount;
                    std::cout << "Enter deposit amount: ";
                    std::cin >> amount;
                    if (atm.deposit(amount))
                        std::cout << "Deposited successfully.\n";
                    else
                        std::cout << "Deposit failed.\n";
                    break;
                }
                case 2: {
                    double amount;
                    std::cout << "Enter withdrawal amount: ";
                    std::cin >> amount;
                    if (atm.withdraw(amount))
                        std::cout << "Withdrawal successful.\n";
                    else
                        std::cout << "Insufficient balance or error.\n";
                    break;
                }
                case 3:
                    std::cout << "Current balance: " << atm.getBalance() << "\n";
                    break;
                case 4: {
                    std::string oldPin, newPin;
                    std::cout << "Enter current PIN: ";
                    std::cin >> oldPin;
                    std::cout << "Enter new PIN: ";
                    std::cin >> newPin;
                    if (atm.changePin(oldPin, newPin))
                        std::cout << "PIN changed successfully.\n";
                    else
                        std::cout << "PIN change failed.\n";
                    break;
                }
                case 5: {
                    std::string pin;
                    std::cout << "Enter your PIN to confirm delete: ";
                    std::cin >> pin;
                    if (atm.deleteUser(pin)) {
                        std::cout << "User deleted.\n";
                        atm.logout();
                    } else {
                        std::cout << "Delete failed.\n";
                    }
                    break;
                }
                case 6:
                    atm.logout();
                    std::cout << "Logged out.\n";
                    break;
                case 0:
                    running = false;
                    break;
                default:
                    std::cout << "Invalid option.\n";
            }
        }
    }
    std::cout << "Thank you for using the ATM!\n";
    return 0;
}