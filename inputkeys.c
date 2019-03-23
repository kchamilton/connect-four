//
// Created by Kayla Hamilton on 3/22/2019.
//

#include "inputkeys.h"
#include <curses.h>

void getEnter() {
    noecho();
    printw("Press enter to continue.\n");
    refresh();
    keypad(stdscr, TRUE);
    while(10 != getch()) {}
    keypad(stdscr, FALSE);
    echo();
}