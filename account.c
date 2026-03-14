#include "account.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_accounts(Account **accounts, int *count) {
    FILE *fp = fopen(ACCOUNTS_FILE, "rb");
    if (!fp) { *accounts = NULL; *count = 0; return 0; }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    *count = size / sizeof(Account);
    *accounts = (Account*)malloc(size);
    fread(*accounts, sizeof(Account), *count, fp);
    fclose(fp);
    return *count;
}

int save_accounts(Account *accounts, int count) {
    FILE *fp = fopen(ACCOUNTS_FILE, "wb");
    if (!fp) return 0;
    fwrite(accounts, sizeof(Account), count, fp);
    fclose(fp);
    return 1;
}

int find_account(Account *accounts, int count, int account_number) {
    for (int i = 0; i < count; ++i) {
        if (accounts[i].account_number == account_number) return i;
    }
    return -1;
}

int authenticate(Account *accounts, int count, int account_number, const char *pin) {
    int idx = find_account(accounts, count, account_number);
    if (idx == -1) return -1;
    if (accounts[idx].locked) return -2;
    if (strcmp(accounts[idx].pin, pin) == 0) return idx;
    return -1;
}

void reset_failed_attempts(Account *accounts, int idx) { accounts[idx].failed_attempts = 0; }
void increment_failed_attempts(Account *accounts, int idx) { accounts[idx].failed_attempts++; }
void lock_account(Account *accounts, int idx) { accounts[idx].locked = 1; }
void unlock_account(Account *accounts, int idx) { accounts[idx].locked = 0; accounts[idx].failed_attempts = 0; }

int create_account(Account **accounts, int *count, const char *name, const char *pin) {
    int new_acc_num = 1000 + *count;
    *accounts = (Account*)realloc(*accounts, (*count + 1) * sizeof(Account));
    Account *acc = &(*accounts)[*count];
    acc->account_number = new_acc_num;
    strncpy(acc->name, name, NAME_LEN);
    strncpy(acc->pin, pin, PIN_LEN);
    acc->balance = 0.0;
    acc->locked = 0;
    acc->failed_attempts = 0;
    (*count)++;
    save_accounts(*accounts, *count);
    return new_acc_num;
}

