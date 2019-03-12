//
// Created by Kayla Hamilton on 3/11/2019.
//

#include "gamestats.h"
#include "gameboard.h"
#include "game.h"
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>


void makeMove(char **gameBoard, char *playerMove, int x, int y) {
    int key, placed = 0;
    setPlayerMove(playerMove, x);
    printHeader();
    printPlayerMove(playerMove, x);
    printGameBoard(gameBoard, x, y);
    int location = 0;
    keypad(stdscr, TRUE);
    noecho();
    while(!placed) {
        key = getch();
        switch (key) {
            case KEY_LEFT:
                if(location > 0)
                    updatePlayerMove(gameBoard, playerMove, x, y, location--, -1);
                break;
            case KEY_RIGHT:
                if(location < x - 1)
                    updatePlayerMove(gameBoard, playerMove, x, y, location++, 1);
                break;
            case KEY_DOWN:
                placed = 1;
                updateGameBoard(gameBoard, playerMove, x, y, location);
            default:
                break;
        }
    }
    keypad(stdscr, FALSE);
    echo();
}

void playGame(struct GameStats *gameStats) {
    int x = gameStats->xDimension;
    int y = gameStats->yDimension;
    char **gameBoard = createGameBoard(x, y);
    char *playerMove = createPlayerMove(x);
    makeMove(gameBoard, playerMove, x, y);
    freePlayerMove(playerMove);
    freeGameBoard(gameBoard, y);
    getch();
}