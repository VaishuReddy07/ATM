#ifndef UTILS_H
#define UTILS_H

void clear_input();
void pause();
void get_string(const char *prompt, char *buffer, int size);
int get_int(const char *prompt);
double get_double(const char *prompt);
void get_pin(char *buffer, int size);
void get_date(char *buffer, int size);

#endif // UTILS_H

