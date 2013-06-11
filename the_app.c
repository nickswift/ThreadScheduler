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

#define NUM_THREADS 40
#define NUM_THREADS_BASE 10
#define THREAD_RUNS 40
#define THREAD_RUNS_BASE 10

void threadFunction(void);

/** 
 * threads.c functions
 */
int main(void)
{
    /* Give srand a seed number */
	srand(time(NULL));
	
	/* sets up the scheduler. only happens once */
    init_scheduler();

    /* Insert a random number of threads into the scheduler */
	int threads;
	printf("Inserting threads\n");
	for (threads = rand()%NUM_THREADS + NUM_THREADS_BASE; threads > 0; threads--){
        thread_create(threadFunction, rand()%39 + 0);
	}
	printf("Threads inserted\n\n");
	
	/* TLRef _list = get_gbl_thread_list(); */
	while(numThreads() > 1){
		printf("%d threads left.\n", numThreads());
		
		printf("MAIN Yielding\n\n***\n");
		thread_yield();
	}
	
	printf("\n************ ************\n");
	printf("SIMULATION FINISHED. YAY!");
	printf("\n************ ************\n");
	return 0;
}

/**
 * Our thread function:
 * this does the arbitrary work we need 
 * for a function to be a thread
 */
void threadFunction(void)
{
	int runTime;
	int ctid;

	for( runTime = rand()%THREAD_RUNS + THREAD_RUNS_BASE; runTime > 0; runTime--){
		
		ctid 		    = get_gbl_curr_thread();
		TLRef tmpL 		= get_gbl_thread_list();
		int ct_tickets 	= getID_tickets(tmpL, ctid);
	
		printf("I am Thread %d, with %d Tickets\n", ctid, ct_tickets);
		
		if(rand()%10 == 0){
			printf("Thread ID %d Yielding\n\n***\n",ctid);
			thread_yield();
		
		}
	}
	printf("Thread ID %d Exiting\n\n***\n", ctid);
	thread_exit();
}
