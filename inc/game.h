#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdbool.h>

/* Common macros to shorten code verbosity */

/* Defines */
#define MONTY_MAX_DOORS 6
#define MONTY_BEHAVIOUR_TOTAL 3

#define MONTY_DOOR_UNREVEALED   0
#define MONTY_DOOR_REVEALED     1
#define MONTY_IS_SELECTED       2
#define MONTY_HAS_PRICE         3
#define MONTY_HAS_WON           4
#define MONTY_SHOW_VOID         5

/* Structures and enums */
typedef enum {
    NORMAL,
    MONTY_HELL,
    MONTY_ANGELIC,
} host_behaviour;

/* Function definitions */

/* It starts the monty game */
void start_monty_game(const size_t doors, const size_t reveal);

/* 
This function should be run after the user selects a door 
The behaviour of the host is randomized and each one is more friendly or a total nightmare
This should be executed once
*/
void host_interact_post_select(host_behaviour host, int *arr_doors, const size_t doors, const size_t reveal, const size_t selected, const size_t price);

/* 
    Reveal doors with the amount of doors to reveal on arguments
    It only reveals doors that are not the selected one neither has the price behind it
*/
void host_reveal_doors(int *arr_doors, const size_t doors, const size_t reveal);

/* 
    Read input from user, the return is the index of the selected door 
    It also does some basic check to validate user's input
*/
size_t get_door_from_user(int *arr_doors, const size_t doors);

/* 
    Ask the user to switch doors, the return type is whether the user agrees to switch or not 
    It also does some basic validations from the user
*/
bool ask_to_switch_doors();

/* This function prints the host type on console */
void print_monty_host_type(const host_behaviour host);

/* Print doors on ASCII art */
void print_ascii_doors(int *arr_doors, const size_t doors);

#endif


