//
// Created by Kayla Hamilton on 3/11/2019.
//

#include "gameboard.h"
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>

void printHeader() {
    clear();
    printw("Connect Four\n");
    printw("Use the left and right arrow keys to select the column, press the down arrow key to drop the piece.\n\n");
    refresh();
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

void updatePlayerMove(char **gameBoard, char *playerMove, int x, int y, int location, int direction) {
    playerMove[(location * 3) + 1] = ' ';
    if(direction < 0) {
        playerMove[(--location * 3) + 1] = 'O';
    }
    else {
        playerMove[(++location * 3) + 1] = 'O';
    }
    clear();
    printHeader();
    printPlayerMove(playerMove, x);
    printGameBoard(gameBoard, x, y);
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

void updateGameBoard(char **gameBoard, char *playerMove, int x, int y, int location) {
    int placed = 0, currentLoc = y - 1;
    while(!placed && currentLoc >= 0) {
        if(gameBoard[currentLoc][(location * 3) + 1] == ' ') {
            gameBoard[currentLoc][(location * 3) + 1] = 'O';
            placed = 1;
        }
        else
            currentLoc--;
    }
    clear();
    printHeader();
    printPlayerMove(playerMove, x);
    printGameBoard(gameBoard, x, y);
}

void printGameBoard(char **gameBoard, int x, int y) {
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x * 3; j++){
            printw("%c", gameBoard[i][j]);
        }
        printw("\n");
    }
    refresh();
    //getch();
}

void freeGameBoard(char **gameBoard, int y) {
    for(int i = 0; i < y; i++){
        free(gameBoard[i]);
    }
    free(gameBoard);
}