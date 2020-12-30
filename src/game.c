#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "common.h"
#include "ascii.h"

void start_monty_game(const size_t doors, const size_t reveal _MAYBE_UNUSED_){
    if (doors > MONTY_MAX_DOORS) {
        printf("The maximum amount of doors to use is %d!", MONTY_MAX_DOORS);
        return;
    }

    // // Use unix timestamp (seconds) as a random seed with uniform distribution
    srand((int) time(NULL));

    int *arr_doors = (int*) calloc (doors, sizeof(int));

    if (arr_doors == NULL) {
        printf("No space left for doors!\n");
        return;
    }

    // Get random host behaviour and the random door for the price
    host_behaviour host = rand() % MONTY_BEHAVIOUR_TOTAL;
    size_t index_price = rand() % doors;

    arr_doors[index_price] = MONTY_HAS_PRICE;

    // Print stage!
    printf("%s", ascii_monty_title);
    print_ascii_doors(arr_doors, doors);

    // Read user input and save it
    size_t index_selected = get_door_from_user(arr_doors, doors);

    // Set the door as a selected one
    if (index_selected != index_price){
        arr_doors[index_selected] = MONTY_IS_SELECTED;
    }

    // This functions does the interaction between the user and the host
    host_interact_post_select(host, arr_doors, doors, reveal, index_selected, index_price);

    free(arr_doors);

    // Print the host type
    print_monty_host_type(host);
}

void host_interact_post_select(host_behaviour host, int *arr_doors, const size_t doors, const size_t reveal, const size_t selected, const size_t price) {
    // Temporal selected index
    size_t selected_tmp = selected;


    // This switch statement can be WAAAY clearer
    switch (host) {
        // Always reveals and asks to switch doors
        case NORMAL:{
            host_reveal_doors(arr_doors, doors, reveal);

            print_ascii_doors(arr_doors, doors);

            if (ask_to_switch_doors()) {
                selected_tmp = get_door_from_user(arr_doors, doors);
            }
        }break;
        // Only asks to switch if the selected door has the price
        case MONTY_HELL:{
            if (selected_tmp == price) {
                host_reveal_doors(arr_doors, doors, reveal);

                print_ascii_doors(arr_doors, doors);

                if (ask_to_switch_doors()) {
                    selected_tmp = get_door_from_user(arr_doors, doors);
                }
            }
            printf("\n");
        }break;
        // Only asks to switch if the selected door does not has the price
        case MONTY_ANGELIC:{
            if (selected_tmp != price) {
                host_reveal_doors(arr_doors, doors, reveal);

                print_ascii_doors(arr_doors, doors);

                if (ask_to_switch_doors()) {
                    selected_tmp = get_door_from_user(arr_doors, doors);
                }
            }
            printf("\n");
        }break;
    }

    if (selected_tmp == price){
        printf("%s", win_message);
        arr_doors[selected_tmp] = MONTY_HAS_WON;
    }
    else {
        printf("\nYou lost :(\n");
        arr_doors[selected_tmp] = MONTY_SHOW_VOID;
    }

    print_ascii_doors(arr_doors, doors);

}


void print_monty_host_type(const host_behaviour host) {
    printf("\nThe host type was: ");

    switch (host) {
        case NORMAL:{
            printf("Normal");
        }break;

        case MONTY_HELL:{
            printf("Monty from Hell");
        }break;

        case MONTY_ANGELIC:{
            printf("Angelic Monty");
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

size_t get_door_from_user(int *arr_doors, const size_t doors){
    size_t selected = 0;

    printf("\n\rSelect a door\n");
    scanf("%zu", &selected);

    while (selected >= doors || arr_doors[selected] == MONTY_IS_SELECTED){
        printf("\n\rPlease select a valid door\n");
        scanf("%zu", &selected);
    }

    return selected;
}

bool ask_to_switch_doors(){
    char YN;
    while ( getchar() != '\n' );
    printf("\nDo you want to switch doors? [y/n]\n");
    scanf("%c", &YN);

    return YN == 'y' ? true : false;
}


void print_ascii_doors(int *arr_doors, const size_t doors){
    for (size_t i = 0; i < doors; i++) {
        printf(ASCII_NUMBER_PLACEHOLER, i);
    }
    printf("\n");
    for(size_t row = 0; row < ascii_door_lines; row++){
        for (size_t i = 0; i < doors; i++) {
            if (arr_doors[i] == MONTY_DOOR_UNREVEALED) {
                printf("%s\t", ascii_doors_unrevealed[row]);
            }
            else if (arr_doors[i] == MONTY_DOOR_REVEALED || arr_doors[i] == MONTY_SHOW_VOID) {
                printf("%s\t", ascii_doors_revealed[row]);
            }
            else if (arr_doors[i] == MONTY_HAS_WON) {
                printf("%s\t", ascii_doors_starred[row]);
            }
            else{
                printf("%s\t", ascii_doors_unrevealed[row]);
            }
        }
        printf("\n");
    }
}
