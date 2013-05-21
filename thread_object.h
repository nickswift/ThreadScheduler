/**
 * Created: thread_object.h
 * PROGRAMMING ASSIGNMENT 2
 * CMPS 111 Spring 2013
 * Authors: Andrew Bao, Konstantin Litovskiy, Tyler Esser & Nick Wood
 */
#if !defined(_THREADOBJECT_H_INCLUDE_)
#define _THREADOBJECT_H_INCLUDE

typedef struct ThreadObject	* TORef;

/* constructor */
TORef newThread(ucontext_t initCtx, int initID, int initPriority);

/* destructor */
void freeThread(TORef T);

/* accessors */
ucontext_t getContext(TORef T);
int getID(TORef T);
int getPriority(TORef T);

#endif