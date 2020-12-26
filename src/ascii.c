#include <stdio.h>

const size_t ascii_door_lines = 12;

const char *ascii_doors_unrevealed[] = {
    " __________ ",
    "|  __  __  |",
    "| |  ||  | |",
    "| |  ||  | |",
    "| |__||__| |",
    "|  __  __()|",
    "| |  ||  | |",
    "| |  ||  | |",
    "| |  ||  | |",
    "| |  ||  | |",
    "| |__||__| |",
    "|__________|"
};

const char *ascii_doors_revealed[] = {
    " __________ ",
    "||         |",
    "||         |",
    "||         |",
    "||         |",
    "||         |",
    "||)        |",
    "||         |",
    "||         |",
    "||         |",
    "||         |",
    "||_________|"
};

const char *ascii_doors_starred[] = {
    " __________ ",
    "||         |",
    "||         |",
    "||    A    |",
    "||___/_\\___|",
    "|| ',. ..' |",
    "|| /.'^'.\\ |",
    "||/'     '\\|",
    "||         |",
    "||         |",
    "||         |",
    "||_________|"
};

const char *ascii_monty_title =
"  __  __             _           _           _ _ \n |  \\/  |           | |         | |         | | |\n | \\  / | ___  _ __ | |_ _   _  | |__   __ _| | |\n | |\\/| |/ _ \\| '_ \\| __| | | | | '_ \\ / _` | | |\n | |  | | (_) | | | | |_| |_| | | | | | (_| | | |\n |_|  |_|\\___/|_| |_|\\__|\\__, | |_| |_|\\__,_|_|_|\n                          __/ |                  \n                         |___/                   \n";