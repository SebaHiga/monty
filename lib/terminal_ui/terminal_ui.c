#include <stdio.h>
#include <stdlib.h>

#include "terminal_ui.h"

void print_help_and_exit() {
    printf("Usage: ./waz [--doors <n>] [--reveal <n>] [--loops <n>] [--threads <n>]\n");
    printf("--help              - show help and exit\n");
    printf("--doors <n>         - amount of doors to simulate with  0 < n\n");
    printf("--reveal <n>        - amount of doors to reveal 0 <= n < (doors - 1)\n");
    printf("--loops <n>         - amount of loops to do to calculate probability 0 < n\n");
    printf("--threads <n>       - amount of threads to use 1 < n < 5\n");
    printf("--interactive [y/n] - start interactive mode and play the game!\n");
    exit(0);
}

void printProgress(const double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}
