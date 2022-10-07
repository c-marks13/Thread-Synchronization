# CS441/541 Synchronization Project

## Author(s):

Connor Marks

## Date:

4/28/22

## Description:

This is a program that solves and creates the most efficient solution to the intersection located in Smallville, WI. Threads are programmed as cars and semaphores are used to synchronize the intersection and make it as efficient as possible. The threads will approach from a random direction and have a destination direction. The threads (cars) will continue approaching and leaving the intersection as long as the program is alive. When they approach from the direction they wait for the proper semaphore to go through the intersection. Parameters for the program are gathered through the command line, that is how long the main thread lives and the number of cars (threads).

## How to build the software

The included Makefile is used to build (compile and link) this software. It can be used as follows:
- To build the software, run "make" from the command line.
- To clean the directory, run "make clean" from the command line.

## How to use the software

To use the software after building it, simply type ./stoplight followed by the set of parameters. All the parameters data types should be ints and in the following order:
- Sleep Time: This parameter is how long the main thread will sleep and how long the cars will run through the intersection.
- Number of Cars: The number of allocated threads (cars) that will be going/driving through the intersection


## How the software was tested

Because the results produced are random and will be slightly different each time I ran a few tests where I tweaked the parameters and traced through the output of the program to make sure it was running correctly.

To make sure that the Sleep Time and Number of car parameters were working correctly I simply changed these parameters and timed the program as well as observed the output making sure the car id was never greater than the parameter passed in for number of cars.

To make sure that the synchronization was working I traced the output of a few different tests on the program. I first ran small test cases where the car number was small. When I ran these tests I made sure that cars were turning the right way depending on their approach and destination direction, as well as changing state appropriately . I also ran larger cases with more cars to make sure the synchronization was working. This was harder to tell but slowly tracing through the output and writing on a white board the cars movement I could tell that the conditions for this intersection were satisfied. By doing this I was able to see that no car was in the same "tile" as another car so no accidents were caused, and no deadlock was caused because after many tests there was never a point where no car could advance.


## Known bugs and problem areas

No known bugs and problem areas at the moment
