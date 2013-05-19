/**
 * Created: thread_list.h
 * PROGRAMMING ASSIGNMENT 2
 * CMPS 111 Spring 2013
 * Authors: Andrew Bao, Konstantin Litovskiy, Tyler Esser & Nick Wood
 *
 * thread_list.h: Thread List
 * A linked list containing the number of lottery tickets,
 * as well as identifying information regarding the threads
 * being kept track of.
 */

#ifndef _THREADLIST_H_INCLUDE
#define _THREADLIST_H_INCLUDE

/* Exported Types */
typedef struct ThreadList *TLRef;
typedef struct ThreadListNode *TLNodeRef;

/* Constructors */
TLRef newThreadList(void);
TLNodeRef newThreadListNode(void *initData, int initTickets);

/* Destructors */
void freeThreadList(TLRef *pL);
void freeThreadListNode(TLNodeRef *pN);

/* Accessors */
TLNodeRef getFront(TLRef L);
TLNodeRef getNodeAtIndex(TLRef L, int index);
TLNodeRef getNodeAtTicket(TLRef L, int numTickets);
int isListEmpty(TLRef L);

/* Mutators */
void insertNode(TLRef L, TLNodeRef N);
void removeNode(TLRef L, int index);

#endif
