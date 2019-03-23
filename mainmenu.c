//
// Created by Kayla Hamilton on 3/11/2019.
//

#include "gamestats.h"
#include "inputkeys.h"
#include "mainmenu.h"
#include <curses.h>
#include <ncurses.h>


void selectMode(struct GameStats *gameStats) {
    int mode;
    clear();
    printw("Welcome to Connect Four!\n");
    printw("Please select a game mode:\n");
    printw("\tPlayer vs. Player (1)\n");
    printw("\tPlayer vs. Computer (2)\n");
    printw("Enter mode here: ");
    refresh();
    if(scanw("%d", &mode))
        if(mode == 1 || mode == 2)
            setMode(gameStats, mode);
        else {
            printw("\nError, please enter 1 or 2.\n");
            getEnter();
            selectMode(gameStats);
        }
    else {
        printw("\nError, please enter an integer.\n");
        getEnter();
        selectMode(gameStats);
    }
}

void selectXDimension(struct GameStats *gameStats) {
    const int maxXDimension = 40;
    int x;
    clear();
    printw("Welcome to Connect Four!\n");
    printw("Please enter the width of the game board: ", maxXDimension);
    refresh();
    if(scanw("%d", &x)) {
        if(x <= maxXDimension && x >= 4)
            setxDimension(gameStats, x);
        else {
            if(x > maxXDimension)
                printw("\nBoard size is too large, \nplease enter a value less than or equal to %d.\n", maxXDimension);
            else
                printw("\nBoard must have a dimension greater than or equal 4, \nplease enter a value greater than or equal to 4.\n");
            getEnter();
            selectXDimension(gameStats);
        }
    }
    else {
        printw("\nError, please enter an integer value.\n");
        getEnter();
        selectXDimension(gameStats);
    }
}

void selectYDimension(struct GameStats *gameStats) {
    const int maxYDimension = 40;
    int y;
    clear();
    printw("Welcome to Connect Four!\n");
    printw("Please enter the height of the game board: ", maxYDimension);
    refresh();
    if(scanw("%d", &y)) {
        if(y <= maxYDimension && y >= 4)
            setyDimension(gameStats, y);
        else {
            if(y > maxYDimension)
                printw("\nBoard size is too large, \nplease enter a value less than or equal to %d.\n", maxYDimension);
            else
                printw("\nBoard must have a dimension greater than or equal to 4, \nplease enter a value greater than or equal to 4.\n");
            getEnter();
            selectYDimension(gameStats);
        }
    }
    else {
        printw("\nError, please enter an integer value.\n");
        getEnter();
        selectYDimension(gameStats);
    }
}

void selectBoardSize(struct GameStats *gameStats) {
    selectXDimension(gameStats);
    selectYDimension(gameStats);
}

void executeMainMenu(struct GameStats *gameStats) {
    selectMode(gameStats);
    selectBoardSize(gameStats);
}