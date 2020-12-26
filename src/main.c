#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include "common.h"
#include "simulator.h"

/* Print text on invalid usage */
void print_help_and_exit() {
    printf("Usage: ./waz [--doors <n>] [--reveal <n>] [--loops <n>] [--threads <n>]\n");
    printf("--help          - show help and exit\n");
    printf("--doors <n>     - amount of doors to simulate with  0 < n\n");
    printf("--reveal <n>    - amount of doors to reveal 0 <= n < (doors - 1)\n");
    printf("--loops <n>     - amount of loops to do to calculate probability 0 < n\n");
    printf("--threads <n>   - amount of threads to use 1 < n < 5\n");
    exit(0);
}

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

void printProgress(const double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

int main(int argc _MAYBE_UNUSED_, const char *argv[] _MAYBE_UNUSED_){

    if ( argc < 7 ) {
        print_help_and_exit();
    }
    else if ( !strcmp(argv[1], "--help") ) {
        print_help_and_exit();
    }

    // Little trick to ignore and shift the name of program
    argc--; argv++;

    size_t doors = 0;
    size_t loops = 0;
    size_t reveal = 0;
    size_t n_threads = 1;

    // Parse arguments
    for (int i = 0; i < argc; i += 2) {
        if (argv[i+1][0] == '-') continue; // Do not accept negative numbers
        if ( !strcmp(argv[i], "--doors") ) {
            doors = atoi(argv[i+1]);
        }
        else if ( !strcmp(argv[i], "--loops") ){
            loops = atoi(argv[i+1]);
        }
        else if (!strcmp(argv[i], "--reveal") ){
            reveal = atoi(argv[i+1]);
        }
        else if (!strcmp(argv[i], "--threads") ){
            n_threads = atoi(argv[i+1]);
        }
        else {
            printf ("**ERROR**: unrecognized flag: %s\n", argv[i]);
            print_help_and_exit();
        }
    }

    // Check command line arguments
    if ( doors == 0 || loops == 0 || doors - 1 <= reveal || n_threads > 4) {
        print_help_and_exit();
    }


    printf("Using: \n\tLoops: %ld\n\tDoors: %ld\n\tReveal: %ld\n\n", loops, doors, reveal);
    // All arguments are ok for this program

    // Instantiating base params
    MontyParameters params_base;
    params_base.doors = doors;
    params_base.reveal = reveal;
    params_base.loops = loops / n_threads;

    size_t total_winners_stayer = 0;
    size_t total_winners_changer = 0;

    // // Use unix timestamp (seconds) as a random seed with uniform distribution
    srand((int) time(NULL));

    // Create a threads and it's parameters
    MontyParameters *arr_params = (MontyParameters *) malloc (n_threads * sizeof(MontyParameters));
    pthread_t *arr_threads = (pthread_t *) malloc (n_threads * sizeof(pthread_t));

    if (arr_params == NULL){
        printf("ERROR: no memory left to allocate parameters\n");
        return EXIT_FAILURE;
    }
    if (arr_threads == NULL){
        printf("ERROR: no memory left to allocate threads\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n_threads; i++) {
        arr_params[i] = params_base;
        arr_params[i].seed = rand();
        *(arr_params[i].loops_done) = 0;

        pthread_create(arr_threads + i, NULL, monty_calculate_thread, (void *) (arr_params + i));
    }

    printf("Threads are running!\n");

    while ( *(arr_params[0].loops_done) < params_base.loops ){
        printProgress((float) *(arr_params[0].loops_done) / params_base.loops);
        usleep(50);
    }
    printProgress(1);
    printf("\n");

    // Wait all threads to join
    for (size_t i = 0; i < n_threads; i++) {
        int status = pthread_join(arr_threads[i], NULL);

        printf("Thread finished with: %d\n", status);
        total_winners_changer += arr_params[i].ret.total_wins_changer;
        total_winners_stayer += arr_params[i].ret.total_wins_stayer;
    }

    double prob_changer = (double) total_winners_changer / loops;
    double prob_stayer = (double) total_winners_stayer / loops;
    double predicted_for_changer = (double) (doors - 1) / (doors * (doors - reveal - 1));

    printf("** The probability to win with no door change: %f **\n", prob_stayer);
    printf("** The probability to win with door change is: %f **\n", prob_changer);

    printf("The prediction for the Changer is: %f\nSimulation error: %f\n", predicted_for_changer,
    predicted_for_changer - prob_changer);

    // Free resources
    free(arr_params);
    free(arr_threads);
    pthread_exit(NULL);
}