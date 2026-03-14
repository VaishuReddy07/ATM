#include "transaction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void log_transaction(int account_number, const char *type, double amount, int target_account) {
    FILE *fp = fopen(TRANSACTION_FILE, "ab");
    if (!fp) return;
    Transaction t;
    t.account_number = account_number;
    strncpy(t.type, type, 15);
    t.amount = amount;
    t.target_account = target_account;
    time_t now = time(NULL);
    strftime(t.date, DATE_LEN, "%Y-%m-%d %H:%M", localtime(&now));
    fwrite(&t, sizeof(Transaction), 1, fp);
    fclose(fp);
}

void show_transaction_history(int account_number) {
    FILE *fp = fopen(TRANSACTION_FILE, "rb");
    if (!fp) { printf("No transaction history.\n"); return; }
    Transaction t;
    printf("\n--- Transaction History ---\n");
    while (fread(&t, sizeof(Transaction), 1, fp)) {
        if (t.account_number == account_number) {
            printf("%s | %s | %.2f", t.date, t.type, t.amount);
            if (strcmp(t.type, "transfer") == 0)
                printf(" | To: %d", t.target_account);
            printf("\n");
        }
    }
    fclose(fp);
}

