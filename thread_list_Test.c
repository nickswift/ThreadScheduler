/**
 * Test thread list
 */
 
#include <stdio.h>
#include <stdlib.h>
#include "thread_list.h"
 
 void main() {
	int testData = 21;
	TlRef f = newThreadList();
	TLNodeRef n = newThreadListNode(&testData, 5);
	
	f->insertNode(n);
	
	printList(f);
 
 }