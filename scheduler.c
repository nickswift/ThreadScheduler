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
#include <signal.h>

#define _XOPEN_SOURCE
#include <ucontext.h>

#include <sys/time.h>

#include "scheduler.h"
#include "thread_list.h"

/* Global constants */
#define THREAD_STACKSIZE 8192
#define TIMER_Q_SEC 0
#define TIMER_Q_USEC 300

/* Struct Typedefs */
typedef struct ThreadObj {
    ucontext_t ctx;
    int tid;
    int tickets;
} ThreadObj;

/* Global Variables */
static int gbl_curr_thread;
static int gbl_curr_thread_priority;
static TLRef gbl_thread_list;

/* Functions Declarations */
void init_scheduler();
ThreadObj *create_ThreadObj(ucontext_t*, int);

int thread_create(void (*thread_func)(void), int priority){
    /* sets up the scheduler. only happens once */
    init_scheduler();

    /* get a valid context */
    ucontext_t *pCTX = malloc(sizeof(ucontext_t));
    getcontext(pCTX);

    /* give context new stack to separate from other contexts */
    pCTX->uc_stack.ss_sp = malloc(THREAD_STACKSIZE);
    pCTX->uc_stack.ss_size = THREAD_STACKSIZE;
    
    /* uc_link used if thread exits. using main thread's ctx */
    ThreadObj *pThrObj = getID(gbl_thread_list, 0);
    pCTX->uc_link      = &(pThrObj->ctx);

    /* create thread object to insert into list */
    insertData(gbl_thread_list, pThrObj->tid, pThrObj, pThrObj->tickets);

    /* make the new context with the provided function */
    makecontext(pCTX, thread_func, 0);
}

void thread_yield(){
    struct itimerval sched_timer = {0};

    /* turn off timer while in scheduler */
    setitimer(ITIMER_VIRTUAL, &sched_timer, NULL);

    int old_tid = gbl_curr_thread;

    gbl_curr_thread = lottery();

    /* don't need to swap if it's the same thread */
    if(old_tid != gbl_curr_thread){
        
        ThreadObj *thrOne = getID(gbl_thread_list,old_tid);
        ThreadObj *thrTwo = getID(gbl_thread_list,gbl_curr_thread);
    
        swapcontext(&(thrOne->ctx),&(thrTwo->ctx));
    }

    /* restart the timer */
    struct itimerval new_timer = {0};
    sched_timer.value.tv_sec  = TIMER_Q_SEC;
    sched_timer.value.tv_usec = TIMER_Q_USEC;

    setitimer(ITIMER_VIRTUAL, &new_timer, NULL);
    return;
}

int numThreads(){
    return getSize(gbl_thread_list);
}

/* return the thread id of the next thread */
int lottery(){
    int totalTickets = getTickets(gbl_thread_list);
    int goldenTicket = rand() % totalTickets;

    int index;
    for(index = 0; goldenTicket > 0; index++){
        /* decrement tickets until negative,
         * giving the index of the selected thread */
        ThreadObj *tobj = getIndex(gbl_thread_list, index);
        goldenTicket   -= tobj->tickets;
    }
    /* get returned value */
    ThreadObj *retobj = getIndex(gbl_thread_list, index);
    return retobj->tid;

}

ThreadObj *create_ThreadObj(ucontext_t *pCTX, int priority){
    static int totalThreads = 0;

    if(priority >= 40 || priority < 0){
        printf("Thread priority is between 0 (highest) and 39 (lowest)\n");
        exit(1);
    }

    ThreadObj *pThrObj = malloc(sizeof(ThreadObj));

    /* priority to ticket conversion */
    int tickets = 40 - priority;

    pThrObj->tickets = tickets;
    pThrObj->tid = totalThreads++;
    pThrObj->ctx = *(pCTX);

    return pThrObj;
}

void init_scheduler(){
    static just_once = 0;

    if(just_once++ == 0){
        gbl_thread_list = newThreadList();

        ucontext_t tmpCtx;
        getcontext(&tmpCtx);

        /* main thread get average priority */
        ThreadObj *pThrObj = create_ThreadObj(&tmpCtx, 20);

        insertData(gbl_thread_list, pThrObj, pThrObj->tickets, pThrObj->tid);

        struct sigaction sched_handler = {0};
        sched_handler.sa_handler = &thread_yield;

        sigaction(SIGVTALRM, &sched_handler, NULL);
    }
    return;
}

