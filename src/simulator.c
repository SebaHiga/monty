#include <time.h>
#include <stdio.h>

#include "simulator.h"

double monty_calculate_winning_chance(const size_t doors, const size_t reveal, size_t loops){
    if (doors - 1 < reveal) return -1;

    /* Create dynamic door array with: -1 revealed
                                        0 is empty
                                        1 has the winning price
    */
    int *door_array = (int*) malloc (doors * sizeof(int));

    // clean doors putting all of them as empty
    memset(door_array, 1, doors);

    // Use unix timestamp as a random seed
    srand((int) time(NULL));

    while ( loops ) {
        printf("number : %d\n", rand());

        loops--;
    }

    return 0;
}
