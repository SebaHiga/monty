#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

#include <stdlib.h>

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
double monty_calculate_winning_chance(const size_t doors, const size_t reveal, size_t loops);


#endif
