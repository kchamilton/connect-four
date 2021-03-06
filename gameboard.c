/*
 * Functions to allocate memory for and create the game board and player move,
 * print the main game header, player move, game board, and scores,
 * and free the memory allocated to game board and player move.
 * The x dimension of the board is always multiplied by 3 to account for the two bracket characters ('[' and ']')
 * used in each column to better display the game board.
 * -> to get the correct x position to place the game piece, the desired x location = (xPos * 3) + 1
 */

#include "gameboard.h"
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>

//The printHeader() function prints the main game header and directions on how to add the game piece to the board.
void printHeader(int playerNum) {
    clear();
    printw("Connect Four\n");
    printw("Use the left and right arrow keys to select the column, \npress the down arrow key to drop the piece.\n");
    printw("Player %d's turn.\n\n", playerNum);
    refresh();
}

//The printScore() function prints the current score of the game.
void printScore(int playerOneScore, int playerTwoScore) {
    printw("\nPlayer 1 (O): %d  vs.  Player 2 (X): %d\n", playerOneScore, playerTwoScore);
}

/* The createPlayerMove() function allocates space for the player move array.
 * The function returns a pointer to the new playerMove
*/
char *createPlayerMove(int x) {
    char *playerMove = malloc(x * 3 * sizeof(char));
    return playerMove;
}

//The setPlayerMove() function resets the player move array to display the game piece above the first column.
void setPlayerMove(char *playerMove, int x, char playerPiece) {
    for(int i = 0; i < x * 3; i ++)
        playerMove[i] = ' ';
    playerMove[1] = playerPiece;
}

//The printPlayerMove() function prints the player move array to show which column the player's piece is currently above.
void printPlayerMove(char *playerMove, int x) {
    for(int i = 0; i < x * 3; i++)
        printw("%c", playerMove[i]);
    printw("\n");
    refresh();
}

//The updatePlayerMove() function updates the location of the player piece over the game board as the player moves it back and forth.
void updatePlayerMove(char **gameBoard, char *playerMove, int x, int y, int location, int playerNum, int scoreOne,
                      int scoreTwo, int newLocation, char playerPiece) {
    //set previous position to ' '
    playerMove[(location * 3) + 1] = ' ';
    //set new position to player piece
    playerMove[(newLocation * 3) + 1] = playerPiece;
    clear();
    printHeader(playerNum);
    printPlayerMove(playerMove, x);
    printGameBoard(gameBoard, x, y);
    printScore(scoreOne, scoreTwo);
    refresh();
}

//The freePlayerMove() function frees the memory allocated for the playerMove array.
void freePlayerMove(char *playerMove) {
    free(playerMove);
}

/* The createGameBoard() function allocates space for the game board and initializes the setup of the board.
 * The function returns a pointer to the new game board.
*/
char **createGameBoard(int x, int y) {
    char **gameBoard;
    //allocate memory for the game board
    gameBoard = malloc(y * sizeof(char *));
    for(int i = 0; i < y; i++) {
        gameBoard[i] = malloc(x * 3 * sizeof(char));
    }
    //count keeps track of position to create [ ] game board pattern
    int count = 0;
    for(int i = 0; i < y; i++) {
        for(int j = 0; j < (x * 3); j++) {
            //adds left bracket '['
            if(count == 0) {
                gameBoard[i][j] = '[';
                count++;
            }
            //adds space ' ', position for game piece to be added later
            else if(count == 1) {
                gameBoard[i][j] = ' ';
                count++;
            }
            //adds right bracket ']'
            else {
                gameBoard[i][j] = ']';
                count = 0;
            }
        }
    }
    return gameBoard;
}

//The updateGameBoard() function adds a player piece to the game board and then reprints the header, player move array, and game board.
void updateGameBoard(char **gameBoard, char *playerMove, int x, int y, int xPos, int yPos, int playerNum, char playerPiece) {
    gameBoard[yPos][(xPos * 3) + 1] = playerPiece;
    clear();
    printHeader(playerNum);
    printPlayerMove(playerMove, x);
    printGameBoard(gameBoard, x, y);
}

//The boardFull() function checks to see if the game board is full and returns 1 if it is, 0 if there is still space to play.
int boardFull(char **gameBoard, int x) {
    //assume board is full
    int full = 1;
    for(int i = 0; i < x; i++) {
        //if empty spot is found
        if(gameBoard[0][(i * 3) + 1] == ' ')
            full = 0;
    }
    return full;
}

//The printGameBoard() function prints the game board.
void printGameBoard(char **gameBoard, int x, int y) {
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x * 3; j++){
            printw("%c", gameBoard[i][j]);
        }
        printw("\n");
    }
    refresh();
}

//The freeGameBoard() function frees the memory allocated for the game board.
void freeGameBoard(char **gameBoard, int y) {
    for(int i = 0; i < y; i++){
        free(gameBoard[i]);
    }
    free(gameBoard);
}