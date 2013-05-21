/**
 * Modified: scheduler.c
 * PROGRAMMING ASSIGNMENT 2
 * CMPS 111 Spring 2013
 * Authors: Andrew Bao, Konstantin Litovskiy, Tyler Esser & Nick Wood
 *
 * Scheduler.c
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ucontext.h>

#include "scheduler.h"
<<<<<<< HEAD
#include "thread_list.h"

/* Global Variables */
static int gbl_curr_thread;
static int gbl_curr_thread_priority;
static int gbl_total_tickets;
static TLRef gbl_thread_list;

/* Struct Typedefs */
typedef struct ThreadObj {
    ucontext_t ctx;
    int tid;
    int tickets;
} ThreadObj;

/* Functions Declarations */
void init_scheduler();
ThreadObj *create_ThreadObj(ucontext_t*, int);

int thread_create(void (*thread_func)(void), int priority){
    init_scheduler();

    /* get a valid context */
    ucontext_t *pCTX = malloc(sizeof(ucontext_t));
    getcontext(pCTX);

    /* give context new stack to separate from other contexts */
    pCTX->uc_stack.ss_sp = malloc(THREAD_STACKSIZE);
    pCTX->uc_stack.ss_size = THREAD_STACKSIZE;

    /* TODO: not sure how uc_link is used */
    pCTX->uc_link = pMainCTX;

    /* TODO: create thread object to insert into list */

    /* make the new context with the provided function */
    makecontext(pCTX, thread_func, 0);
}

ThreadObj *create_ThreadObj(ucontext_t *pCTX, int priority){
        static totalThreads = 0;

        if(priority >= 40 || priority < 0){
            printf("Thread priority is between 0 (highest) and 39 (lowest)\n");
            exit(1);
        }

        ThreadObj *pThrObj = malloc(sizeof(ThreadObj));

        /* priority to ticket conversion */
        int tickets = 40 - priority;

        pThrObj->tickets = tickets;
        pThrObj->tid = totalThreads++;

        return pThrObj;
}

void init_scheduler(){
    static sched_init = 0;
    if(sched_init == 0){
        gbl_thread_list = newThreadList();

        ucontext_t tmpCtx;
        getcontext(&tmpCtx);

        /* Zeroth thread get average priority */
        ThreadObj *pFirstThreadData = create_ThreadObj(&tmpCtx, 20);

        add_thread(pFirstThreadData);

        /* prevent this function from being called multiple times */
        sched_init = 1;
    }

    return;
}
=======

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
>>>>>>> 73fd5d501f22e4fcd72e4ad4a0ea9fdc41f07f04
