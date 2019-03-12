//
// Created by Kayla Hamilton on 3/11/2019.
//

#include "gamestats.h"
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
        setMode(gameStats, mode);
    else {
        printw("\nError, please enter an integer.");
        printw("\nPress any key to continue.");
        refresh();
        getch();
        selectMode(gameStats);
    }
}

void selectXDimension(struct GameStats *gameStats) {
    const int maxXDimension = 40;
    int x;
    clear();
    printw("Welcome to Connect Four!\n");
    printw("Please enter the width of the game board (less than or equal to %d): ", maxXDimension);
    refresh();
    if(scanw("%d", &x)) {
        if(x <= maxXDimension && x > 0)
            setxDimension(gameStats, x);
        else {
            if(x > maxXDimension)
                printw("\nBoard size is too large, please enter a value less than or equal to %d.", maxXDimension);
            else
                printw("\nBoard must have a dimension greater than 0, please enter a value greater than 0.");
            printw("\nPress any key to continue.");
            refresh();
            getch();
            selectXDimension(gameStats);
        }
    }
    else {
        printw("\nError, please enter an integer value.");
        printw("\nPress any key to continue.");
        refresh();
        getch();
        selectXDimension(gameStats);
    }
}

void selectYDimension(struct GameStats *gameStats) {
    const int maxYDimension = 40;
    int y;
    clear();
    printw("Welcome to Connect Four!\n");
    printw("Please enter the height of the game board (less than or equal to %d): ", maxYDimension);
    refresh();
    if(scanw("%d", &y)) {
        if(y <= maxYDimension)
            setyDimension(gameStats, y);
        else {
            if(y > maxYDimension)
                printw("\nBoard size is too large, please enter a value less than or equal to %d.", maxYDimension);
            else
                printw("\nBoard must have a dimension greater than 0, please enter a value greater than 0.");
            printw("\nPress any key to continue.");
            refresh();
            getch();
            selectYDimension(gameStats);
        }
    }
    else {
        printw("\nError, please enter an integer value.");
        printw("\nPress any key to continue.");
        refresh();
        getch();
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