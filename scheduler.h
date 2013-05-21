/**
 * Modified: scheduler.h
 * PROGRAMMING ASSIGNMENT 2
 * CMPS 111 Spring 2013
 * Authors: Andrew Bao, Konstantin Litovskiy, Tyler Esser & Nick Wood
 *
 * Scheduler.h
 */

#ifndef _SCHEDULER_H_INCLUDE
#define _SCHEDULER_H_INCLUDE

/* Functions Declarations */
int thread_create(void (*thread_func)(void), int priority);
void thread_yield();
void thread_exit();
int numThreads();

#endif

