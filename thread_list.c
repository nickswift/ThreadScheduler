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
TLRef newThreadList(void){
    /* Make the list */
    TLRef _list         = malloc(sizeof(struct ThreadList));
    
    _list->back         = NULL;
    _list->front        = NULL;
   
    /* Setup ticket count and node count */
    _list->ticketCount = 0;
    _list->nodeCount   = 0;
    return _list;
}

/* A single node insertion wrapper to make this list easier to use */
void insertData(TLRef L, int id, void * data, int tickets){

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
void freeNode(TLRef L, TNRef *pN){
	/* Decrement number of tickets in the list */
	TNRef tmp = *pN;
	L->ticketCount -= tmp->tickets;

	/* Delete the node */
    if(*pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}

/* Clear the list */
void clearList(TLRef L){
    printf("\n\nClearing the list\n\n");
    TNRef tmpNode;
    
    /* do the following until L is empty */
    while(!isListEmpty(L)){
    
        /* check for list front */
        if(L->front == L->back){
        	L->back = NULL;
        }
            
        /* Get back, move list-back node 
            pointer forward */     
        tmpNode  = L->front;
        L->front = L->front->next;
        
        /* free the observed node */
        freeNode(L, &tmpNode);
    }
    /* free the pointer when we're done */
    tmpNode = NULL;
}

/* Deallocate a list */
void freeList(TLRef *pL){
    clearList(*pL);
    if(*pL != NULL){
        free(*pL);
        *pL = NULL;
    }
}

/* check list emptiness */
int isListEmpty(TLRef L){
	return (L->ticketCount <= 0);
}
int getTickets(TLRef L){
    return L->ticketCount;
}
int getSize(TLRef L){
    return L->nodeCount;
}

/* get node data by id */
void* getID(TLRef L, int ID){
    /* get first node */
    TNRef tmpNode = L->front;
    
    /* find the desired ID in the list */
    while(tmpNode != NULL && id != tmpNode->threadID){
        tmpNode = tmpNode->next;
    }
    return tmpNode->data;
}

void removeID(TLRef L, int ID){
	/* get first node */
    TNRef tmpNode = L->front;
    
    /* find the desired ID in the list */
    while(tmpNode != NULL && id != tmpNode->threadID){
        tmpNode = tmpNode->next;
    }
    
    freeNode(L, &tmpNode);
}

/* Print the list */
void printList(TLRef L){
    /* get first node */
    TNRef tmpNode = L->front;
    printf("Walking a list.\n");
    
    /* print all nodes */
    while(tmpNode != NULL){
        printf("(%d)->", tmpNode->threadID);
        tmpNode = tmpNode->next;
    }
    printf("NULL");
    return;
}

/*int main(void){
	
	printf("Testing list:\n\n");
	
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	
	TLRef _list = newThreadList();
	
	insertData(_list, 1, &data1, 10);
	insertData(_list, 2, &data2, 15);
	insertData(_list, 3, &data3, 10);
	
	printList(_list);
	
	freeList(&_list);
	return 0;
}*/
