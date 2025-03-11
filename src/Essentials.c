// #include <cstdarg>
// #include <cstdarg>
#include "MIDI/LoadMIDI.h"
#include "termanip.h"
#include "Sound/KDMAPI.h"

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdarg.h>
#include <stdbool.h>
#include <ncurses.h>

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #define VC_EXTRALEAN
    #include <Windows.h>


    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
    #endif
#endif

#include "Essentials.h"

char ntdllAvailable = 0;
signed long long start = 0;
bool ncursesMode = false;

int intInput(char *text)
{
    int num;
    printf(text);
    scanf("%d", &num);
    fflush(stdin);
    return num;
}
void removeSymbol(char text[], char symbol, char *clean)
{
    int i, j;
    for (i = 0, j = 0; i < strlen(text); i++)
    {
        if (text[i] != symbol)
        {
            clean[j++] = text[i];
        }
    }
    clean[j] = '\0';
}
/*
void error(char text[])
{
    printf("\n[ERROR] %s\n", text);
    exit(0);
}
*/
// Now replaced by error_log() function


char *concat(const char *str1, const char *str2)
{
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char *result = malloc(len1 + len2 + 1);
    if (result == NULL)
    {
        return NULL;
    }
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

double getTimeMsec(void)
{

        struct timeval tv;
        gettimeofday(&tv, NULL);
        return (((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
    
}

#ifdef _WIN32

static HANDLE stdoutHandle, stdinHandle;
static DWORD outModeInit, inModeInit;

// Enables ansi escapes on windows terminal
void win32_terminal_setup()
{
    DWORD outMode = 0, inMode = 0;
    stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    stdinHandle = GetStdHandle(STD_INPUT_HANDLE);

    if(stdoutHandle == INVALID_HANDLE_VALUE || stdinHandle == INVALID_HANDLE_VALUE) 
    {
        exit(GetLastError());
    }
    
    if(!GetConsoleMode(stdoutHandle, &outMode) || !GetConsoleMode(stdinHandle, &inMode)) 
    {
        exit(GetLastError());
    }

    outModeInit = outMode;
    inModeInit = inMode;
    
    // Enable ANSI escape codes
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    // Set stdin as no echo and unbuffered
    inMode = (ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT);

    if(!SetConsoleMode(stdoutHandle, outMode) || !SetConsoleMode(stdinHandle, inMode)) 
    {
        exit(GetLastError());
    }
    SetConsoleOutputCP(CP_UTF8); //Enabling unicode charset on windows console
}
#endif

void ncurses_setup()
{
    // Set up the ncurses things
    initscr();
    noecho();
    // nodelay(stdscr, TRUE);
    curs_set(FALSE);
    scrollok(stdscr, TRUE);
    cbreak();
}



void internal_vprintf(const char * fmt, va_list args)
{
    char buf[1024];
    vsnprintf(buf, sizeof(buf), fmt, args);
    printw("%s", buf);
}

// Logging functions
void info_log(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    printf("ConMIDI: [\033[38;5;188mInfo\033[0m] -> ");
    vprintf(fmt, args);
    // internal_vprintf(fmt, args);
    puts("");
    va_end(args);
}

void success_log(const char *fmt, ...)
{
    va_list args;
    printf("ConMIDI: [\033[38;5;40mSuccess !\033[0m] -> ");
    vprintf(fmt, args);
    // internal_vprintf(fmt, args);
    puts("");
    va_end(args);
}

void warn_log(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    printf("ConMIDI: [\033[38;5;220mWarn\033[0m] -> ");
    vprintf(fmt, args);
    // internal_vprintf(fmt, args);
    puts("");
    va_end(args);
}

void err_log(bool is_exit, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    printf("ConMIDI: [\033[38;5;196mErr\033[0m] -> ");
    vprintf(fmt, args);
    // internal_vprintf(fmt, args);
    puts("");
    va_end(args);

    if(is_exit == true)
      exit(1);
}

void pauseUnpausePlayback()
{
    static bool state = false;
    state ^= 1;

    // Some toggle thingy
    if(state)
    {
        // Pause the playback thread
        move(5, 0);
        printw("Playback paused");
        pthread_kill(midiPlayerThr, SIGSTOP);
    }
    if(!state)
    {
        // Resume the playback thread
        move(5, 0);
        clrtoeol();
        pthread_kill(midiPlayerThr, SIGCONT);
    }
}


void printKeyBinds()
{
    mvprintw(0, 0, "Press space to pause & unpause");
    mvprintw(1, 0, "Press 'q' to quit");
}


void terminateConMIDI()
{
    // Safely quit ConMIDI witout segfault


    // pthread_detach(keyHandle);
    // pthread_detach(midiPlayerThr);
    pthread_mutex_destroy(&locker);

    // Ncurses stuff
    // endwin();

    fflush(stdout);

    // pthread_cancel(playbackThread);
    
    // Safely terminate OmniMIDI from processing events so it won't seg fault
    info_log("Terminating KDMAPI...");
    KDMAPI_TerminateKDMAPIStream();

    // endwin();
    // And finally quit ConMIDI
    exit(0);
}
