#ifndef ACCOUNT_H
#define ACCOUNT_H

#define NAME_LEN 50
#define PIN_LEN 10
#define ACCOUNTS_FILE "accounts.dat"

typedef struct {
    int account_number;
    char name[NAME_LEN];
    char pin[PIN_LEN];
    double balance;
    int locked; // 0 = unlocked, 1 = locked
    int failed_attempts;
} Account;

int load_accounts(Account **accounts, int *count);
int save_accounts(Account *accounts, int count);
int find_account(Account *accounts, int count, int account_number);
int authenticate(Account *accounts, int count, int account_number, const char *pin);
void reset_failed_attempts(Account *accounts, int idx);
void increment_failed_attempts(Account *accounts, int idx);
void lock_account(Account *accounts, int idx);
void unlock_account(Account *accounts, int idx);
int create_account(Account **accounts, int *count, const char *name, const char *pin);

#endif // ACCOUNT_H

