#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#include "common.h"
#include "simulator.h"
#include "terminal_ui.h"
#include "game.h"

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
    size_t loops = 1;
    size_t reveal = 0;
    size_t n_threads = 1;
    bool interactive = false;

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
        else if (!strcmp(argv[i], "--interactive") ){
            interactive = argv[i+1][0] == '1' ? true : false;
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

    // Start interactive mode and exit
    if (interactive){
        start_monty_game(doors, reveal);
        return EXIT_SUCCESS;
    } 

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

    // Initialize parameters and create threads
    for (size_t i = 0; i < n_threads; i++) {
        arr_params[i].doors = doors;
        arr_params[i].reveal = reveal;
        arr_params[i].loops = loops / n_threads;
        arr_params[i].seed = rand();
        arr_params[i].loops_done = 0;

        pthread_create(arr_threads + i, NULL, monty_calculate_thread, (void *) (arr_params + i));
    }

    printf("Threads are running!\n");

    // Print progress status bar using the loops done and the loops to be done.
    while ( arr_params[n_threads-1].loops_done < arr_params[n_threads-1].loops ){
        printProgress((double) arr_params[n_threads-1].loops_done / arr_params[n_threads-1].loops);
        usleep(50);
    }
    printProgress(1);
    printf("\n");

    // Wait all threads to join
    for (size_t i = 0; i < n_threads; i++) {
        int status = pthread_join(arr_threads[i], NULL);

        printf("Thread finished with status: %d\n", status);
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