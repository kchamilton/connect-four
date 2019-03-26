/*
 * Functions to implement and run main menu/beginning of game tasks.
 */

#include "gamestats.h"
#include "inputkeys.h"
#include "mainmenu.h"
#include <curses.h>
#include <ncurses.h>


//The selectMode() function gets the desired playing mode from the user.
void selectMode(struct GameStats *gameStats) {
    int mode;
    clear();
    printw("Welcome to Connect Four!\n");
    printw("Please select a game mode:\n");
    printw("\tPlayer vs. Player (1)\n");
    printw("\tPlayer vs. Computer (2)\n");
    printw("Enter mode here: ");
    refresh();
    //if the value entered is an integer
    if(scanw("%d", &mode)) {
        //store mode
        if (mode == 1 || mode == 2)
            setMode(gameStats, mode);
        //the value entered was not 1 or 2
        else {
            printw("\nError, please enter 1 or 2.\n");
            getEnter();
            //call function again to get correct input
            selectMode(gameStats);
        }
    }
    //the value entered was not an integer
    else {
        printw("\nError, please enter an integer.\n");
        getEnter();
        //call function again to get correct input
        selectMode(gameStats);
    }
}

//The selectXDimension() function gets the desired board width from the user.
void selectXDimension(struct GameStats *gameStats) {
    const int maxXDimension = 40;
    int x;
    clear();
    printw("Welcome to Connect Four!\n");
    printw("Please enter the width of the game board: ", maxXDimension);
    refresh();
    //if the value inputted is an integer
    if(scanw("%d", &x)) {
        //store x dimension
        if(x <= maxXDimension && x >= 4)
            setxDimension(gameStats, x);
        else {
            //the value entered was not less than or equal to the max dimension
            if(x > maxXDimension)
                printw("\nBoard size is too large, \nplease enter a value less than or equal to %d.\n", maxXDimension);
            //the value entered was not greater than or equal to 4
            else
                printw("\nBoard must have a dimension greater than or equal 4, \nplease enter a value greater than or equal to 4.\n");
            getEnter();
            //call function again to get correct input
            selectXDimension(gameStats);
        }
    }
    //the value entered was not an integer
    else {
        printw("\nError, please enter an integer value.\n");
        getEnter();
        //call function again to get correct input
        selectXDimension(gameStats);
    }
}

//The selectYDimension() function gets the desired board height from the user.
void selectYDimension(struct GameStats *gameStats) {
    const int maxYDimension = 40;
    int y;
    clear();
    printw("Welcome to Connect Four!\n");
    printw("Please enter the height of the game board: ", maxYDimension);
    refresh();
    //if the value inputted is an integer
    if(scanw("%d", &y)) {
        //store y dimension
        if(y <= maxYDimension && y >= 4)
            setyDimension(gameStats, y);
        else {
            //the value entered was not less than or equal to the max dimension
            if(y > maxYDimension)
                printw("\nBoard size is too large, \nplease enter a value less than or equal to %d.\n", maxYDimension);
            //the value entered was not greater than or equal to 4
            else
                printw("\nBoard must have a dimension greater than or equal to 4, \nplease enter a value greater than or equal to 4.\n");
            getEnter();
            //call function again to get correct input
            selectYDimension(gameStats);
        }
    }
    //the value entered was not an integer
    else {
        printw("\nError, please enter an integer value.\n");
        getEnter();
        //call function again to get correct input
        selectYDimension(gameStats);
    }
}

//The selectBoardSize() function gets user input for the desired board size.
void selectBoardSize(struct GameStats *gameStats) {
    selectXDimension(gameStats);
    selectYDimension(gameStats);
}

//The executeMainMenu() function gets user input for the desired game mode and board size.
void executeMainMenu(struct GameStats *gameStats) {
    selectMode(gameStats);
    selectBoardSize(gameStats);
}