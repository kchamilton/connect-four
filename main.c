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
    while(!exit) {
        if(newGame()) {
            int play = 1;
            //new gameStats
            struct GameStats *gameStats = malloc(sizeof(gameStats));
            gameStats->playerOneScore = 0;
            gameStats->playerTwoScore = 0;
            executeMainMenu(gameStats);
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

int newGame() {
    char answer;
    clear();
    printw("Welcome to Connect Four!\n");
    printw("Would you like to start a new game? (y/n): ");
    refresh();
    if(scanw("%c", &answer)) {
        if(answer == 'y' || answer == 'Y')
            return 1;
        else if(answer == 'n' || answer == 'N')
            return 0;
        else {
            printw("\nError, please enter y to start a new game or n to exit.\n");
            getEnter();
            return 0 + newGame();
        }
    }
    else {
        printw("\nError, please enter y to start a new game or n to exit.\n");
        getEnter();
        return 0 + newGame();
    }
}