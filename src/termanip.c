#include <stdatomic.h>
#include <stdio.h>
#include <pthread.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>


#include "Essentials.h"
#include "Playback/MainPlayer.h"
#include "termanip.h"



void* ThreadTest1(void* arg)
{
	info_log("ThreadTest1() thread: %d", *(int*)arg);
	return NULL;
}


void* keyListener(void * arg)
{
	//#ifdef FULL_DBG
	  // info_log("keyListener() thread: %d", *(int*)arg);
	  move(9, 0);
	  printw("Key Listener runing");
//	#endif
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
				// static bool PauseToggle = false;
				//PauseToggle = !PauseToggle;
				// pauseState = !pauseState;

				atomic_store(&PauseToggle, !atomic_load(&PauseToggle));

				if(atomic_load(&PauseToggle))
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
				}
				
        
				
			}
		}
		usleep(50000);
	}
	return NULL;
}
