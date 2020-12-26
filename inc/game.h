#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdbool.h>

/* Common macros to shorten code verbosity */

#define MONTY_MAX_DOORS 10
#define MONTY_BEHAVIOUR_TOTAL 4

#define MONTY_DOOR_UNREVEALED   0
#define MONTY_DOOR_REVEALED     1
#define MONTY_IS_SELECTED       2
#define MONTY_HAS_PRICE         3
#define MONTY_HAS_WON           4

#define REVEALED_DOOR   "[ ]"

typedef enum {
    NORMAL,
    MONTY_HELL,
    MONTY_ANGELIC,
    MONTY_IGNORANT
} host_behaviour;

void start_monty_game(const size_t doors, const size_t reveal);
void print_monty_host_type(const host_behaviour host);

// 0 -> ok
// 1 -> ignorant revealed the price!
int host_interact_post_select(host_behaviour host, int *arr_doors, const size_t doors, const size_t reveal, const size_t selected);

void host_reveal_doors(int *arr_doors, const size_t doors, const size_t reveal);

void print_monty_doors(int *arr_doors, const size_t doors);

size_t get_door_from_user(int *arr_doors, const size_t doors);

bool ask_to_switch_doors();

// 0 -> didnt win
// 1 -> won game
int check_won_game(int *arr_doors, const size_t doors);

#endif


