#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

#include <stdlib.h>


/* 
    Simulation process to force calculte the probability of winning 
    a price in the Monty Hall door game
*/

/* Type structures */

/* This is the return type from the thread, it contains the total winners of both cases */

typedef struct{
    size_t total_wins_changer;
    size_t total_wins_stayer;
} MontyCalcRet;

/*
    This is the parameter structure, it contains the amount of doors, doors to reveal, loops and the return type.
    Additionally it has the seed for rand_r() and the loops that the thread has done.
*/

typedef struct{
    size_t doors;
    size_t reveal;
    size_t loops;

    size_t loops_done;
    
    unsigned int seed;

    MontyCalcRet ret;
} MontyParameters;

/* 
This function takes:
                    - size_t doors: the amount of doors to play with
                    - size_t reveal: the amount of doors to reveal after one door is chosen
                    - size_t loops: the amount of loops to do to calculate the winning chance

Return:
                    - double    The winning chance given the function arguments
                                It returns -1 if it is not posible to perform the simulation
 */
MontyCalcRet monty_calculate_winning_chance(MontyParameters *params);

/* 

    Use this function to start a thread. Also, use the structure MontyParameters defined 
    to do the simulation. Remember to set a proper seed.

*/
void *monty_calculate_thread(void *args);


#endif
