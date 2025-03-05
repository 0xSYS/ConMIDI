#ifndef ESSENTIALS_H
#define ESSENTIALS_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int intInput(char* text);
void removeSymbol(char text[], char symbol, char* clean);
void error(char text[]);
char* concat(const char* str1, const char* str2);
double getTimeMsec(void);


void terminal_setup();
void ncurses_setup();
void info_log(const char * fmt, ...);
void success_log(const char * fmt, ...);
void warn_log(const char * fmt, ...);
void err_log(bool is_exit, const char * fmt, ...);

#endif
