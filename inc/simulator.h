#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

#include <stdlib.h>

typedef struct{
    size_t total_wins_changer;
    size_t total_wins_stayer;
} MontyCalcRet;

/* Threading */
typedef struct{
    size_t doors;
    size_t reveal;
    size_t loops;

    size_t *loops_done;
    
    unsigned int seed;

    MontyCalcRet ret;
} MontyParameters;

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
MontyCalcRet monty_calculate_winning_chance(MontyParameters *params);

/* 

    Use this function to start a thread. Also, use the structure MontyParameters defined 
    to do the simulation. Remember to set a proper seed.

*/
void *monty_calculate_thread(void *args);


#endif
