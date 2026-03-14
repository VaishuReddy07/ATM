#ifndef TRANSACTION_H
#define TRANSACTION_H

#define TRANSACTION_FILE "transactions.dat"
#define DATE_LEN 20

typedef struct {
    int account_number;
    char type[16]; // deposit, withdraw, transfer
    double amount;
    char date[DATE_LEN];
    int target_account; // for transfer, else 0
} Transaction;

void log_transaction(int account_number, const char *type, double amount, int target_account);
void show_transaction_history(int account_number);

#endif // TRANSACTION_H

