#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pause() {
    printf("Press Enter to continue...");
    getchar();
}

void get_string(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

int get_int(const char *prompt) {
    char buf[32];
    int val;
    while (1) {
        printf("%s", prompt);
        fgets(buf, sizeof(buf), stdin);
        if (sscanf(buf, "%d", &val) == 1) return val;
        printf("Invalid input. Try again.\n");
    }
}

double get_double(const char *prompt) {
    char buf[32];
    double val;
    while (1) {
        printf("%s", prompt);
        fgets(buf, sizeof(buf), stdin);
        if (sscanf(buf, "%lf", &val) == 1) return val;
        printf("Invalid input. Try again.\n");
    }
}

void get_pin(char *buffer, int size) {
    get_string("Enter PIN: ", buffer, size);
}

void get_date(char *buffer, int size) {
    time_t now = time(NULL);
    strftime(buffer, size, "%Y-%m-%d %H:%M", localtime(&now));
}

