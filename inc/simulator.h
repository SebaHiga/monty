#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

#include <stdlib.h>

typedef struct{
    size_t total_wins_changer;
    size_t total_wins_stayer;
} MontyCalcRet;

/* 
    Simulation process to force calculte the probability of winning 
    a price in the Monty Hall door game
*/

/* 
This function takes:
                    - size_t doors: the amount of doors to play with
                    - size_t reveal: the amount of doors to reveal after one door is chosen
                    - size_t loops: the amount of loops to do to calculate the winning chance

Return:
                    - double    The winning chance given the function arguments
                                It returns -1 if it is not posible to perform the simulation
 */
MontyCalcRet monty_calculate_winning_chance(const size_t doors, const size_t reveal, size_t loops, unsigned int seed);


/* Threading */
typedef struct{
    size_t doors;
    size_t reveal;
    size_t loops;
    
    unsigned int seed;

    MontyCalcRet ret;
} MontyParameters;

void *monty_calculate_thread(void *args);


#endif
