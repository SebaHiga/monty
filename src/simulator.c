#include <time.h>
#include <stdio.h>
#include <string.h>

#include "simulator.h"

double monty_calculate_winning_chance(const size_t doors, const size_t reveal, const size_t loops){
    if (doors - 1 < reveal || loops == 0) return -1;
    // // Use unix timestamp (seconds) as a random seed with uniform distribution
    srand((int) time(NULL));

    /* Create dynamic door array with: -1 revealed
                                        0 is empty
                                        1 has the winning price
    */
    int *door_array = (int*) malloc (doors * sizeof(int));

    size_t total_wins_changer = 0;
    size_t total_wins_stayer = 0;

    size_t loop_count = loops;

    while ( loop_count ) {

        // Setup initial winning and selected positions
        size_t index_price = rand() % doors;
        size_t index_stayer = rand() % doors;

        // printf("Setting winning index to %ld\nThe selected index is: %ld\n", index_price, index_stayer);
        
        // clean doors putting all of them as empty
        memset(door_array, 0, doors * sizeof(int));
        door_array[index_price] = 1;

        // Reveal doors that are not the selected ones or that has the winning price
        size_t revealed = 0;

        while ( revealed < reveal ) {
            size_t to_reveal = rand() % doors;

            if ( door_array[to_reveal] == 0 
                && !!!(to_reveal == index_stayer || to_reveal == index_price) ){
                    
                    // Revealed
                    door_array[to_reveal] = -1;
                    revealed++;
            }
        }

        // debug printing array
        for(size_t i = 0; i < doors; i++){
            // printf("index:\t%ld\tvalue:\t%d\n", i, door_array[i]);
        }

        // Get new index to the switched door
        size_t index_changer = rand() % doors;
        
        do {
            index_changer = rand() % doors;
        } while(index_changer == index_stayer
                || door_array[index_changer] == -1);

        // printf("Changer index is: %ld\n", index_changer);

        if (index_changer == index_price) {
            // printf("changer won\n");
            total_wins_changer++;
        } 
        if (index_stayer == index_price) {
            // printf("stayer won\n");
            total_wins_stayer++;
        }


        loop_count--;
    }

    printf("stayer won: %ld times and changer won %ld times\n", total_wins_stayer, total_wins_changer);

    double prob_stayer = (double) total_wins_stayer / loops;
    double prob_changer = (double) total_wins_changer / loops;

    printf("probability stayer: %f\t probability changer: %f", prob_stayer, prob_changer);

    free(door_array);

    return 0;
}
