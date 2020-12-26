#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "common.h"

void start_monty_game(const size_t doors, const size_t reveal _MAYBE_UNUSED_){
    if (doors > MONTY_MAX_DOORS) {
        printf("The maximum amount of doors to use is %d!", MONTY_MAX_DOORS);
        return;
    }

    // // Use unix timestamp (seconds) as a random seed with uniform distribution
    srand((int) time(NULL));

    int *arr_doors = (int*) calloc (doors, sizeof(int));

    if (arr_doors == NULL) {
        printf("No space left for doors!");
        return;
    }

    host_behaviour host = 0;
    size_t index_price = rand() % doors;

    arr_doors[index_price] = MONTY_HAS_PRICE;

    printf("The monty game\n");

    for (size_t i = 0; i < doors; i++) printf("[%ld] ", i);

    size_t index_selected = get_door_from_user(arr_doors, doors);

    if (index_selected != index_price){
        arr_doors[index_selected] = MONTY_IS_SELECTED;
    }

    host_interact_post_select(host, arr_doors, doors, reveal, index_selected);

    free(arr_doors);
    print_monty_host_type(host);
}

int host_interact_post_select(host_behaviour host, int *arr_doors, const size_t doors, const size_t reveal, const size_t selected) {
    switch (host) {
        // Always reveals doors
        case NORMAL:{
            host_reveal_doors(arr_doors, doors, reveal);

            print_monty_doors(arr_doors, doors);

            if (ask_to_switch_doors()) {
                size_t selected_new = get_door_from_user(arr_doors, doors);

                // Add 1 to the selected door if it had the price it's value should be 4
                arr_doors[selected_new]++;
            }
            else {
                arr_doors[selected]++;
            }

            print_monty_doors(arr_doors, doors);

            if (check_won_game(arr_doors, doors)){
                printf("\nYou won the game!\n");
            }
            else {
                printf("\nYou didnt won\n");
            }

            return 0;
        }break;
        // Only asks to switch if the selected door has the price
        case MONTY_HELL:{
            printf("Monty from Hell");
        }break;
        // Only asks to switch if the selected door does not has the price
        case MONTY_ANGELIC:{
            printf("Angelic Monty");
        }break;
        // Random reveal and keep going
        case MONTY_IGNORANT:{
            printf("Ignorant Monty");
        }break;
    }

    return 0;
}


void print_monty_host_type(const host_behaviour host) {
    printf("The host type was: ");

    switch (host) {
        case NORMAL:{
            printf("normal");
        }break;

        case MONTY_HELL:{
            printf("Monty from Hell");
        }break;

        case MONTY_ANGELIC:{
            printf("Angelic Monty");
        }break;

        case MONTY_IGNORANT:{
            printf("Ignorant Monty");
        }break;
    }
}

void host_reveal_doors(int *arr_doors, const size_t doors _MAYBE_UNUSED_, const size_t reveal) {
        size_t revealed = 0;
        size_t index = 0;

        while ( revealed < reveal ) {
            
            // Reveal doors that are not the selected ones or that have the winning price
            if ( arr_doors[index] == MONTY_DOOR_UNREVEALED 
                && !!!(arr_doors[index] == MONTY_IS_SELECTED || arr_doors[index] == MONTY_HAS_PRICE) ){
                    
                    // Revealed
                    arr_doors[index] = MONTY_DOOR_REVEALED;
                    revealed++;
            }

            index++;
        }
}

void print_monty_doors(int *arr_doors, const size_t doors){
    for (size_t i = 0; i < doors; i++) {
        if ( arr_doors[i] == MONTY_DOOR_REVEALED ) {
            printf("[ ] ");
        }
        else if ( arr_doors[i] == MONTY_DOOR_UNREVEALED ) {
            printf("[?] ");
        }
        else {
            printf("[%ld] ", i);
        }
    }
}

size_t get_door_from_user(int *arr_doors, const size_t doors){
    size_t selected = 0;

    printf("\nSelect a door: ");
    scanf("%zu", &selected);

    while (selected >= doors || arr_doors[selected] == MONTY_IS_SELECTED){
        printf("\nPlease select a valid door: ");
        scanf("%zu", &selected);
    }

    return selected;
}

int check_won_game(int *arr_doors, const size_t doors) {
    for (size_t i = 0; i < doors; i++) if ( arr_doors[i] == MONTY_HAS_WON ) return 1;
    return 0;
}

bool ask_to_switch_doors(){
    char YN;
    while ( getchar() != '\n' );
    printf("\nDo you want to switch doors? [y/n]: ");
    scanf("%c", &YN);

    return YN == 'y' ? true : false;
}
