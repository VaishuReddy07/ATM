#include "atm_c.h"
#include "account.h"
#include "transaction.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ATTEMPTS 3

void user_menu(Account *accounts, int idx, int *acc_count);
void admin_menu(Account **accounts, int *acc_count);

void atm_menu() {
    Account *accounts = NULL;
    int acc_count = 0;
    load_accounts(&accounts, &acc_count);
    int choice;
    while (1) {
        printf("\n--- ATM Main Menu ---\n");
        printf("1. Login\n2. Create Account\n3. Admin Mode\n0. Exit\n");
        choice = get_int("Select option: ");
        if (choice == 1) {
            int acc_num = get_int("Enter account number: ");
            char pin[PIN_LEN];
            get_pin(pin, PIN_LEN);
            int idx = find_account(accounts, acc_count, acc_num);
            if (idx == -1) { printf("Account not found.\n"); continue; }
            if (accounts[idx].locked) { printf("Account is locked. Contact admin.\n"); continue; }
            if (strcmp(accounts[idx].pin, pin) == 0) {
                printf("Login successful.\n");
                reset_failed_attempts(accounts, idx);
                save_accounts(accounts, acc_count);
                user_menu(accounts, idx, &acc_count);
            } else {
                printf("Incorrect PIN.\n");
                increment_failed_attempts(accounts, idx);
                if (accounts[idx].failed_attempts >= MAX_ATTEMPTS) {
                    lock_account(accounts, idx);
                    printf("Account locked due to too many failed attempts.\n");
                }
                save_accounts(accounts, acc_count);
            }
        } else if (choice == 2) {
            char name[NAME_LEN], pin[PIN_LEN];
            get_string("Enter your name: ", name, NAME_LEN);
            get_pin(pin, PIN_LEN);
            int new_acc = create_account(&accounts, &acc_count, name, pin);
            printf("Account created. Your account number: %d\n", new_acc);
        } else if (choice == 3) {
            admin_menu(&accounts, &acc_count);
        } else if (choice == 0) {
            save_accounts(accounts, acc_count);
            free(accounts);
            printf("Thank you for using the ATM!\n");
            break;
        } else {
            printf("Invalid option.\n");
        }
    }
}

void user_menu(Account *accounts, int idx, int *acc_count) {
    int choice;
    while (1) {
        printf("\n--- User Menu ---\n");
        printf("1. Check Balance\n2. Deposit\n3. Withdraw\n4. Transfer\n5. Change PIN\n6. Transaction History\n0. Logout\n");
        choice = get_int("Select option: ");
        if (choice == 1) {
            printf("Current balance: %.2f\n", accounts[idx].balance);
        } else if (choice == 2) {
            double amt = get_double("Enter deposit amount: ");
            if (amt > 0) {
                accounts[idx].balance += amt;
                save_accounts(accounts, *acc_count);
                log_transaction(accounts[idx].account_number, "deposit", amt, 0);
                printf("Deposited successfully.\n");
            } else {
                printf("Invalid amount.\n");
            }
        } else if (choice == 3) {
            double amt = get_double("Enter withdrawal amount: ");
            if (amt > 0 && amt <= accounts[idx].balance) {
                accounts[idx].balance -= amt;
                save_accounts(accounts, *acc_count);
                log_transaction(accounts[idx].account_number, "withdraw", amt, 0);
                printf("Withdrawal successful.\n");
            } else {
                printf("Insufficient balance or invalid amount.\n");
            }
        } else if (choice == 4) {
            int target_acc = get_int("Enter target account number: ");
            int t_idx = find_account(accounts, *acc_count, target_acc);
            if (t_idx == -1) { printf("Target account not found.\n"); continue; }
            double amt = get_double("Enter transfer amount: ");
            if (amt > 0 && amt <= accounts[idx].balance) {
                accounts[idx].balance -= amt;
                accounts[t_idx].balance += amt;
                save_accounts(accounts, *acc_count);
                log_transaction(accounts[idx].account_number, "transfer", amt, accounts[t_idx].account_number);
                printf("Transferred successfully.\n");
            } else {
                printf("Insufficient balance or invalid amount.\n");
            }
        } else if (choice == 5) {
            char new_pin[PIN_LEN];
            get_pin(new_pin, PIN_LEN);
            strncpy(accounts[idx].pin, new_pin, PIN_LEN);
            save_accounts(accounts, *acc_count);
            printf("PIN changed successfully.\n");
        } else if (choice == 6) {
            show_transaction_history(accounts[idx].account_number);
        } else if (choice == 0) {
            printf("Logged out.\n");
            break;
        } else {
            printf("Invalid option.\n");
        }
    }
}

void admin_menu(Account **accounts, int *acc_count) {
    int choice;
    while (1) {
        printf("\n--- Admin Menu ---\n");
        printf("1. Unlock Account\n2. List Accounts\n0. Back\n");
        choice = get_int("Select option: ");
        if (choice == 1) {
            int acc_num = get_int("Enter account number to unlock: ");
            int idx = find_account(*accounts, *acc_count, acc_num);
            if (idx == -1) { printf("Account not found.\n"); continue; }
            unlock_account(*accounts, idx);
            save_accounts(*accounts, *acc_count);
            printf("Account unlocked.\n");
        } else if (choice == 2) {
            printf("\nAccount List:\n");
            for (int i = 0; i < *acc_count; ++i) {
                printf("%d | %s | Balance: %.2f | %s\n", (*accounts)[i].account_number, (*accounts)[i].name, (*accounts)[i].balance, (*accounts)[i].locked ? "Locked" : "Active");
            }
        } else if (choice == 0) {
            break;
        } else {
            printf("Invalid option.\n");
        }
    }
}

