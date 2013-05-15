/**
 * Modified: tschedule.c
 * PROGRAMMING ASSIGNMENT 2
 * CMPS 111 Spring 2013
 * Authors: Andrew Bao, Konstantin Litovskiy, Tyler Esser & Nick Wood
 */
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

void thread_yield(void);
void test_thread(void);
void thread_create(void (*thread_function)(void));
void thread_exit(int status);
