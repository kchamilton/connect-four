/*
 * Functions to implement and run end menu/end of game tasks.
 */

#include "gamestats.h"
#include "inputkeys.h"
#include "mainmenu.h"
#include "endmenu.h"
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>

/*
 * The replayOptions() function gets user input about what to do next after a game is over (rematch, return to main menu, or exit).
 * Returns the integer value of the option selected by the user.
 */
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
    //if valid input, return the desired option
    if(scanw("%d", &answer) && (answer == 1 || answer == 2 || answer == 3))
        return answer;
    //the value entered was not 1, 2, or 3
    else {
        printw("\nError, please enter 1, 2, or 3 to proceed.\n");
        getEnter();
        //calls function again to get correct input, returns 0 + replayOptions() as the function has an int return type
        return 0 + replayOptions();
    }
}

/*
 * The likeToResize() function gets user input on resizing the game board for a rematch.
 * The function returns 1 if the user would lke to resize the game board, 0 if not.
 */
int likeToResize() {
    char answer;
    printw("Would you like to change the game board dimensions? (y/n): ");
    refresh();
    if(scanw("%c", &answer)) {
        if(answer == 'y' || answer == 'Y')
            return 1;
        else if(answer == 'n' || answer == 'N')
            return 0;
        //the value entered was not 'y' or 'n'
        else {
            printw("\nError, please enter y to change the game board dimensions or n to leave them the same.\n");
            getEnter();
            //calls function again to get correct input, returns 0 + likeToResize() as the function has an int return type
            return 0 + likeToResize();
        }
    }
    //the value entered was not a char
    else {
        printw("\nError, please enter y to change the game board dimensions or n to leave them the same.\n");
        getEnter();
        //calls function again to get correct input, returns 0 + likeToResize() as the function has an int return type
        return 0 + likeToResize();
    }
}

/*
 * The executeEndMenu() function get user input about how to proceed once the game has finished.
 * The function is passed the struct GameStats to update the board size for a rematch,
 * or to free the memory allocated if user does not want a rematch.
 */
void executeEndMenu(struct GameStats *gameStats, int *play, int *exit){
    clear();
    //gets desired option from user
    int option = replayOptions();
    //if rematch, get user input on resizing the game board
    if(option == 1) {
        if(likeToResize())
            selectBoardSize(gameStats);
    }
    //if return to main menu, set play to 0 to stop loop of matches
    else if(option == 2) {
        *play = 0;
        free(gameStats);
    }
    //if exit, set play to 0 to stop loop of matches, and set exit to 1 to exit game loop
    else {
        *play = 0;
        *exit = 1;
        free(gameStats);
    }
}

