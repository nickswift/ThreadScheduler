/**
 * Modified: scheduler.h
 * PROGRAMMING ASSIGNMENT 2
 * CMPS 111 Spring 2013
 * Authors: Andrew Bao, Konstantin Litovskiy, Tyler Esser & Nick Wood
 *
 * Scheduler.h
 */
 
#include "thread_list.h"

#ifndef _SCHEDULER_H_INCLUDE
#define _SCHEDULER_H_INCLUDE

typedef struct SchedLottery * SLotto;

/* Constructor */
SLotto newLottery(int initQuantum);

/* Cleanup */
void runScheduler(SLotto Lotto);
void freeSchedLottery(SLotto S);

/* Create threads */
void createThread(SLotto S, void* data, int priority);

/* Scheduler Functions */
TNRef getNextNode(SLotto S);

/* Timer Manipulations */
void setupTimer(int timerQuantum);
void stopTimer(SLotto S);
void startTimer(SLotto S);

#endif

