#include <signal.h>
#include <stdio.h>
#include <sys/time.h>

/* Global variables */
static volatile int waiting = 3; /* volatile to prevent caching issues  */

/* Function Declarations    */
void handleOnce(int);
void handleCont(int);

int main(void) {
    /* zero initializers for structures */
    struct itimerval timer_once = {0};
    struct itimerval timer_cont = {0};
    struct sigaction handler_once = {0};
    struct sigaction handler_cont = {0};

    /* an interval of 0 prevents reinitialization */
    timer_once.it_value.tv_sec = 2;

    /* timer signals every thirty seconds   */
    timer_cont.it_interval.tv_sec = 4;
    timer_cont.it_value.tv_sec = 4;

    handler_once.sa_handler = (*handleOnce);
    handler_cont.sa_handler = (*handleCont);

    /* setting the timer signal handlers before the timers  */
    sigaction(SIGVTALRM, &handler_once, NULL);
    sigaction(SIGALRM, &handler_cont, NULL);

    /* timer only counts when process is running, emits a SIGVTALRM */
    setitimer(ITIMER_VIRTUAL, &timer_once, NULL);

    /* timer uses actual system clock, emits a SIGALRM  */
    setitimer(ITIMER_REAL, &timer_cont, NULL);

    while(waiting > 0); /* avoid exiting and stopping timers */

    return 0;
}

void handleOnce(int sig) {
    printf("This timer only triggers once. SIGVTALRM is %d\n", sig);
    fflush(stdout);
}

void handleCont(int sig) {
    printf("This timer continues forever. SIGALRM is %d\n", sig);
    printf("But we'll stop after %d more timer interval(s).\n", --waiting);
    fflush(stdout);
}

