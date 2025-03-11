#ifndef ESSENTIALS_H
#define ESSENTIALS_H

#include <bits/pthreadtypes.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

static pthread_t midiPlayerThr;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static volatile bool ncursesMode = false;

int intInput(char* text);
void removeSymbol(char text[], char symbol, char* clean);
void error(char text[]);
char* concat(const char* str1, const char* str2);
double getTimeMsec(void);


#ifdef _WIN32
  void win_32terminal_setup();
#endif
void ncurses_setup();
void printKeyBinds();
void pauseUnpausePlayback();
void info_log(const char * fmt, ...);
void success_log(const char * fmt, ...);
void warn_log(const char * fmt, ...);
void err_log(bool is_exit, const char * fmt, ...);
void terminateConMIDI();

#endif
