#ifndef MAINPLAYER_H
#define MAINPLAYER_H

#include <stdatomic.h>
#include <stdbool.h>

extern int metaAllow[10];
extern int showFpsOutsideLag;
static volatile bool PlaybackPause = false;

void* StartPlayback(void* arg);
void PlaybackPauseToggle();
#endif
