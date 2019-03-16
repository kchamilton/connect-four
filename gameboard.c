//
// Created by Kayla Hamilton on 3/11/2019.
//

#include "gameboard.h"
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>

void printHeader(int playerNum) {
    clear();
    printw("Connect Four\n");
    printw("Use the left and right arrow keys to select the column, press the down arrow key to drop the piece.\n");
    printw("Player %d's turn.\n\n", playerNum);
    refresh();
}

void printScore(int playerOneScore, int playerTwoScore) {
    printw("\nPlayer 1: %d  vs.  Player 2: %d\n", playerOneScore, playerTwoScore);
}

char *createPlayerMove(int x) {
    char *playerMove = malloc(x * 3 * sizeof(char));
    return playerMove;
}

void setPlayerMove(char *playerMove, int x) {
    for(int i = 0; i < x * 3; i ++)
        playerMove[i] = ' ';
    playerMove[1] = 'O';
}

void printPlayerMove(char *playerMove, int x) {
    for(int i = 0; i < x * 3; i++)
        printw("%c", playerMove[i]);
    printw("\n");
    refresh();
}

void updatePlayerMove(char **gameBoard, char *playerMove, int x, int y, int location, int playerNum, int scoreOne, int scoreTwo, int newLocation) {
    playerMove[(location * 3) + 1] = ' ';
    playerMove[(newLocation * 3) + 1] = 'O';
    clear();
    printHeader(playerNum);
    printPlayerMove(playerMove, x);
    printGameBoard(gameBoard, x, y);
    printScore(scoreOne, scoreTwo);
    refresh();
}

void freePlayerMove(char *playerMove) {
    free(playerMove);
}

char **createGameBoard(int x, int y) {
    char **gameBoard;
    gameBoard = malloc(y * sizeof(char *));
    for(int i = 0; i < y; i++) {
        gameBoard[i] = malloc(x * 3 * sizeof(char));
    }
    int count = 0;
    for(int i = 0; i < y; i++) {
        for(int j = 0; j < (x * 3); j++) {
            if(count == 0) {
                gameBoard[i][j] = '[';
                count++;
            }
            else if(count == 1) {
                gameBoard[i][j] = ' ';
                count++;
            }
            else {
                gameBoard[i][j] = ']';
                count = 0;
            }
        }
    }
    return gameBoard;
}

void updateGameBoard(char **gameBoard, char *playerMove, int x, int y, int xPos, int yPos, int playerNum) {
    gameBoard[yPos][(xPos * 3) + 1] = playerNum + '0';
    clear();
    printHeader(playerNum);
    printPlayerMove(playerMove, x);
    printGameBoard(gameBoard, x, y);
}

int boardFull(char **gameBoard, int x) {
    int full = 1;
    for(int i = 0; i < x; i++) {
        if(gameBoard[0][(i * 3) + 1] == ' ')
            full = 0;
    }
    return full;
}

void printGameBoard(char **gameBoard, int x, int y) {
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x * 3; j++){
            printw("%c", gameBoard[i][j]);
        }
        printw("\n");
    }
    refresh();
}

void freeGameBoard(char **gameBoard, int y) {
    for(int i = 0; i < y; i++){
        free(gameBoard[i]);
    }
    free(gameBoard);
}