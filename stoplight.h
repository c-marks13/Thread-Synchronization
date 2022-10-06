/*
 * Connor Marks
 *
 * CS 441/541 : Synchronization Project
 */
#include "support.h"


/*****************************
 * Defines
 *****************************/

 //No Custom defines

/*****************************
 * Structures
 *****************************/

 //No Custom Structs

/*****************************
 * Global Variables
 *****************************/

//Time to live (Seconds)
int ttl = 0;

//Number of Cars
int car_num = 0;

//Number of cars (threads) in the system
int num_cars = 0;

double total_time = 0;
double min_time = 0;
double max_time = 0;
double avg_time = 0;
int a = 0;

int cross_time = 0;

//Indicate when for threads to stop processing and exit
int time_to_exit = FALSE;

//Semaphores used for the 4 quadrants a car can move into
semaphore_t nw;
semaphore_t ne;
semaphore_t sw;
semaphore_t se;

//Semaphores used to make sure a car can only go when the one in
//front of it going the same direction finishes (leaves the intersection)
semaphore_t n;
semaphore_t e;
semaphore_t w;
semaphore_t s;

//Semaphore used to make sure that no car enters the intersection creating
//a deadlock, used in straight and left turns. A right turn will not create a dedlock
semaphore_t intersection_count;

//Array for the car threads that is set to the number passed into the command line
pthread_t *car_threads;


car_t *north_queue;
car_t *south_queue;
car_t *west_queue;
car_t *east_queue;

int n_count;
int s_count;
int w_count;
int e_count;

/*****************************
 * Function Declarations
 *****************************/

//Parse command line arguments
int parse_args(int argc, char **argv);

//Print the initial stats (what is passed into the command line)
void print_stats();

void print_close( );

//Redirects the car for proper thread synchronization based on the cars
//appr_dir and its dest_dir
void redirect(car_t car);

//3 turn possibilities, each with different semaphores they wait on
void straight(car_t car);
void left(car_t car);
void right(car_t car);

//methods for queue
void add(car_t c, char dir);
void remove_from(char dir);

/*
 * Main thread function that picks an arbitrary direction to approach from,
 * and to travel to for each car.
 *
 * Write and comment this function
 *
 * Arguments:
 *   param = The car ID number for printing purposes
 *
 * Returns:
 *   NULL
 */
void *start_car(void *param);
