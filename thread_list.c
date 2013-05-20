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
typedef struct ThreadList {
	/* Number of tickets present in the list */
	int ticketCount;
	/* Number of threads in the list */
	int threadCount;
	/* Pointers to first and last elements */
	struct ThreadListNode *front;
	struct ThreadListNode *back;
} ThreadList;

typedef struct ThreadListNode {
	/* pointer to data for the node */
	void *data;
	/* tickets in this node */
	int tickets;
	/* next node on the list */
	struct ThreadListNode * next;
} ThreadListNode;

/* Constructors */
TLRef newThreadList(void){
	TLRef _list 		= malloc(sizeof(ThreadList));
	_list->threadCount 	= 0;
	_list->ticketCount 	= 0;
	_list->front 		= NULL;
	_list->back 		= NULL;
	return(_list);
}

TLNodeRef newThreadListNode(void *initData, int initTickets){
	/* Allocate memory for the new node */
	TLNodeRef _node = malloc(sizeof(ThreadListNode));

	/* Set node data values */
	_node->data = initData;
	_node->next 	= NULL;
	_node->tickets 	= initTickets;

	return(_node);
}

/* Destructors */
/* Forward declaration to allow use in deconstructors*/
TLNodeRef popThread(TLRef L); 

void freeThreadList(TLRef * pL){
	if(pL != NULL && *pL != NULL){
		/* Free elements on the list */
		TLNodeRef tmpNode = popThread(*pL);

		while(tmpNode != NULL){
			freeThreadListNode(&tmpNode); /* free node */
			tmpNode = popThread(*pL); /* get next node */
		}

		/* now, free this list */
		(*pL)->front = NULL;
		(*pL)->back = NULL;
		free(*pL);
		*pL = NULL;
	}
}

void freeThreadListNode(TLNodeRef * pN){
	/* Make sure we're not passing a null pointer */
	if(pN != NULL && *pN != NULL){
		/* Free memory at given address and destroy the pointer */
		free((*pN)->next);
		free((*pN)->data);
		free(*pN);
		*pN = NULL;
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
 * Returns the node at index in the list
 * Assuming front is element 0
 */
TLNodeRef getNodeAtIndex(TLRef L, int index){
	/* Error conditions */
	if(L == NULL){
		printf("Error: null List reference\n");
		exit(1);
	}
	if(index < 0 || index > L->threadCount){
		printf("Error: given index out of range.\n");
		exit(1);
	}
	
	TLNodeRef current = getFront(L);
	while(current != NULL && index > 0)
	{
		current = current->next;
		--index;
	}
	
	return(current);	
}

/**
 * Choose a Node based on ticket count
 * within the list's range of lottery tickets
 */
TLNodeRef getNodeAtTicket(TLRef L, int numTickets){
	/* Error conditions */
	if(L == NULL){
		printf("Error: null List reference\n");
		exit(1);
	}
	if(numTickets < 0 || numTickets > L->ticketCount){
		printf("Error: given ticket index out of range.\n");
		exit(1);
	}

	/* Set up walk */
	int tmpIndex 		= numTickets;
	TLNodeRef current 	= getFront(L);

	/* Walk down the list */
	while(current != NULL && tmpIndex >= 0){
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
void insertNode(TLRef L, TLNodeRef N){
	/* Insert node on the list */
	if(L->front == NULL){
		L->front 	= N;
		L->back 	= N;
	}
	else{
		L->back->next 	= N;
		L->back 		= N;
	}

	/* Add node tickets to ticket count */
	L->ticketCount += N->tickets;
	L->threadCount++;
}

/**
 * Pop a thread off the back of the list and return
 * the reference to that node.
 */
TLNodeRef popThread(TLRef L){
	TLNodeRef tmpNode = NULL;
	if(L->front != NULL){
		tmpNode = L->front;
		if(L->threadCount == 1)
			L->back = NULL;
		L->front = L->front->next;
	}

	L->ticketCount -= tmpNode->tickets;
	L->threadCount--;

	return(tmpNode);
}

/* removes node from list */
TLNodeRef removeNode(TLRef L, int index){
	/* Error conditions */
	if(L == NULL){
		printf("Error: null List reference\n");
		exit(1);
	}
	if(index < 0 || index >= L->threadCount){
		printf("Error: given index out of range.\n");
		exit(1);
	}
	TLNodeRef tmp = L->front;
	TLNodeRef target = L->front;

	if(target != NULL){
		/* searching list for the predecesor to the thread to be deleted */
		while(index > 0){
			tmp = target;
			target = target->next;
			--index;
		}
		if(tmp != target) {
			tmp->next = target->next;
			target->next = L->front;
			L->front = target;
		}
		tmp = popThread(L);
	}
	
	return(target);
}

int isListEmpty(TLRef L){
	return !(L->threadCount);
}

/* List Operations */
void printList(TLRef L){
	TLNodeRef current = L->front;
	int index = 0;
	while(current != NULL){
		printf("Index: %d | Tickets: %d \n", index, current->tickets);
		++index;
		current = current->next;
	}
	printf("\nNumber Of Nodes: %d\n", L->threadCount);
	printf("Total Tickets: %d\n\n", L->ticketCount);

}

 int testThreadList() {
	int testData = 21;
	int i;
	TLRef f = newThreadList();
	
	for(i = 0; i < 15; ++i)
		insertNode(f,newThreadListNode(&testData, i+1));
		
	printList(f);
	
	if(!isListEmpty(f))
		printf("List is not Empty.\n\n");
		
	popThread(f);
	printList(f);
	
	removeNode(f,0);
	printList(f);
	
	removeNode(f, 10);
	printList(f);
	
	int indexTest = 3;
	printf("%d tickets: %d\n", indexTest, getNodeAtIndex(f,indexTest)->tickets);
	
	int ticketTest = 104;
	printf("%d tickets: %d\n", ticketTest, getNodeAtTicket(f,ticketTest)->tickets);
 
	return 0;
 }

