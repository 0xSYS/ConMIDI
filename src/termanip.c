#include <stdio.h>
#include <pthread.h>
#include <ncurses.h>
#include <stdlib.h>


#include "Essentials.h"

#include "termanip.h"


void* ThreadTest1(void* arg)
{
	info_log("ThreadTest1() thread: %d", *(int*)arg);
	return NULL;
}


void* keyListener(void * arg)
{
	//#ifdef FULL_DBG
	  info_log("keyListener() thread: %d", *(int*)arg);
	//#endif
	while(TRUE)
	{
		key = getch();
		if(key == 'q')		/* Without keypad enabled this will */
		{
			// move(2, 1);
		  // printw("F1 Key pressed");/*  not get to us either	*/
					                     /* Without noecho() some ugly escape
					                      * charachters might have been printed
					                      * on screen			*/
		  // exit(0);
		  terminateConMIDI();
		}
	  else
	  {
	  	int row = 0;
	  	mvprintw(row++, 0, "The pressed key is %c", key);
	  	// attron(A_BOLD);
	  	// printw("%c", key);
	  	attroff(A_BOLD);
	  }
	  refresh();			/* Print it on to the real screen */
	  getch();
	}
	return NULL;
}
