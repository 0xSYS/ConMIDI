#include <stdio.h>
#include <pthread.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>


#include "Essentials.h"

#include "termanip.h"


void* ThreadTest1(void* arg)
{
	info_log("ThreadTest1() thread: %d", *(int*)arg);
	return NULL;
}


void* keyListener(void * arg)
{
	#ifdef FULL_DBG
	  info_log("keyListener() thread: %d", *(int*)arg);
	#endif
	while(TRUE)
	{
		key = getch();

		if(key != ERR)
		{
			if(key == 'q')
			{
				endwin();
				terminateConMIDI();
			}
			else if(key == ' ')
			{
				// move(4, 0);
				// printw("Space Pressed");
				pauseUnpausePlayback();
			}
		}

		usleep(50000);
		  // terminateConMIDI();
			// pauseUnpausePlayback();
	}
	return NULL;
}
