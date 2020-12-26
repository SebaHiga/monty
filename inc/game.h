#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdbool.h>

/* Common macros to shorten code verbosity */

#define MONTY_MAX_DOORS 10
#define MONTY_BEHAVIOUR_TOTAL 3

#define MONTY_DOOR_UNREVEALED   0
#define MONTY_DOOR_REVEALED     1
#define MONTY_IS_SELECTED       2
#define MONTY_HAS_PRICE         3
#define MONTY_HAS_WON           4
#define MONTY_SHOW_VOID         5

#define REVEALED_DOOR   "[ ]"

typedef enum {
    NORMAL,
    MONTY_HELL,
    MONTY_ANGELIC,
} host_behaviour;

void start_monty_game(const size_t doors, const size_t reveal);
void print_monty_host_type(const host_behaviour host);

// 0 -> ok
// 1 -> ignorant revealed the price!
void host_interact_post_select(host_behaviour host, int *arr_doors, const size_t doors, const size_t reveal, const size_t selected, const size_t price);

void host_reveal_doors(int *arr_doors, const size_t doors, const size_t reveal);

void print_monty_doors(int *arr_doors, const size_t doors);

size_t get_door_from_user(int *arr_doors, const size_t doors);

bool ask_to_switch_doors();

void print_ascii_doors(int *arr_doors, const size_t doors);

#endif


