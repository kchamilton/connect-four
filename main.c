#include "gamestats.h"
#include "mainmenu.h"
#include "endmenu.h"
#include "game.h"
#include "inputkeys.h"
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>

int newGame();

int main() {
    int exit = 0;
    initscr();
    //loop allows for multiple games in either mode
    while(!exit) {
        //verifies user wants to play a new game
        if(newGame()) {
            int play = 1;
            //allocate space for struct that holds game data (i.e. board size, mode, and score)
            struct GameStats *gameStats = malloc(sizeof(gameStats));
            gameStats->playerOneScore = 0;
            gameStats->playerTwoScore = 0;
            //starts brand new game
            executeMainMenu(gameStats);
            //loop allows for multiple rounds of the same game
            while (play) {
                playGame(gameStats);
                executeEndMenu(gameStats, &play, &exit);
            }
        }
        else exit = 1;
    }
    endwin();
    return 0;
}

/*
 * The newGame() function asks the user if they would like to play a new game of connect four.
 * The function returns 1 if the user would like to play a new game, 0 if not.
 */
int newGame() {
    char answer;
    clear();
    printw("Welcome to Connect Four!\n");
    printw("Would you like to start a new game? (y/n): ");
    refresh();
    if(scanw("%c", &answer)) {
        //accepts lowercase or uppercase 'y' as yes
        if(answer == 'y' || answer == 'Y')
            return 1;
        //accepts lowercase or uppercase 'n' as no
        else if(answer == 'n' || answer == 'N')
            return 0;
        //the char entered was not 'y' or 'n'
        else {
            printw("\nError, please enter y to start a new game or n to exit.\n");
            getEnter();
            //call function again to get correct input, returns 0 + newGame() as the function has an int return type
            return 0 + newGame();
        }
    }
    //the value entered was not a char
    else {
        printw("\nError, please enter y to start a new game or n to exit.\n");
        getEnter();
        //calls function again to get correct input, returns 0 + newGame() as the function has an int return type
        return 0 + newGame();
    }
}