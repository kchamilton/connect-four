//
// Created by Kayla Hamilton on 3/11/2019.
//

#include "gamestats.h"
#include "gameboard.h"
#include "game.h"
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>

int horizontalCheck(char **gameBoard, int x, int y, int playerNum) {
    for(int i = 0; i < y; i++) {
        int count = 0;
        for(int j = 0; j < x; j++) {
            if(gameBoard[i][(j * 3) + 1] == (playerNum + '0'))
                count++;
            else
                count = 0;
            if(count == 4)
                return 1;
        }
    }
    return 0;
}

int verticalCheck(char **gameBoard, int x, int y, int playerNum) {
    for(int i = 0; i < x; i ++) {
        int count = 0;
        for(int j = 0; j < y; j++) {
            if(gameBoard[j][(i * 3) + 1] == (playerNum + '0'))
                count++;
            else
                count = 0;
            if(count == 4)
                return 1;
        }
    }
    return 0;
}

int diagonalCheck(char **gameBoard, int x, int y, int playerNum) {
    for(int i = 0; i < y; i++) {
        int tempX = 0, tempY = i, count = 0;
        while(tempX < x && tempY < y) {
            if(gameBoard[tempY][(tempX * 3) + 1] == (playerNum + '0'))
                count++;
            else
                count = 0;
            if(count == 4)
                return 1;
            tempX++;
            tempY++;
        }
    }
    for(int i = 1; i < x; i++) {
        int tempX = i, tempY = 0, count = 0;
        while(tempX < x && tempY < y) {
            if(gameBoard[tempY][(tempX * 3) + 1] == (playerNum + '0'))
                count++;
            else
                count = 0;
            if(count == 4)
                return 1;
            tempX++;
            tempY++;
        }
    }
    for(int i = 0; i < y; i++) {
        int tempX = x - 1, tempY = i, count = 0;
        while(tempX >= 0 && tempY < y) {
            if(gameBoard[tempY][(tempX * 3) + 1] == (playerNum + '0'))
                count++;
            else
                count = 0;
            if(count == 4)
                return 1;
            tempX--;
            tempY++;
        }
    }
    for(int i = x - 2; i > 0; i--) {
        int tempX = i, tempY = 0, count = 0;
        while(tempX >= 0 && tempY < y) {
            if(gameBoard[tempY][(tempX * 3) + 1] == (playerNum + '0'))
                count++;
            else
                count = 0;
            if(count == 4)
                return 1;
            tempX--;
            tempY++;
        }
    }
    return 0;
}

int checkForWin(char **gameBoard, int x, int y, int playerNum) {
    return (horizontalCheck(gameBoard, x, y, playerNum) || verticalCheck(gameBoard, x, y, playerNum) || diagonalCheck(gameBoard, x, y, playerNum));
}

void makeMove(char **gameBoard, char *playerMove, int x, int y, int playerNum, int scoreOne, int scoreTwo) {
    int key, placed = 0;
    setPlayerMove(playerMove, x);
    printHeader(playerNum);
    printPlayerMove(playerMove, x);
    printGameBoard(gameBoard, x, y);
    printScore(scoreOne, scoreTwo);
    int location = 0;
    keypad(stdscr, TRUE);
    noecho();
    while(!placed) {
        key = getch();
        switch (key) {
            case KEY_LEFT:
                if(location > 0)
                    updatePlayerMove(gameBoard, playerMove, x, y, location--, playerNum, scoreOne, scoreTwo, -1);
                break;
            case KEY_RIGHT:
                if(location < x - 1)
                    updatePlayerMove(gameBoard, playerMove, x, y, location++, playerNum, scoreOne, scoreTwo, 1);
                break;
            case KEY_DOWN:
                placed = 1;
                if(gameBoard[0][(location * 3) + 1] == ' ') {
                    updateGameBoard(gameBoard, playerMove, x, y, location, playerNum);
                }
                else {
                    printw("\nThe column is full please choose a different one.\n");
                    printw("Press any key to continue.");
                    refresh();
                    getch();
                    makeMove(gameBoard, playerMove, x, y, playerNum, scoreOne, scoreTwo);
                }
            default:
                break;
        }
    }
    keypad(stdscr, FALSE);
}

void congratulateWinner(int playerNum){
    clear();
    printw("Congratulations Player %d, you won the game!\n", playerNum);
    printw("Press any key to continue.");
    refresh();
    getch();
}

void playGame(struct GameStats *gameStats) {
    int x = gameStats->xDimension;
    int y = gameStats->yDimension;
    int gameWon = 0;
    char **gameBoard = createGameBoard(x, y);
    char *playerMove = createPlayerMove(x);
    while(!gameWon) {
        if(!checkForWin(gameBoard, x, y, 2)) {
            makeMove(gameBoard, playerMove, x, y, 1, gameStats->playerOneScore, gameStats->playerTwoScore);
            if (!checkForWin(gameBoard, x, y, 1))
                makeMove(gameBoard, playerMove, x, y, 2, gameStats->playerOneScore, gameStats->playerTwoScore);
            else {
                updatePlayerOneScore(gameStats);
                congratulateWinner(1);
                gameWon = 1;
            }
        }
        else {
            updatePlayerTwoScore(gameStats);
            congratulateWinner(2);
            gameWon = 1;
        }
    }
    freePlayerMove(playerMove);
    freeGameBoard(gameBoard, y);
}