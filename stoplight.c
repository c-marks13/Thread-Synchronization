/*
 * Connor Marks
 *
 * CS 441/541 : Synchronization Project
 */
#include "stoplight.h"

int main(int argc, char * argv[]) {
    int ret;

    //Parse Command Line arguments
    if( 0 != (ret = parse_args(argc, argv)) ) {
        return -1;
    }

    print_header();

    //Initialize: - random number generator
    srand(time(NULL));

    //Initialize semaphores
    semaphore_create(&nw, 1);
    semaphore_create(&ne, 1);
    semaphore_create(&se, 1);
    semaphore_create(&sw, 1);
    semaphore_create(&n, 1);
    semaphore_create(&e, 1);
    semaphore_create(&s, 1);
    semaphore_create(&w, 1);
    //count thread set to 3 because that is the most allowed in the intersection
    semaphore_create(&intersection_count, 3);

    //Create Car Thread(s)
    car_threads = (pthread_t *)malloc(sizeof(pthread_t) * (car_num));
    //Creating car Threads
    for(int i = 0; i<car_num; i++){
      pthread_create(&car_threads[i], NULL, start_car, (void *)(intptr_t)i);
    }

    //sleeps the amount passed into command line argument, set time_to_exit to TRUE
    sleep(ttl);
    time_to_exit = 1;

    //Join threads
    for(int i = 0; i < car_num; ++i ) {
     pthread_join(car_threads[i], NULL);
    }

    //Print footer (timing information
    print_footer();
    print_close();
    print_footer();

    //Cleanup
    semaphore_destroy(&nw);
	  semaphore_destroy(&ne);
	  semaphore_destroy(&se);
	  semaphore_destroy(&sw);
    semaphore_destroy(&n);
    semaphore_destroy(&e);
    semaphore_destroy(&s);
    semaphore_destroy(&w);
    semaphore_destroy(&intersection_count);

    //Finalize support library
    support_finalize();

    return 0;
}

//print header/command line information
void print_stats(){
  printf("--------------------\n");
  printf("Time to Live : %d\n", ttl);
  printf("Number of Cars: %d\n", car_num);
  printf("--------------------\n");
}

//print footer/time stats
void print_close(){
  printf("Min. Time : %.3f msec\n", min_time*1000);
  printf("Avg. Time : %.3f msec\n", (total_time/a)*1000);
  printf("Max. Time : %.3f msec\n", max_time*1000);
  printf("Total Time : %.3f msec\n", total_time*1000);
}

//function to parse command line arguments
int parse_args(int argc, char **argv){
    if(argc != 3){
      printf("Error: Incorrect Number of Arguments\n");
      return -1;
    }

    ttl = atoi(argv[1]);
    car_num = atoi(argv[2]);

    if(ttl <= 0 || car_num <= 0 || argc != 3){
      printf("Error: Incorrect Arguments\n");
      return -1;
    }

    print_stats();

    //Initialize support library
    support_init();

    return 0;
}

//redirects cars to correct direction method
//ensures that the direcetion the car is ending uses proper synchronization
void redirect(car_t car){
  if(car.appr_dir == NORTH1){
    if(car.dest_dir == WEST){ right(car); }
    else if(car.dest_dir == EAST){ left(car);}
    else{ straight(car); }
  }
  else if(car.appr_dir == EAST){
    if(car.dest_dir == NORTH1){ right(car); }
    else if(car.dest_dir == SOUTH1){ left(car);}
    else{ straight(car); }
  }
  else if(car.appr_dir == SOUTH1){
    if(car.dest_dir == EAST){ right(car); }
    else if(car.dest_dir == WEST){ left(car);}
    else{ straight(car); }
  }
  else if(car.appr_dir == WEST){
    if(car.dest_dir == SOUTH1){ right(car); }
    else if(car.dest_dir == NORTH1){ left(car);}
    else{ straight(car); }
  }
}

