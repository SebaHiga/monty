#ifndef __TEMRINAL_UI_H__
#define __TEMRINAL_UI_H__

/* This headers contains terminal user interface functions */

/* Defines */
/* Progress status bar */
#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

/* Print the help menu and exit the program */
void print_help_and_exit();

/* Print a progress status bar given a percentage */
void printProgress(const double percentage);

#endif


