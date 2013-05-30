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

/* Struct Typedefs */
typedef struct ThreadObj {
    ucontext_t ctx;
    int tid;
    int tickets;
} ThreadObj;

/* Functions Declarations */
int thread_create(void (*thread_func)(void), int priority);
void thread_yield(int);
void thread_exit(void);
int numThreads(void);

/* Export file-wide globals */
int get_gbl_curr_thread(void);
TLRef get_gbl_thread_list(void);

#endif

