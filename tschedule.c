/**
 * tSchedule
 *     a simple user-space thread scheduler
 *     programming assingment 2 for CS111 @ UCSC
 *     Spring 2013
 *
 *     Authors: Konstantin Litovsky, Tyler Esser, Andrew Bao, and Nick Wood
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

void thread_utils_init();
void thread_stack_init(jmp_buf *env, int size);

sigjmp_buf env[2];
int test_thread(void);
int thread = 0;
void thread_exit(int);

/* Main application starting point */
int main(void){

	printf("Main starting\n");
	printf("Main calling thread_create\n");
	
	thread_utils_init();
	thread_create(&test_thread);

	printf("Main returned from thread_create\n");
	
	while(1){
		printf("Main calling thread_yield\n");
		thread_yield();
		printf("Main returned from thread_yield\n");
	}
	thread_exit(0);
}

/* A test thread to run */
int test_thread(void){
	printf("In test_thread\n");
	
	/* Thread alternation loop */
	while(1){
		printf("Test thread calling thread_yield.\n");
		thread_yield();
		printf("Test thread returned from thread_yield\n");
	}
	thread_exit(0);
}

/* yield for another thread */
int thread_yield(){

	int old_thread = thread;
	
	thread = 1 - thread;
	
	printf("Thread %d yielding to %d\n", old_thread, thread);
	
	/**
	 * Figure out whether we got here via thread_yield, or
	 *	longjmp
	 */
	if(sigsetjmp(env[old_thread], 1) == 0){
		/* thread yield: switch to other thread */
		printf("Thread %d calling siglongjmp to restart thread %d\n", old_thread, thread);
		siglongjmp(env[thread], 1);
	}
	else{
		printf("Returned to thread %d\n", thread);
	}
}

/* Create a thread */
int thread_create(int (*thread_function)(void)) {

	int newthread = 1-thread;
	
	printf("Thread %d in thread_create\n", thread);
	printf("Thread %d calling sigsetjmp\n", thread);
	
	/* Save the context of this thread and start the new thread */
	if(sigsetjmp(env[newthread], 1) != 0) {
		/**
		 * If we got here via longjmp, then this thread just started
		 * running
		 */
		printf("Starting thread %d\n", thread);
		
		printf("Thread %d calling thread function\n", thread);
		
		(*thread_function)();
	}
	
	/**
	 * If we get here, we just started the new thread, but it hasn't run yet
	 * So set up its stack and return
	 */
	thread_stack_init(&env[newthread], 1000);
	printf("Thread %d back in thread_create\n", thread);
}

void thread_exit(int status) {
	printf("Thread %d exiting\n", thread);
}