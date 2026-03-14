#pragma once
#include <string>

class User {
private:
    std::string pin;
    double balance;
public:
    User(const std::string& pin, double balance = 0.0);
    const std::string& getPin() const;
    void setPin(const std::string& newPin);
    double getBalance() const;
    void deposit(double amount);
    bool withdraw(double amount);
};

