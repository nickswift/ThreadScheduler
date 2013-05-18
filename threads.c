//
//  threads.c
//  
//
//  Created by Scott Brandt on 5/6/13.
//
//

#include <stdio.h>
#include <stdlib.h>

#define _XOPEN_SOURCE
#include <ucontext.h>

static ucontext_t ctx[3];

static void test_thread(void);
static int thread = 0;
void thread_exit(int);

// This is the main thread
// In a real program, it should probably start all of the threads and then wait for them to finish
// without doing any "real" work
int main(void) {
    printf("Main starting\n");
    
    printf("Main calling thread_create\n");

    // Start one other thread
    thread_create(&test_thread);
    
    printf("Main returned from thread_create\n");

    // Loop, doing a little work then yielding to the other thread
    while(1) {
        printf("Main calling thread_yield\n");
        
        thread_yield();
        
        printf("Main returned from thread_yield\n");
    }

    // We should never get here
    exit(0);
    
}

// This is the thread that gets started by thread_create
static void test_thread(void) {
    printf("In test_thread\n");

    // Loop, doing a little work then yielding to the other thread
    while(1) {
        
        printf("Test_thread calling thread_yield\n");
        
        thread_yield();
        
        printf("Test_thread returned from thread_yield\n");
    }
    
    thread_exit(0);
}

// Yield to another thread
int thread_yield() {
    int old_thread = thread;
    
    // This is the scheduler, it is a bit primitive right now
    thread = 1-thread;

    printf("Thread %d yielding to thread %d\n", old_thread, thread);
    printf("Thread %d calling swapcontext\n", old_thread);
    
    // This will stop us from running and restart the other thread
    swapcontext(&ctx[old_thread], &ctx[thread]);

    // The other thread yielded back to us
    printf("Thread %d back in thread_yield\n", thread);
}

// Create a thread
int thread_create(int (*thread_function)(void)) {
    int newthread = 1-thread;
    
    printf("Thread %d in thread_create\n", thread);
    
    printf("Thread %d calling getcontext and makecontext\n", thread);

    // First, create a valid execution context the same as the current one
    getcontext(&ctx[newthread]);

    // Now set up its stack
    ctx[newthread].uc_stack.ss_sp = malloc(8192);
    ctx[newthread].uc_stack.ss_size = 8192;

    // This is the context that will run when this thread exits
    ctx[newthread].uc_link = &ctx[thread];

    // Now create the new context and specify what function it should run
    makecontext(&ctx[newthread], test_thread, 0);
    
    printf("Thread %d done with thread_create\n", thread);
}

// This doesn't do anything at present
void thread_exit(int status) {
    printf("Thread %d exiting\n", thread);
}