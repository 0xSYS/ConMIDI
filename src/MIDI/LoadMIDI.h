#ifndef LOADMIDI_H
#define LOADMIDI_H


#include <pthread.h>
#include <signal.h>

static pthread_t playbackThread;
static pthread_t keyHandle;

void LoadMIDI(char path[], unsigned int bs);

#endif
