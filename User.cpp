#include "User.h"

User::User(const std::string& pin, double balance) : pin(pin), balance(balance) {}

const std::string& User::getPin() const { return pin; }

void User::setPin(const std::string& newPin) { pin = newPin; }

double User::getBalance() const { return balance; }

void User::deposit(double amount) { if (amount > 0) balance += amount; }

bool User::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}

