/**
 * Test thread scheduler code
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "thread_list.h"

int main(void){

	int i, tmptix;
	TLNodeRef tmpNode;
	
	srand(time(NULL));

	/* Make a list */
	TLRef tmpList = newThreadList();
	
	printf("\n");
	
	/* Add some nodes */
	for(i=0; i<10; i++){
		/* make new node */ 
		tmpNode = newThreadListNode();
		
		/* assign random priority (0-40) */
		tmptix = rand();
		setThreadTickets(tmpNode, tmptix%40);
		
		/* insert node on the list */
		insertThread(tmpList, tmpNode);
	}
	
	/* Print the list */
	printList(tmpList);
	
	/* Get rid of list */
	freeThreadList(&tmpList);

	return 0;	
}