/**
 * Created: the_app.c
 * PROGRAMMING ASSIGNMENT 2
 * CMPS 111 Spring 2013
 * Authors: Andrew Bao, Konstantin Litovskiy, Tyler Esser & Nick Wood
 *
 * main class that creates the threads and sends them to the scheduler. 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _XOPEN_SOURCE
#include <ucontext.h>

#include "scheduler.h"


void threadFunction();

/** 
 * threads.c functions
 */

int main(){
    /* Give srand a seed number */
	srand(time(NULL));

    /* Insert a random number of threads into the scheduler */
	int threads;
	for (threads = rand()%254 + 1 ; threads > 0; threads--){
        thread_create(threadFunction, rand()%39 + 0);
	}

	while(numThreads() > 1){
		thread_yield();
	}
}

/**
 * Our thread function:
 * this does the arbitrary work we need 
 * for a function to be a thread
 */
void threadFunction(){
	int runTime;

	for( runTime = rand()%300 + 100; runTime > 0; runTime--){
		printf("I am Thread %d, with %d Tickets\n", 10/*get gbl thrad*/, 20/*get gbl_priority*/);

		if(rand()%10==0){
			thread_yield();
		}
	}
	thread_exit();
}
