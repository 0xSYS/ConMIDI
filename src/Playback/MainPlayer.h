#ifndef MAINPLAYER_H
#define MAINPLAYER_H

#include <stdatomic.h>
#include <stdbool.h>

extern int metaAllow[10];
extern int showFpsOutsideLag;
static atomic_bool PauseToggle = false;

void* StartPlayback(void* arg);
#endif
