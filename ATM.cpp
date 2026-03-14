#include "ATM.h"

ATM::ATM() {}

bool ATM::createUser(const std::string& pin) {
    for (const auto& user : users) {
        if (user.getPin() == pin) return false;
    }
    users.emplace_back(pin);
    return true;
}

bool ATM::login(const std::string& pin) {
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i].getPin() == pin) {
            currentUserIdx = static_cast<int>(i);
            return true;
        }
    }
    return false;
}

void ATM::logout() { currentUserIdx = -1; }

bool ATM::deleteUser(const std::string& pin) {
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->getPin() == pin) {
            users.erase(it);
            if (currentUserIdx >= static_cast<int>(users.size())) currentUserIdx = -1;
            return true;
        }
    }
    return false;
}

bool ATM::changePin(const std::string& oldPin, const std::string& newPin) {
    if (currentUserIdx == -1) return false;
    if (users[currentUserIdx].getPin() != oldPin) return false;
    users[currentUserIdx].setPin(newPin);
    return true;
}

bool ATM::deposit(double amount) {
    if (currentUserIdx == -1) return false;
    users[currentUserIdx].deposit(amount);
    return true;
}

bool ATM::withdraw(double amount) {
    if (currentUserIdx == -1) return false;
    return users[currentUserIdx].withdraw(amount);
}

double ATM::getBalance() const {
    if (currentUserIdx == -1) return 0.0;
    return users[currentUserIdx].getBalance();
}

bool ATM::isLoggedIn() const { return currentUserIdx != -1; }