//Synchronization for a car going straight
void straight(car_t car){
  car.time = car.time + (TIME_TO_CROSS*2);

  car.state = STATE_APPROACH_I1;
  print_state(car, NULL);

  semaphore_wait(&intersection_count);
  if(car.appr_dir == NORTH1){
    semaphore_wait(&n);
    semaphore_wait(&nw);
    car.state = STATE_GO_STRAIGHT_I1;
    print_state(car, NULL);
    usleep(TIME_TO_CROSS);
    semaphore_wait(&sw);
    usleep(TIME_TO_CROSS);
    semaphore_post(&nw);
    semaphore_post(&sw);
    semaphore_post(&n);
  }
  else if(car.appr_dir == EAST){
    semaphore_wait(&e);
    semaphore_wait(&ne);
    car.state = STATE_GO_STRAIGHT_I1;
    print_state(car, NULL);
    usleep(TIME_TO_CROSS);
    semaphore_wait(&nw);
    usleep(TIME_TO_CROSS);
    semaphore_post(&ne);
    semaphore_post(&nw);
    semaphore_post(&e);
  }
  else if(car.appr_dir == SOUTH1){
    semaphore_wait(&s);
    semaphore_wait(&se);
    car.state = STATE_GO_STRAIGHT_I1;
    print_state(car, NULL);
    usleep(TIME_TO_CROSS);
    semaphore_wait(&ne);
    usleep(TIME_TO_CROSS);
    semaphore_post(&se);
    semaphore_post(&ne);
    semaphore_post(&s);
  }
  else if(car.appr_dir == WEST){
    semaphore_wait(&w);
    semaphore_wait(&sw);
    car.state = STATE_GO_STRAIGHT_I1;
    print_state(car, NULL);
    usleep(TIME_TO_CROSS);
    semaphore_wait(&se);
    usleep(TIME_TO_CROSS);
    semaphore_post(&sw);
    semaphore_post(&se);
    semaphore_post(&w);
  }
  semaphore_post(&intersection_count);
}

//Synchronization for a car going left
void left(car_t car){
  car.state = STATE_APPROACH_I1;
  print_state(car, NULL);

  semaphore_wait(&intersection_count);
  if(car.appr_dir == NORTH1){
    semaphore_wait(&n);
    semaphore_wait(&nw);
    car.state = STATE_GO_LEFT_I1;
    print_state(car, NULL);
    usleep(TIME_TO_CROSS);
    semaphore_wait(&sw);
    usleep(TIME_TO_CROSS);
    semaphore_post(&nw);
    semaphore_wait(&se);
    usleep(TIME_TO_CROSS);
    semaphore_post(&sw);
    semaphore_post(&se);
    semaphore_post(&n);
  }
  else if(car.appr_dir == EAST){
    semaphore_wait(&e);
    semaphore_wait(&ne);
    car.state = STATE_GO_LEFT_I1;
    print_state(car, NULL);
    usleep(TIME_TO_CROSS);
    semaphore_wait(&nw);
    usleep(TIME_TO_CROSS);
    semaphore_post(&ne);
    semaphore_wait(&sw);
    usleep(TIME_TO_CROSS);
    semaphore_post(&nw);
    semaphore_post(&sw);
    semaphore_post(&e);
  }
  else if(car.appr_dir == SOUTH1){
    semaphore_wait(&s);
    semaphore_wait(&se);
    car.state = STATE_GO_LEFT_I1;
    print_state(car, NULL);
    usleep(TIME_TO_CROSS);
    semaphore_wait(&ne);
    usleep(TIME_TO_CROSS);
    semaphore_post(&se);
    semaphore_wait(&nw);
    usleep(TIME_TO_CROSS);
    semaphore_post(&ne);
    semaphore_post(&nw);
    semaphore_post(&s);
  }
  else if(car.appr_dir == WEST){
    semaphore_wait(&w);
    semaphore_wait(&sw);
    car.state = STATE_GO_LEFT_I1;
    print_state(car, NULL);
    usleep(TIME_TO_CROSS);
    semaphore_wait(&se);
    usleep(TIME_TO_CROSS);
    semaphore_post(&sw);
    semaphore_wait(&ne);
    usleep(TIME_TO_CROSS);
    semaphore_post(&se);
    semaphore_post(&ne);
    semaphore_post(&w);
  }
  semaphore_post(&intersection_count);
}

