#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

void print_help_and_exit() {
    printf("Usage: ./waz [--doors <n>]\n");
    printf("--help          - show help and exit\n");
    printf("--doors <n>     - amount of doors to simulate with  0 < n\n");
    printf("--loops <n>     - amount of loops to do to calculate probability 0 < n\n");
    exit(0);
}

int main(int argc _MAYBE_UNUSED_, const char *argv[] _MAYBE_UNUSED_){

    if ( argc < 5 ) {
        print_help_and_exit();
    }
    else if ( !strcmp(argv[1], "--help") ) {
        print_help_and_exit();
    }

    // Little trick to ignore and shift the name of program
    argc--; argv++;

    size_t doors = 0;
    size_t loops = 0;

    // Parse arguments
    for (int i = 0; i < argc; i += 2) {
        if ( !strcmp(argv[i], "--doors") ) {
            doors = atoi(argv[i+1]);
        }
        else if ( !strcmp(argv[i], "--loops") ){
            loops = atoi(argv[i+1]);
        }
        else {
            printf ("**ERROR**: unrecognized flag: %s\n", argv[i]);
            print_help_and_exit();
        }
    }

    // Check
    if ( doors == 0 || loops == 0 ) {
        print_help_and_exit();
    }

    // All arguments are ok for this program




    return 0;
}