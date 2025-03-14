/*
Contains functions for handling terminal manipulation using ncurses
*/
#pragma once
#include <pthread.h>





static pthread_t keyHandle;
static int thread_id = 1;
static int key;



void* keyListener(void * arg);
