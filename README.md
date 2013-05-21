SlugCorp
========
*Why solve it, when you can Slug it? &trade;*

ThreadScheduler
---------------

A simple user-space thread scheduler

## V0.1
> The initial version of the thread scheduler is a restatement of
> the code given to us by Prof. Brandt. It still doesn't work, but when
> it does, we should be able to run it and play around with it before the 
> actual assignment is posted.

## V0.2
> thread_list is a linked list which will be used to make the lottery ticket
> system work. Currently, the list functions as a basic list, but I think 
> we're going to need it because while the array Brandt gave us in the assignment
> is needed to make the thread context switching work, we're using the linked list
> to keep track of lottery tickets for the main scheduling subroutines.
>
> Also, the current make targets are as follows:
> 
> 1. main: the main program we're going to turn in
> 2. test: the thread list testing program
> 3. clean: git rid o' dat shit

## V0.3
> Went scorched earth and redid the entire master branch

### Note on deleting lists
> I modified the way lists get deleted and added to. One adds data to a list by calling 
> insertData(TLRef L, void *data, int tickets), and a node is automatically created
> and inserted into the list.
>
> To delete a list, you must first clear it out using clearList(TLRef L). This function
> frees every node on the list in preparation for the list to be deleted. After calling this
> function, you can then call freeList(TLRef L) to finish the job.

### Notes on refactor
I had to make a few changes to some of the files so that they would work with my new list
First: I changed the name of the list references to the following for more clarity:

> ThreadList      -> TLRef

> ThreadListNode  -> TNRef

Second: I fixed the errors GCC was throwing with respect to scheduler.c and the_app.c

> define _XOPEN_SOURCE

> include <ucontext.h>

gets called before main() now. Also, I added threads.c's functions in stub-form to the_app.c
until we figure out what to do with them.

Also, I haven't done anything to this effect, but I'd like to pose the following concern here: 

I fail to see the use in keeping a separate "thread_object" object in addition to the list. It seems
to be something we can use thread list nodes to do. If we keep the context variable and thread ID 
inside the list, then there's nothing else we need to do. We can just invoke the context change
from a random thread by randomizing an index, selecting that random index off of the list, and 
using the resultant node reference to extract the context we want to go into after setting the timer.

## V0.4

Tyler redid most of the code comprising scheduler.c, which included a rewrite of thread_object within that 
file. This means that thread_object is now deprecated, and subject to deletion when scheduler is doing its
job.

thread_list can now be freed using a single function, freeList(TLRef *pL). This function calls clear_list()
by itself, but that function is still accessible in case one wants to clear the list without deleting it.