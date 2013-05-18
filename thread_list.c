/**
 * Created: thread_list.c
 * PROGRAMMING ASSIGNMENT 2
 * CMPS 111 Spring 2013
 * Authors: Andrew Bao, Konstantin Litovskiy, Tyler Esser & Nick Wood
 *
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
	/* Pointer for thread object */
	struct ThreadObject* thread;

} ThreadListNode;

typedef struct ThreadList {
	/* Number of tickets present in the list */
	int ticketCount;
	int threadCount;
	struct ThreadListNode *front;
	struct ThreadListNode *back;
} ThreadList;

/* Constructors */
TLNodeRef newThreadListNode(int initTickets, ThreadObject newThread){
	/* Allocate memory for the new node */
	TLNodeRef _node = malloc(sizeof(ThreadListNode));

	/* Set node data values */
	_node->tickets 	= initTickets;
	_node->next 	= NULL;
	_node->thread 	= newThread;

	return(_node);
}

TLRef newThreadList(void){
	TLRef _list 		= malloc(sizeof(ThreadList));
	_list->threadCount 	= 0;
	_list->ticketCount 	= 0;
	_list->front 		= NULL;
	_list->back 		= NULL;
	return(_list);
}

/* Destructors */
void freeThreadListNode(TLNodeRef * pN){
	/* Make sure we're not passing a null pointer */
	if(pN != NULL && *pN != NULL){
		/* Free memory at given address and destroy the pointer */
		free(pn->next);
		free(pn->thread);
		free(*pN);
		*pN = NULL;
	}
}

void freeThreadList(TLRef * pL){
	if(pL != NULL && *pL != NULL){
		/* Free elements on the list */
		TLNodeRef tmpNode = popThread(*pL);

		while(tmpNode != NULL){
			freeThreadListNode(&tmpNode); /* free node */
			tmpNode = popThread(*pL); /* get next node */
		}

		/* now, free this list */
		front = NULL;
		back = NULL;
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
	/* Error conditions */
	if(L == NULL){
		printf("Error: null List reference\n");
		exit(1);
	}
	if(i < 0 || i > L->ticketCount){
		printf("Error: given index out of range.");
		exit(1);
	}

	/* Set up walk */
	int tmpIndex 		= i;
	int walkIndexBuffer = 0;
	TLNodeRef current 	= getFront(L);

	/* Walk down the list */
	while(current != NULL && tmpIndex <= 0){
		/**
		 * decrament tmpIndex with the number of tickets at each node
		 * if tmpIndex remains above 0, move set current to the next node.
		 */
		tmpIndex -= current->tickets;
		if(tmpIndex > 0){
			current = current->next;
		}
	}

	return(current);
}

/* Mutators */
void insertThread(TLRef L, TLNodeRef N){
	/* Insert node on the list */
	if(L->front == NULL){
		L->front 	= N;
		L->back 	= N;
	}
	else{
		L->front->next 	= N;
		L->front 		= N;
	}

	/* Add node tickets to ticket count */
	L->ticketCount += N->tickets;
	L->threadCount++;
}

/* set number of lottery tickets associated with a thread */
void setThreadTickets(TLRef L, TLNodeRef N, int _tickets){
	/* remove current # of tickets from count */
	L->ticketCount -= N->tickets;

	/* Update node's tickets */
	N->tickets = _tickets;

	/* Re-Add node's tickets to ticket count */
	L->ticketCount += N->tickets;
}

/* removes node and thread from list */
void removeThreadNode(TLRef L, int _threadID){
	TLNodeRef tmp = L->front;
	TLNodeRef target = L->front;

	if(target != NULL){
		/* searching list for the predecesor to the thread to be deleted */
		while(target->next != NULL && target->next->thread->id != _threadID){
			target = target->next;
		}

		if(target->next != NULL){
			L->front = target->next;
			target->next = target->next->next;
			target->next = tmp;

			if(L->front == L->back){ L->back = target; }

			tmp = popThread(L);
		}
	}
}

bool isListEmpty(TLRef _list){
	return _list->threadCount;
}

/**
 * Pop a thread off the back of the list and return
 * the reference to that node.
 */
TLNodeRef popThread(TLRef L){
	TLNodeRef tmpNode = NULL;
	if(L->back != NULL){
		tmpNode = L->back;
		L->back = L->back->next;
	}

	L->ticketCount -= tmpNode->tickets;
	L->threadCount--;

	return(tmpNode);
}

/* List Operations */
void printList(TLRef L){
	TLNodeRef current = L->front;

	while(current != NULL){
		printf("Tickets: %d | Thread ID: &d\n\n", current->tickets, current->thread->id);
		current = current->next;
	}

}

