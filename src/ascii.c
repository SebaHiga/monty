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
    "||)        |",
    "||         |",
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

const char *ascii_monty_title = "███╗   ███╗ ██████╗ ███╗   ██╗████████╗██╗   ██╗    ██╗  ██╗ █████╗ ██╗     ██╗     \n████╗ ████║██╔═══██╗████╗  ██║╚══██╔══╝╚██╗ ██╔╝    ██║  ██║██╔══██╗██║     ██║     \n██╔████╔██║██║   ██║██╔██╗ ██║   ██║    ╚████╔╝     ███████║███████║██║     ██║     \n██║╚██╔╝██║██║   ██║██║╚██╗██║   ██║     ╚██╔╝      ██╔══██║██╔══██║██║     ██║     \n██║ ╚═╝ ██║╚██████╔╝██║ ╚████║   ██║      ██║       ██║  ██║██║  ██║███████╗███████╗\n╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═══╝   ╚═╝      ╚═╝       ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝\n";

const char *win_message = " __  __     ______     __  __        __     __     __     __   __    \n/\\ \\_\\ \\   /\\  __ \\   /\\ \\/\\ \\      /\\ \\  _ \\ \\   /\\ \\   /\\ \"-.\\ \\   \n\\ \\____ \\  \\ \\ \\/\\ \\  \\ \\ \\_\\ \\     \\ \\ \\/ \".\\ \\  \\ \\ \\  \\ \\ \\-.  \\  \n \\/\\_____\\  \\ \\_____\\  \\ \\_____\\     \\ \\__/\".~\\_\\  \\ \\_\\  \\ \\_\\\\\"\\_\\ \n  \\/_____/   \\/_____/   \\/_____/      \\/_/   \\/_/   \\/_/   \\/_/ \\/_/ \n";