//
// Created by Kayla Hamilton on 3/11/2019.
//

#include "gamestats.h"
#include "inputkeys.h"
#include "mainmenu.h"
#include "endmenu.h"
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>


int replayOptions() {
    int answer;
    clear();
    printw("Thank you for playing Connect Four!\n");
    printw("Would you like to:\n");
    printw("\tHave a rematch? (1)\n");
    printw("\tReturn to the main menu? (2)\n");
    printw("\tOr exit the game? (3)\n");
    printw("Enter your choice here: ");
    refresh();
    echo();
    if(scanw("%d", &answer) && (answer == 1 || answer == 2 || answer == 3))
        return answer;
    else {
        printw("\nError, please enter 1, 2, or 3 to proceed.\n");
        getEnter();
        return 0 + replayOptions();
    }
}

int likeToResize() {
    char answer;
    printw("Would you like to change the game board dimensions? (y/n): ");
    refresh();
    if(scanw("%c", &answer)) {
        if(answer == 'y' || answer == 'Y')
            return 1;
        else if(answer == 'n' || answer == 'N')
            return 0;
        else {
            printw("\nError, please enter y to change the game board dimensions or n to leave them the same.\n");
            getEnter();
            return 0 + likeToResize();
        }
    }
    else {
        printw("\nError, please enter y to change the game board dimensions or n to leave them the same.\n");
        getEnter();
        return 0 + likeToResize();
    }
}

void executeEndMenu(struct GameStats *gameStats, int *play, int *exit){
    clear();
    int option = replayOptions();
    if(option == 1) {
        if(likeToResize())
            selectBoardSize(gameStats);
    }
    else if(option == 2) {
        *play = 0;
        free(gameStats);
    }
    else {
        *play = 0;
        *exit = 1;
        free(gameStats);
    }
}

