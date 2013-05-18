/**
 * Created: thread_object.c
 * PROGRAMMING ASSIGNMENT 2
 * CMPS 111 Spring 2013
 * Authors: Andrew Bao, Konstantin Litovskiy, Tyler Esser & Nick Wood
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "thread_object.h"

typedef struct ThreadObject {
	/* stores thread's id, and number of 
	 * iterations it will perform 
	 */
	int id, iteration_time;
	
	/* stores thread's creation time */
	time_t create_time; 
} ThreadObject;

/* Constructor */
TORef newThread(int initID, initIT){	
	/* Allocate memory for the new thread objects */
	TORef thread = malloc(sizeof(ThreadObject));
	
	time_t tmpTime;
	time(&tmpTime);
	
	/* Set thread data values */
	thread->id             = initID;
	thread->iteration_time = initIT;
	thread->create_time    = tmpTime;
	
	return(thread);
}

/* destructor */
void freeThread(TORef T){
    TORef * pT = &T;
    if(*pT != NULL && pT != NULL){
        free(*pT);
        *pT = NULL;
    }
}