//Synchronization for a car going right
void right(car_t car){
  car.state = STATE_APPROACH_I1;
  print_state(car, NULL);

  //will not wait for intersection count, only wait for the square in front of it
  //to open up because it is only turning right
  if(car.appr_dir == NORTH1){
    semaphore_wait(&n);
    semaphore_wait(&nw);
    car.state = STATE_GO_RIGHT_I1;
    print_state(car, NULL);
    usleep(TIME_TO_CROSS);
    semaphore_post(&nw);
    semaphore_post(&n);
  }
  else if(car.appr_dir == EAST){
    semaphore_wait(&e);
    semaphore_wait(&ne);
    car.state = STATE_GO_RIGHT_I1;
    print_state(car, NULL);
    usleep(TIME_TO_CROSS);
    semaphore_post(&ne);
    semaphore_post(&e);
  }
  else if(car.appr_dir == SOUTH1){
    semaphore_wait(&s);
    semaphore_wait(&se);
    car.state = STATE_GO_RIGHT_I1;
    print_state(car, NULL);
    usleep(TIME_TO_CROSS);
    semaphore_post(&se);
    semaphore_post(&s);
  }
  else if(car.appr_dir == WEST){
    semaphore_wait(&w);
    semaphore_wait(&sw);
    car.state = STATE_GO_RIGHT_I1;
    print_state(car, NULL);
    usleep(TIME_TO_CROSS);
    semaphore_post(&sw);
    semaphore_post(&w);
  }
}

/*
void add(car_t c, char dir){
  if(dir == 'n'){
    n_count++;
    north_queue = realloc(north_queue, (sizeof(car_t)*n_count));
    north_queue[n_count-1] = c;
  }
}

void remove_from(char dir){
  if(dir == 'n'){
    for(int i = 0; i<n_count-1; i++){
      north_queue[i] = north_queue[i+1];
    }
    n_count--;
    north_queue = realloc(north_queue, (sizeof(car_t)*n_count));
  }
}
*/

//Approach intersection
//param = Car Number (car_id)
void *start_car(void *param) {

    int car_id = (intptr_t)param;
    car_t this_car;
    this_car.car_id = car_id;

    //Keep cycling through
    while( time_to_exit == FALSE ) {

        //Sleep for a bounded random amount of time before approaching the intersection
        usleep(random()%TIME_TO_APPROACH);

        //Setup the car's direction, where it is headed, set its state
        this_car.appr_dir = get_random_direction(-1);
        this_car.dest_dir = get_random_direction(this_car.appr_dir);
        this_car.state = STATE_WAITING_I1;

        //Mark start time for car
        gettimeofday(&this_car.start_time, NULL);
        gettimeofday(&this_car.end_time, NULL);
        print_state(this_car, NULL);

        //Move the car in the direction and change its state accordingly
        redirect(this_car);

        //Once we return from redirect, the car has left the intersection
        this_car.state = STATE_LEAVE_I1;

        //Mark leave time for car
        gettimeofday(&this_car.end_time, NULL);
        print_state(this_car, NULL);

        //Save statistics about the cars travel
        struct timeval difference = get_timeval_diff_as_timeval(this_car.start_time, this_car.end_time);
        double diff = timeval_to_double(difference);
        this_car.time = diff;
        total_time += this_car.time;

        //sets the min time
        if(min_time > this_car.time || a == 0){ min_time = this_car.time; }
        //sets the max time
        if(max_time < this_car.time){ max_time = this_car.time; }
        //increase a for the average
        a++;
    }

    //All done
    pthread_exit((void *) 0);

    return NULL;
}
