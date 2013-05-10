/**
 * Thread List
 * A linked list containing the number of lottery tickets,
 * as well as identifying information regarding the threads
 * being kept track of.
 */

#include <stdio.h>
#include <stdlib.h>
#include "thread_list.h"
 
/* Struct declarations */
typedef struct ThreadListNode {
	/* tickets in this node */
	int tickets;
	/* next node on the list */
	struct ThreadListNode * next;
} ThreadListNode;

typedef struct ThreadList {
	
	/* Number of tickets present in the list */
	int ticketCount;
	struct ThreadListNode * front;
	struct ThreadListNode * back;
	
	/* Walk helpers */
	struct ThreadListNode * current;
	
} ThreadList;
 
/* Constructors */
TLNodeRef newThreadListNode(void){
	/* Allocate memory for the new node */
	TLNodeRef _node = malloc(sizeof(ThreadListNode));
	
	/* Set node data values */
	_node->tickets 	= 0;
	_node->next 	= NULL;
	
	return(_node);
}

TLRef newThreadList(void){
	TLRef _list 		= malloc(sizeof(ThreadList));
	_list->ticketCount 	= 0;
	_list->front		= NULL;
	_list->back			= NULL;
	_list->current		= NULL;
	
	return(_list);
}

/* Destructors */
void freeThreadListNode(TLNodeRef * pN){
	/* Make sure we're not passing a null pointer */
	if(pN != NULL && *pN != NULL){
		/** 
		 * Free memory at given address and 
		 * destroy the pointer 
		 */
		free(*pN);
		*pN = NULL;
	}
}
void freeThreadList(TLRef * pL){
	if(pL != NULL && *pL != NULL){
		free(*pL);
		*pL = NULL;
	}
}

/* Accessors */
TLNodeRef getFront(TLRef L){
	/* Error conditions */
	if(L == NULL){
		printf("Error: null List reference\n");
		exit(1);
	}
	if(L->front == NULL){
		printf("Error: Calling getFront() on an empty list\n");
		exit(1);
	}
	
	return(L->front);
}

/**
 * Choose a thread corresponding to an index 
 * within the list's range of lottery tickets
 */
TLNodeRef getNodeAtIndex(TLRef L, int i){
	// Error conditions
	if(L == NULL){
		printf("Error: null List reference\n");
		exit(1);
	}
	if(i < 0 || i > L->ticketCount){
		printf("Error: given index out of range.");
		exit(1);
	}
	
	/* Set up walk */
	int tmpIndex 		= 0;
	int walkIndexBuffer = 0;
	L->current 			= getFront(L);
	
	/* Walk down the list */
	while(L->current != NULL && tmpIndex < i){
		/** 
		 * increment tmpIndex, and walk forward 
		 * if the walk index buffer equals current's ticket count
		 */
		tmpIndex++;
		walkIndexBuffer++;
	
		if(walkIndexBuffer >= L->current->tickets){
			walkIndexBuffer = 0;
			L->current = L->current->next;
		}
	}
	
	return(L->current);
}

/* Mutators */
void insertThread(TLRef L, TLNodeRef N){
	
	/* Insert node on the list */
	if(L->front == NULL){
		L->front 	  = N;
		L->back  	  = N;
	}
	else{
		L->front->next  = N;
		L->front 		= N;
	}
	
	/* Add node tickets to ticket count */
	L->ticketCount += N->tickets;
}

/* List Operations */
void printList(TLRef L){
	
}