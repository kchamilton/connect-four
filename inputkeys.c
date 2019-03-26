/*
 * Function(s) used to get a specific key input from the user.
 */

#include "inputkeys.h"
#include <curses.h>

/*
 * The getEnter() function waits for the user to press the enter key before continuing the program.
 */
void getEnter() {
    noecho();
    printw("Press enter to continue.\n");
    refresh();
    keypad(stdscr, TRUE);
    //the enter key has an ascii value 10, waiting for a key input of 10 from the enter key
    while(10 != getch()) {}
    keypad(stdscr, FALSE);
    echo();
}