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
	printf("Inserting threads\n");
	for (threads = rand()%10/*254*/ + 1 ; threads > 0; threads--){
        thread_create(threadFunction, rand()%39 + 0);
	}
	printf("Threads inserted\n\n");
	
	while(numThreads() > 1){
		printf("Thread yielding\n");
		thread_yield();
	}
	
	return 0;
}

/**
 * Our thread function:
 * this does the arbitrary work we need 
 * for a function to be a thread
 */
void threadFunction(){
	int runTime;
	int ctid;

	for( runTime = rand()%10 + 5; runTime > 0; runTime--){
		
		ctid 		= get_gbl_thread();
		TLRef tmpL 		= get_gbl_thread_list();
		int ct_tickets 	= getID_tickets(tmpL, ctid);
	
		printf("I am Thread %d, with %d Tickets\n", ctid, ct_tickets);

		sleep(1);
		
		if(rand()%10 == 0){
			printf("Thread ID %d Yielding\n",ctid);
			thread_yield();
		}
	}
	printf("Thread ID %d Exiting\n", ctid);
	thread_exit();
}
