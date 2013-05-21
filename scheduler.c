/**
 * Modified: scheduler.c
 * PROGRAMMING ASSIGNMENT 2
 * CMPS 111 Spring 2013
 * Authors: Andrew Bao, Konstantin Litovskiy, Tyler Esser & Nick Wood
 *
 * Scheduler.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "scheduler.h"

typedef struct SchedLottery{
	
	TLRef threadList;
	TNRef runningNode;
	int time_quantum;
	int winner;
	
} SchedLottery;

/* Constructor */
SLotto newLottery(int initQuantum){

	/* Allocate memory for the new node */
	SLotto _lotto = malloc(sizeof(SchedLottery));

	/* Seed randomizer */
	srand (time(NULL));

	/* Set loto data values */
	_lotto->threadList 	 = newThreadList();
	_lotto->runningNode  = NULL;
	_lotto->time_quantum = initQuantum;
	_lotto->winner 		 = -1;
	
	setupTimer(_lotto->time_quantum);
	return(_lotto);
}

/* Add a thread to the scheduler */
void createThread(SLotto S, void *data, int priority){
    /* Insert the data into the thread list */
    insertData(S->threadList, data, priority);
}

void freeSchedLottery(SLotto S){
    /* Free the running node */
	/* freeNode(oldLotto->runningNode); */
	
	/* free pointer to running node */
	S->runningNode = NULL;
	
	/* Free the list of threads */
	clearList(S->threadList);
	freeList(&(S->threadList));
	
	/* Free this object */
	SLotto *pS = &S;
	free(*pS);
	*pS = NULL;
}

void runScheduler(SLotto S){
	while(1){
		int run = 1;
		while(run){
			if(!isListEmpty(S->threadList)){
				S->runningNode = getNextNode(S);
				run = 0;
			}
			startTimer(S);
		}
	}
}

TNRef getNextNode(SLotto S){
    /* Get the thread list */
	TLRef L     = S->threadList;
	int tickets = getTickets(L);
	
	/* Get a random index and get a node from the list */
	int newIndex = rand()%tickets+1;
	TNRef N      = getNodeAtIndex(L, newIndex);
	
	return N;
}

void setupTimer(int timerQuantum){
}

void stopTimer(SLotto S){
}

void startTimer(SLotto S){
}
