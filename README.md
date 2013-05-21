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
> # Note on deleting lists
>> I modified the way lists get deleted and added to. One adds data to a list by calling 
>> insertData(TLRef L, void *data, int tickets), and a node is automatically created
>> and inserted into the list.
>>
>> To delete a list, you must first clear it out using clearList(TLRef L). This function
>> frees every node on the list in preparation for the list to be deleted. After calling this
>> function, you can then call freeList(TLRef L) to finish the job.