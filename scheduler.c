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
#include <stdbool.h>
#include "scheduler.h"
#include "thread_list.c"
#include "thread_object.h"

typedef struct SchedLottery{
	
	/* 
	 */
	TLRef * threadList;
	TLNodeRef * runningNode;
	int time_quantum;
			
} SchedLottery;

/* Constructor */
SLotto newLottery(int initQuantum){
	/* Allocate memory for the new node */
	SLotto _lotto = malloc(sizeof(SchedLottery));
	
	/* Seed randomizer */
	srand (time(NULL));
	
	/* Set loto data values */
	_loto->threadList 	= newThreadList();
	_loto->runningNode	= NULL;
	_loto->time_quantum = initQuantum;
	_loto->winner 		= -1;
	setupTimer(_lotto->time_quantum);

	return(_loto);
}

void freeSchedLottery(SLotto * oldLotto){
	freeThreadListNode( oldLotto->runningNode );
	freeThreadList( oldLotto->threadList );
	
	free(*oldLotto);
	oldLotto = NULL;
}

void runScheduler(SLotto _lotto){
	while(true){
		bool run = true;
		while(run){
			if(!isListEmpty(_lotto->threadList)){
				_lotto->runningNode = getNextNode(_lotto);
				run = false;
			}
			startTimer();
			/*startThread()*/
		}
	}
}

TLNodeRef getNextNode(SLotto * _lotto){

	TLRef * _list = _lotto->threadList;
	int newIndex = rand() % _list->ticketCount + 1;
			
	TLNodeRef * _node = getNodeAtIndex (_list, newIndex);
	
	return _node;
}

void setupTimer(int timerQuantum){

}

void stopTimer(SLotto * _lotto){

}

void startTimer(SLotto * _lotto){

}



