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

#ifndef _LIST_H_INCLUDE
#define _LIST_H_INCLUDE
 
/* Define struct references */
typedef struct ThreadList       * TLRef;
typedef struct ThreadListNode   * TNRef;

/* Constructors */
TLRef newThreadList(void);
void insertData(TLRef L, void * data, int tickets);

/* Destructors */
void freeList(TLRef *pL);
void freeNode(TNRef *pN);

/* check for list emptiness */
int isListEmpty(TLRef L);

/* get number of tickets */
int getTickets(TLRef L);

/* get list size */
int getSize(TLRef L);

/* Get node by ticket number and list index */
TNRef getNode(TLRef L, int tIndex);
TNRef getNodeAtIndex(TLRef L, int index);

/* I'm using this method to seperate making the list empty from 
 * freeing it.
 */
void clearList(TLRef L);

/* Look at the contents */
void printList(TLRef L);

#endif