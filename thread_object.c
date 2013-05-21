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

	ucontext_t context;
	int id;
	int priority;

} ThreadObject;

/* Constructor */
TORef newThread(ucontext_t initCtx, int initID, int initPriority){	
	/* Allocate memory for the new thread objects */
	TORef thread = malloc(sizeof(ThreadObject));
	
	time_t tmpTime;
	time(&tmpTime);
	
	/* Set thread data values */
	thread->context    = initCtx;
	thread->id         = initID;
	thread->priority   = initPriority;
	
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

/* Accessors */
ucontext_t getContext(TORef T){
	return T->context;
}
int getID(TORef T){
	return T->id;
}
int getPriority(TORef T){
    return T->priority;
}