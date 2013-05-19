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

int main(){
	srand(time(NULL));

	int threads, errors;
	for (threads = rand()%254 + 1 ; threads > 0; threads--){
		errors = thread_create(threadFunction, rand()%39 + 0);
	}

	while(/*!canExit()*/){
		thread_yield();
	}
}

void threadFunction(){
	int runTime;

	for( runTime = rand()%300 + 100; runTime > 0; runTime--){
		printf("I am Thread %d, with %d Tickets\n", /*get gbl thrad*/, /*get gbl_priority*/);

		if(rand()%10==0){
			thread_yield();
		}
	}
	thread_exit();
}

