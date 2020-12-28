#include <time.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "simulator.h"

MontyCalcRet monty_calculate_winning_chance(MontyParameters *params){
    MontyCalcRet ret;
    ret.total_wins_changer = 0;
    ret.total_wins_stayer = 0;
    unsigned int seed_d = params->seed;

    if (params->doors - 1 < params->reveal || params->loops == 0) return ret;

    /* Create dynamic door array with: -1 revealed
                                        0 is empty
                                        1 has the winning price
    */
    int *door_array = (int*) malloc (params->doors * sizeof(int));

    if (door_array == NULL) {
        printf("ERROR: No memory left to allocate door array'n");
        return ret;
    }

    while ( params->loops ) {
        params->loops--;
        // Setup initial winning and selected positions
        size_t index_price = rand_r(&seed_d) % params->doors;
        size_t index_stayer = rand_r(&seed_d) % params->doors;

        // printf("Setting winning index to %ld\nThe selected index is: %ld\n", index_price, index_stayer);
        
        // clean doors, putting all of them as empty
        memset(door_array, 0, params->doors * sizeof(int));
        door_array[index_price] = 1;

        size_t revealed = 0;
        size_t to_reveal = 0;

        while ( revealed < params->reveal ) {
            
            // Reveal doors that are not the selected ones or that have the winning price
            if ( door_array[to_reveal] == 0 
                && !!!(to_reveal == index_stayer || to_reveal == index_price) ){
                    
                    // Revealed
                    door_array[to_reveal] = -1;
                    revealed++;
            }

            to_reveal++;
        }

        // Get new index to the switched door
        size_t index_changer = 0;
        
        // Iterate over the index changer until it is not the one that it was
        // already selected or the door that was already revealed
        do {
            index_changer = rand_r(&seed_d) % params->doors;
        } while(index_changer == index_stayer
                || door_array[index_changer] == -1);


        if (index_changer == index_price) {
            params->ret.total_wins_changer++;
        } 
        if (index_stayer == index_price) {
            params->ret.total_wins_stayer++;
        }

    }

    free(door_array);

    return ret;
}

void *monty_calculate_thread(void *args)
{
    MontyParameters *params = (MontyParameters *) args;

    monty_calculate_winning_chance(params);

    pthread_exit(NULL);
}