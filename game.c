//
// Created by Kayla Hamilton on 3/11/2019.
//

#include "gamestats.h"
#include "gameboard.h"
#include "graph.h"
#include "game.h"
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>

int horizontalCheck(char **gameBoard, int x, int y, char playerPiece) {
    for(int i = 0; i < y; i++) {
        int count = 0;
        for(int j = 0; j < x; j++) {
            if(gameBoard[i][(j * 3) + 1] == playerPiece)
                count++;
            else
                count = 0;
            if(count == 4)
                return 1;
        }
    }
    return 0;
}

int verticalCheck(char **gameBoard, int x, int y, char playerPiece) {
    for(int i = 0; i < x; i ++) {
        int count = 0;
        for(int j = 0; j < y; j++) {
            if(gameBoard[j][(i * 3) + 1] == playerPiece)
                count++;
            else
                count = 0;
            if(count == 4)
                return 1;
        }
    }
    return 0;
}

int diagonalCheck(char **gameBoard, int x, int y, char playerPiece) {
    for(int i = 0; i < y; i++) {
        int tempX = 0, tempY = i, count = 0;
        while(tempX < x && tempY < y) {
            if(gameBoard[tempY][(tempX * 3) + 1] == playerPiece)
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
            if(gameBoard[tempY][(tempX * 3) + 1] == playerPiece)
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
            if(gameBoard[tempY][(tempX * 3) + 1] == playerPiece)
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
            if(gameBoard[tempY][(tempX * 3) + 1] == playerPiece)
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

int checkForWin(char **gameBoard, int x, int y, char playerPiece) {
    return (horizontalCheck(gameBoard, x, y, playerPiece) || verticalCheck(gameBoard, x, y, playerPiece) || diagonalCheck(gameBoard, x, y, playerPiece));
}

void addSurroundingPieces(char **gameBoard, struct Graph *graph, int x, int y, int xPos, int yPos, char playerPiece,
                          int edgeToAdd) {
    if((xPos-1 >= 0) && (yPos-1 >= 0) && gameBoard[yPos-1][((xPos-1) * 3) + 1] == playerPiece)
        updateEdge(graph, ((x * yPos) + xPos), ((x * (yPos-1)) + (xPos-1)), edgeToAdd);
    if((xPos+1 < x) && (yPos-1 >= 0) && gameBoard[yPos-1][((xPos+1) * 3) + 1] == playerPiece)
        updateEdge(graph, ((x * yPos) + xPos), ((x * (yPos-1)) + (xPos+1)), edgeToAdd);
    if((xPos-1 >= 0) && gameBoard[yPos][((xPos-1) * 3) + 1] == playerPiece)
        updateEdge(graph, ((x * yPos) + xPos), ((x * yPos) + (xPos-1)), edgeToAdd);
    if((xPos+1 < x) && gameBoard[yPos][((xPos+1) * 3) + 1] == playerPiece)
        updateEdge(graph, ((x * yPos) + xPos), ((x * yPos) + (xPos-1)), edgeToAdd);
    if((xPos-1 >= 0) && (yPos+1 < y) && gameBoard[yPos+1][((xPos-1) * 3) + 1] == playerPiece)
        updateEdge(graph, ((x * yPos) + xPos), ((x * (yPos+1)) + (xPos-1)), edgeToAdd);
    if((yPos+1 < y) && gameBoard[yPos+1][(xPos * 3) + 1] == playerPiece)
        updateEdge(graph, ((x * yPos) + xPos), ((x * (yPos+1)) + xPos), edgeToAdd);
    if((xPos+1 < x) && (yPos+1 < y) && gameBoard[yPos+1][((xPos+1) * 3) + 1] == playerPiece)
        updateEdge(graph, ((x * yPos) + xPos), ((x * (yPos+1)) + (xPos+1)), edgeToAdd);
}

void humanMove(char **gameBoard, char *playerMove, struct Graph *graph, int x, int y, int playerNum, int mode, int scoreOne,
               int scoreTwo, char playerPiece) {
    int key, placed = 0, xPos = 0;
    setPlayerMove(playerMove, x, playerPiece);
    printHeader(playerNum);
    printPlayerMove(playerMove, x);
    printGameBoard(gameBoard, x, y);
    printScore(scoreOne, scoreTwo);
    keypad(stdscr, TRUE);
    noecho();
    while(!placed) {
        key = getch();
        switch (key) {
            case KEY_LEFT:
                if(xPos > 0)
                    updatePlayerMove(gameBoard, playerMove, x, y, xPos--, playerNum, scoreOne, scoreTwo, xPos, playerPiece);
                break;
            case KEY_RIGHT:
                if(xPos < x - 1)
                    updatePlayerMove(gameBoard, playerMove, x, y, xPos++, playerNum, scoreOne, scoreTwo, xPos, playerPiece);
                break;
            case KEY_DOWN:
                placed = 1;
                if(gameBoard[0][(xPos * 3) + 1] == ' ') {
                    int locFound = 0, yPos = y - 1;
                    while(!locFound && yPos >= 0) {
                        if(gameBoard[yPos][(xPos * 3) + 1] == ' ')
                            locFound = 1;
                        else
                            yPos--;
                    }
                    updateGameBoard(gameBoard, playerMove, x, y, xPos, yPos, playerNum, playerPiece);
                    if(mode == 2) {
                        addSurroundingPieces(gameBoard, graph, x, y, xPos, yPos, playerPiece, 2);
                    }
                }
                else {
                    printw("\nThe column is full please choose a different one.\n");
                    printw("Press any key to continue.");
                    refresh();
                    getch();
                    humanMove(gameBoard, playerMove, graph, x, y, playerNum, mode, scoreOne, scoreTwo, playerPiece);
                }
            default:
                break;
        }
    }
    keypad(stdscr, FALSE);
}

int willWin(char **gameBoard, int x, int y, char playerNum, int xPos, int yPos) {
    int won = 0;
    gameBoard[yPos][(xPos * 3) + 1] = playerNum;
    if(checkForWin(gameBoard, x, y, playerNum))
        won = 1;
    gameBoard[yPos][(xPos * 3) + 1] = ' ';
    return won;
}

void makeAiMove(char **gameBoard, char *playerMove, struct Graph *graph, int x, int y,
                int xPos, int yPos, int scoreOne, int scoreTwo) {
    setPlayerMove(playerMove, x, 'X');
    updatePlayerMove(gameBoard, playerMove, x, y, 0, 2, scoreOne, scoreTwo, xPos, 'X');
    updateGameBoard(gameBoard, playerMove, x, y, xPos, yPos, 2, 'X');
    printScore(scoreOne, scoreTwo);
    printw("\nPlayer 2 has made their move. Press enter to continue.\n");
    refresh();
    getch();
    addSurroundingPieces(gameBoard, graph, x, y, xPos, yPos, 'X', 2);
}

void aiMove(char **gameBoard, char *playerMove, struct Graph *playerOneGraph, struct Graph *playerTwoGraph, int x, int y, int scoreOne, int scoreTwo) {
    int dfsLength1, dfsLength2, xPos1, xPos2, yPos1, yPos2, adjLength1, adjLength2, maxLength1 = -1, maxLength2 = -1, maxAdjLength1 = -1, maxAdjLength2 = -1;
    for(int i = 0; i < x; i++) {
        int moveFound = 0, currentY = y - 1;
        while(!moveFound && currentY >= 0) {
            if(gameBoard[currentY][(i * 3) + 1] == ' ') {
                moveFound = 1;
                if(willWin(gameBoard, x, y, 'X', i, currentY)) {
                    makeAiMove(gameBoard, playerMove, playerTwoGraph, x, y, i, currentY, scoreOne, scoreTwo);
                    return;
                }
                else if(willWin(gameBoard, x, y, 'O', i, currentY)) {
                    makeAiMove(gameBoard, playerMove, playerTwoGraph, x, y, i, currentY, scoreOne, scoreTwo);
                    return;
                }
                addSurroundingPieces(gameBoard, playerOneGraph, x, y, i, currentY, 'O', 1);
                addSurroundingPieces(gameBoard, playerTwoGraph, x, y, i, currentY, 'X', 1);
                dfsLength1 = DFS(playerOneGraph, (x * currentY) + i);
                dfsLength2 = DFS(playerTwoGraph, (x * currentY) + i);
                adjLength1 = adjLength(playerOneGraph, (x * currentY) + i);
                adjLength2 = adjLength(playerTwoGraph, (x * currentY) + i);
                clearVisited(playerOneGraph);
                clearVisited(playerTwoGraph);
                freeAdjacencyList(playerOneGraph, (x * currentY) + i);
                freeAdjacencyList(playerTwoGraph, (x * currentY) + i);
                if(dfsLength1 > maxLength1 || (dfsLength1 == maxLength1 && adjLength1 > maxAdjLength1)) {
                    maxLength1 = dfsLength1;
                    maxAdjLength1 = adjLength1;
                    xPos1 = i;
                    yPos1 = currentY;
                }
                if(dfsLength2 > maxLength2 || (dfsLength2 == maxAdjLength2 && adjLength2 > maxAdjLength2)) {
                    maxLength2 = dfsLength2;
                    maxAdjLength2 = adjLength2;
                    xPos2 = i;
                    yPos2 = currentY;
                }
            }
            else
                currentY--;
        }
    }
    if(maxLength2 == 0)
        makeAiMove(gameBoard, playerMove, playerTwoGraph, x, y, xPos1, yPos1, scoreOne, scoreTwo);
    else
        makeAiMove(gameBoard, playerMove, playerTwoGraph, x, y, xPos2, yPos2, scoreOne, scoreTwo);
}

void congratulateWinner(int playerNum){
    clear();
    printw("Player %d has won the game!\n", playerNum);
    printw("Press any key to continue.");
    refresh();
    getch();
}

void tieGame() {
    clear();
    printw("The game is a tie.\n");
    printw("Press any key to continue.");
    refresh();
    getch();
}

void playGame(struct GameStats *gameStats) {
    int x = gameStats->xDimension;
    int y = gameStats->yDimension;
    int mode = gameStats->mode;
    int gameWon = 0;
    char **gameBoard = createGameBoard(x, y);
    char *playerMove = createPlayerMove(x);
    struct Graph *playerOneGraph;
    playerOneGraph = createGraph(x * y);
    struct Graph *playerTwoGraph;
    playerTwoGraph = createGraph(x * y);
    while(!gameWon) {
        if(boardFull(gameBoard, x)) {
            gameWon = 1;
            tieGame();
        }
        else if(!checkForWin(gameBoard, x, y, 'X')) {
            humanMove(gameBoard, playerMove, playerOneGraph, x, y, 1, gameStats->mode, gameStats->playerOneScore,
                      gameStats->playerTwoScore, 'O');
            if(boardFull(gameBoard, x)) {
                gameWon = 1;
                tieGame();
            }
            else if (!checkForWin(gameBoard, x, y, 'O') && mode == 1)
                humanMove(gameBoard, playerMove, playerTwoGraph, x, y, 2, gameStats->mode, gameStats->playerOneScore,
                          gameStats->playerTwoScore, 'X');
            else if(!checkForWin(gameBoard, x, y, 'O') && mode == 2)
                aiMove(gameBoard, playerMove, playerOneGraph, playerTwoGraph, x, y, gameStats->playerOneScore, gameStats->playerTwoScore);
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
    freeGraph(playerOneGraph);
    freeGraph(playerTwoGraph);
    freePlayerMove(playerMove);
    freeGameBoard(gameBoard, y);
}