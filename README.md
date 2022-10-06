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

## Special Section

### Before Coding

1. Consider first, a single intersection:
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br /><br />(a) Assume that the residents of Smallville are exceptional and follow the old (and widely ignored) convention that whoever arrives at the intersection first proceeds first. Using the language of synchronization primitives describe the way this intersection is controlled. In what ways is this method suboptimal?
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br /><br />One way that this could be suboptimal is that there could be a long line of cars from one direction. For example a handful of cars could arrive from north but then after one arrives from the west, the car from the west would have to wait for a while before it gets a chance to enter the intersection even though it may not even collide with the north cars. Overall there would just be a long queue that only allows the first in line car to enter the intersection. To code this we would only need one semaphore that controls the intersection and all the cars have to wait for that.
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br /><br />(b) Now, assume that the residents of Smallville are like most people and do not follow the convention described above. In what one instance can this four-way-stop intersection produce a deadlock? (It will be helpful to think of this in terms of the model we are using instead of trying to visualize an actual intersection).
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br /><br />If the smallville citizens did not follow the convention described it could result in a deadlock. It would result in a deadlock if 4 cars entered the intersection and none of them are going right, they all are either going straight or left. In this instance, each car would be waiting for one another and no progress would be made.

2. Consider next, a two intersection situation:
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br /><br />(a) Assume that the bridge between the two intersections had space for at most N cars in any one direction. In what instances can this produce deadlock? Provide at least 4 specific, distinct examples that use a path crossing the bridge. Include in those examples what you would consider the worst case scenario.
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br /><br />Similarly to the above example. It will cause a deadlock if 4 cars in either the 1 or 2 intersection enter at the same time and none of them are going right. Another specific example is if a car is coming from the north 2 and they are trying to go right but the bridge is full and the 1 intersection is not moving. This will also cause a deadlock. One more example of deadlock in the bridge is if there are always cars going north and south through the intersection (busiest intersection in the world!) Cars on the bridge would get stuck causing a deadlock.

### After Coding
1. Describe your solution to the problem (in words, not in code).
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br /><br />The solution I came up with incorporates 9 semaphores. 4 semaphores for each section in the intersection, 4 semaphores 4 each direction, and a counting semaphore for the number of cars in the intersection. The 4 semaphores for each "section" of the intersection are used to avoid crashes. The 4 direction semaphores are used so only one car from one direction is in the intersection. That is if two cars from the north are waiting, the 2nd car can not enter the intersection until the car in front of it exits. The counting semaphore is used to avoid deadlock.

2. Describe how your solution meets the goals of this part of the project, namely (each in a separate
section):
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br /><br />How does your solution avoid deadlock?
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br /><br />My solution avoids deadlock mainly through the intersection_count semaphore. A deadlock will occur if 4 cars enter the intersection and none of them are going right. After a car is redirected it will have to wait for certain semaphores depending on the direction it is going. So to avoid 4 non right turning cars entering the intersection I have a semaphore count set to 3 so only 3 straight/left cars can enter into the intersection at one time. A right car can enter as long as it is up next and the car in front of it has left the intersection and the first square in front of it is open because it will get in and out.
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br /><br />How does your solution prevent accidents?
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br /><br />My solution will prevent accidents because no car can enter the same tile/space at one time. This is the case because cars are forced to wait up those certain tiles depending on the direction they are waiting due to the synchronization of the ne, nw, se and sw semaphores. These are also binary semaphores so this will result in only one car entering it at one time.
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br /><br />How does your solution improve traffic flow?
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br /><br />My solution improves traffic flow because cars from every direction will be going constantly. The intersection will be very busy but because the synchronization through semaphores is correct and the problem needs are met this will be the most efficient solution.
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br /><br />How does your solution preserve the order of cars approaching the intersection?
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br /><br />How is your solution “fair”?
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br /><br />How does your solution prevent “starvation”?
