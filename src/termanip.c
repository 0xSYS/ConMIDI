#include <stdatomic.h>
#include <stdio.h>
#include <pthread.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>


#include "Essentials.h"
#include "MIDI/LoadMIDI.h"
#include "Playback/MainPlayer.h"
#include "termanip.h"






void* keyListener(void * arg)
{
	  // info_log("keyListener() thread: %d", *(int*)arg);
  // mvprintw(9, 0, "Key Listener runing");

	while(TRUE)
	{
		key = getch();

		if(key != ERR)
		{
			if(key == 'q')
			{
				usleep(500000); // A bit of delay so that endwin() can do its job preventing the text from OmniMIDI debug logs to be messed up on the termial screen
				endwin();
				terminateConMIDI();
			}
			else if(key == ' ')
			{
				pthread_mutex_lock(&locker);
				PlaybackPauseToggle();

        
				/*if(PlaybackPause)
				{
					move(7, 0);
					printw("Playback Paused");
					// PlaybackPause();
				}
				else
				{
					move(7, 0);
					clrtoeol();
					// PlaybackUnpause();
				}*/

				pthread_mutex_unlock(&locker);
			}
		}
		usleep(50000);
	}
	return NULL;
}
