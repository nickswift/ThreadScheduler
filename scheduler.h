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

<<<<<<< HEAD
/* Functions Declarations */
int thread_create(void (*)(void), int);
void thread_yield();
void thread_exit();
=======
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
>>>>>>> 73fd5d501f22e4fcd72e4ad4a0ea9fdc41f07f04

#endif

