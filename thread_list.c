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

/* constructors */
TLRef newThreadList(void)
{
    /* Make the list */
    TLRef _list         = malloc(sizeof(struct ThreadList));
    
    _list->back         = NULL;
    _list->front        = NULL;
   
    /* Setup ticket count and node count */
    _list->ticketCount  = 0;
    _list->nodeCount    = 0;
    return _list;
}

/* A single node insertion wrapper to make this list easier to use */
void insertData(TLRef L, int id, void * data, int tickets)
{
    TNRef _node     = malloc(sizeof(struct ThreadListNode));
    
    _node->data     = data;
    _node->tickets  = tickets;
    _node->threadID = id;
    _node->next     = NULL;
    
    if(L->front == NULL){
        // Set front and back to our new node
        L->front = _node;
        L->back  = _node;
    }else{
        // Put this node on the end.
        L->back->next  = _node;
        L->back        = _node;
    }
    
    /* Add ticket number to list head */
    L->ticketCount += tickets;
    L->nodeCount++;
}

/* Deallocate a node */
void freeNode(TLRef L, TNRef *pN)
{
	/* Delete the node */
    if(*pN != NULL){
    	TNRef N         = *pN;
    	L->ticketCount -= N->tickets;
    	L->nodeCount--;
    	
        free(*pN);
        *pN = NULL;
    }
}

/* excise a node */
void exciseNode(TLRef L, TNRef N)
{
    /* get the current node, set up previous */
    TNRef tmp     = L->front;
    TNRef tmpPrev = tmp;
    
    while(tmp != NULL && tmp != N){
    	tmpPrev = tmp;
    	tmp     = tmp->next;
    }
    if(tmp == NULL)
    	return;
    
    /* patch up old connections */
    tmpPrev->next = tmp->next;
    
    freeNode(L, &N);
}

/* Clear the list */
void clearList(TLRef L){
    printf("\n\nClearing the list\n\n");
    TNRef tmpNode;
    
    /* do the following until L is empty */
    while(!isListEmpty(L)){   
        /* Get back, move list-back node 
            pointer forward */     
        tmpNode  = L->front;
       	L->front = L->front->next;
        
        /* check for list front */
        if(L->front == L->back){
        	L->back = NULL;
        }
        
        /* free the observed node */
		freeNode(L, &tmpNode);
    }
    /* free the pointer when we're done */
    tmpNode = NULL;
}

/* Deallocate a list */
void freeList(TLRef *pL)
{
    clearList(*pL);
    
    if(*pL != NULL){
        free(*pL);
        *pL = NULL;
    }
}

/* check list emptiness */
int isListEmpty(TLRef L)
{
	return (L->ticketCount <= 0);
}
int getTickets(TLRef L)
{
    return L->ticketCount;
}
int getSize(TLRef L)
{
    return L->nodeCount;
}

/* get node data by id */
void* getID(TLRef L, int ID)
{
    /* get first node */
    TNRef tmpNode = L->front;
    
    /* find the desired ID in the list */
    while(tmpNode != NULL && ID != tmpNode->threadID){
        tmpNode = tmpNode->next;
    }
    return tmpNode->data;
}
/* returns # of tickets at id*/
int getID_tickets(TLRef L, int ID)
{
    /* get first node */
    TNRef tmpNode = L->front;
    
    /* find the desired ID in the list */
    while(tmpNode != NULL && ID != tmpNode->threadID){
        tmpNode = tmpNode->next;
    }
    return tmpNode->tickets;
}

void removeID(TLRef L, int ID)
{
	/* get first node */
    TNRef tmpNode = L->front;
    TNRef removeNode;
	
    /* find the desired ID in the list */
    while(tmpNode->next != NULL && ID != tmpNode->next->threadID){
        tmpNode = tmpNode->next;
    }
	
	removeNode = tmpNode->next;
	tmpNode->next = tmpNode->next->next;
	
    freeNode(L, &removeNode);
}

/* Print the list */
void printList(TLRef L)
{
    /* get first node */
    TNRef tmpNode = L->front;
    printf("\n\n");
    
    /* print all nodes */
    while(tmpNode != NULL){
        printf("(%d)->", tmpNode->threadID);
        tmpNode = tmpNode->next;
    }
    printf("[NULL]\n\n");
    return;
}

/**
 * Choose a thread corresponding to a ticket
 * within the list's range of lottery tickets
 */
TNRef getNodeAtTicket(TLRef L, int winning_ticket)
{
	// Error conditions
	if(L == NULL){
		printf("Error: null List reference\n");
		exit(1);
	}
	if(winning_ticket < 0 || winning_ticket > L->ticketCount){
		printf("Error: given index out of range.");
		exit(1);
	}

	/* Set up walk */
	int tmpIndex  = winning_ticket;
	TNRef current = L->front;

	/* Walk down the list */
	while(current != NULL && tmpIndex > 0){
		/** 
		 * decrement tmpIndex with the number of tickets at each node
		 * if tmpIndex remains above 0, move set current to the next node. 
		 */
		tmpIndex -= current->tickets;
		if(tmpIndex > 0){
			current = current->next;
		}
	}

	return(current);
}