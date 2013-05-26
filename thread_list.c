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

/* The list nodes */
struct ThreadListNode {
    void * data;
    struct ThreadListNode * next;
    
    /* Lottery information */
    int threadID;
    int tickets;
} ThreadListNode;

/* The list proper */
struct ThreadList{
    struct ThreadListNode * front;
    struct ThreadListNode * back;
    
    /* Lottery information */
    int numTickets;
    int numNodes;
} ThreadList;

/* constructors */
TLRef newThreadList(void){
    /* Make the list */
    TLRef _list         = malloc(sizeof(struct ThreadList));
    _list->front        = NULL;
    _list->back         = NULL;
    
    /* Setup ticket count and node count */
    _list->numTickets   = 0;
    _list->numNodes     = 0;
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
        L->front->next  = _node;
        L->front        = _node;
    }
    
    /* Add ticket number to list head */
    L->numTickets += tickets;
    L->numNodes++;
}

/* Deallocate a node */
void freeNode(TNRef *pN){
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
        printf("Removing a node\n");
        
        /* check for list front */
        if(L->back == L->front)
            L->front = NULL;
            
        /* Get back, move list-back node 
            pointer forward */     
        tmpNode = L->back;
        L->back = L->back->next;
        
        /* free the observed node */
        freeNode(&tmpNode);
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
    return (L->front == NULL);
}
int getTickets(TLRef L){
    return L->numTickets;
}
int getSize(TLRef L){
    return L->numNodes;
}

/* Get data off of the front */
void* getFront(TLRef L){
    return L->front->data;
}

/* find data by given node id */
void* getID(TLRef L, int id){
    /* get first node */
    TNRef tmpNode = L->back;
    
    /* find the desired ID in the list */
    while(tmpNode != NULL && id != tmpNode->threadID){
        tmpNode = tmpNode->next;
    }
    return tmpNode->data;
}
int getID_tickets(TLRef L, int id){
	/* get first node */
    TNRef tmpNode = L->back;
    
    /* find the desired ID in the list */
    while(tmpNode != NULL && id != tmpNode->threadID){
        tmpNode = tmpNode->next;
    }
    return tmpNode->tickets;
}

/* Get data at list index */
void* getIndex(TLRef L, int index){
    int i;
    TNRef tmpNode = L->back;
    /* check range */
    if(index > getSize(L)){
        printf("Error: index for list out of range.\n");
        exit(1);
    }
    /* get the node at given index */
    for(i=1; i<index; i++){
        tmpNode = tmpNode->next;
    }
    return tmpNode->data;
}

/* Remove node by ID */
void removeID(TLRef L, int id){
	TNRef tmpNode = L->back;
	TNRef prev    = NULL;
	
	/* find the desired ID in the list */
    while(tmpNode != NULL && id != tmpNode->threadID){
    	prev	= tmpNode;
        tmpNode = tmpNode->next;
    }
    /* Patch up connections */
    prev->next = tmpNode->next;
    
    /* Free the node */
	freeNode(&tmpNode);
}

/* Print the list */
void printList(TLRef L){
    /* get first node */
    TNRef tmpNode = L->back;
    printf("\n\nWalking a list.\n\n");
    
    /* print all nodes */
    while(tmpNode != NULL){
        printf("Visiting a node. Tickets: %d\n", tmpNode->tickets);
        tmpNode = tmpNode->next;
    }
}

/**
 * The test application
 * uncomment to test the list
 */
/* int main(void){
    printf("\nThis is a test of our list\n\n");
    printf("Creating the list...\n");
    
    TLRef mylist = newThreadList();
    
    int d1 = 10;
    int d2 = 20;
    int d3 = 30;
    
    insertData(mylist, 1, &d1, 10);
    insertData(mylist, 2, &d2, 15);
    insertData(mylist, 3, &d3, 20);
      
    printList(mylist);
    
    int *data = getID(mylist, 3);
    
    printf("\nFound node: %d\n", *data);

    printf("Freeing the list...\n");
    
    freeList(&mylist);
    printf("\n\nDone!\n\n");
    return 0;
} */
