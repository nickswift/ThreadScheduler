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