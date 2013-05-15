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

#if !defined(_THREADLIST_H_INCLUDE_)
#define _THREADLIST_H_INCLUDE
#endif

/* Exported Types */
typedef struct ThreadList 		* TLRef;
typedef struct ThreadListNode 	* TLNodeRef;

/* Constructors */
TLRef newThreadList(void);
TLNodeRef newThreadListNode(int initTickets, ThreadObject newThread);

/* Destructors */
void freeThreadList(TLRef * pL);
void freeThreadListNode(TLNodeRef * pN);

/* Accessors */
TLNodeRef getFront(TLRef L);
TLNodeRef getNodeAtIndex(TLRef L, int i);

/* Mutators */
void insertThread(TLRef L, TLNodeRef N);
void setThreadTickets(TLNodeRef N, int _tickets);
void removeThreadNode(TLRef L, int _threadID);
TLNodeRef popThread(TLRef L);

/* List Operations */

void printList(TLRef L);
