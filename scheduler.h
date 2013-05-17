/**
 * Modified: scheduler.h
 * PROGRAMMING ASSIGNMENT 2
 * CMPS 111 Spring 2013
 * Authors: Andrew Bao, Konstantin Litovskiy, Tyler Esser & Nick Wood
 * 
 * Scheduler.h
 */

#if !defined(_SCHEDULER_H_INCLUDE_)
#define _SCHEDULER_H_INCLUDE
#endif 

typedef struct SchedLottery * SLotto;

/* Constructor */
SLotto newLottery(int initQuantum);

/* Cleanup */
void freeSchedLottery(SLotto * oldLotto);

/* Scheduler Functions */
TLNodeRef getNextNode(SLotto * _lotto);

/* Timer Manipulations */
void setupTimer(int timerQuantum);
void stopTimer(SLotto * _lotto);
void startTimer(SLotto * _lotto);