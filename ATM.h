#pragma once
#include <vector>
#include <string>
#include "User.h"

class ATM {
private:
    std::vector<User> users;
    int currentUserIdx = -1;
public:
    ATM();
    bool createUser(const std::string& pin);
    bool login(const std::string& pin);
    void logout();
    bool deleteUser(const std::string& pin);
    bool changePin(const std::string& oldPin, const std::string& newPin);
    bool deposit(double amount);
    bool withdraw(double amount);
    double getBalance() const;
    bool isLoggedIn() const;
};

