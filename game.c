/*
 * Functions to play connect four game including user move capability, ai move capability,
 * and the ability to determine win status of the game.
 */

#include "gamestats.h"
#include "gameboard.h"
#include "graph.h"
#include "inputkeys.h"
#include "game.h"
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>

/*
 * The horizontalCheck() function checks for a horizontal win in the game board for the provided player piece.
 * The function is passed a pointer to the game board, x - the width of the board, y - the height of the board,
 * and playerPiece - the char representing the player piece.
 * The function returns 1 if there is a win, 0 if not.
 */
int horizontalCheck(char **gameBoard, int x, int y, char playerPiece) {
    //for each row
    for(int i = 0; i < y; i++) {
        int count = 0;
        //for each column
        for(int j = 0; j < x; j++) {
            //if piece found increment count
            if(gameBoard[i][(j * 3) + 1] == playerPiece)
                count++;
            //if piece not found, sequence potentially ended, reset count to 0
            else
                count = 0;
            //if count = 4, the game is won
            if(count == 4)
                return 1;
        }
    }
    return 0;
}

/*
 * The verticalCheck() function checks for a vertical win in the game board for the provided player piece.
 * The function is passed a pointer to the game board, x - the width of the board, y - the height of the board,
 * and playerPiece - the char representing the player piece.
 * The function returns 1 if there is a win, 0 if not.
 */
int verticalCheck(char **gameBoard, int x, int y, char playerPiece) {
    //for each column
    for(int i = 0; i < x; i ++) {
        int count = 0;
        //for each row
        for(int j = 0; j < y; j++) {
            //if piece found increment count
            if(gameBoard[j][(i * 3) + 1] == playerPiece)
                count++;
            //if piece not found, possible sequence broken, reset count to 0
            else
                count = 0;
            //if count = 4, the game is won
            if(count == 4)
                return 1;
        }
    }
    return 0;
}

/*
 * The diagonalCheck() function checks for a diagonal win in the game board for the provided player piece.
 * The function is passed a pointer to the game board, x - the width of the board, y - the height of the board,
 * and playerPiece - the char representing the player piece.
 * The function returns 1 if there is a win, 0 if not.
 */
int diagonalCheck(char **gameBoard, int x, int y, char playerPiece) {
    //for diagonals starting on the left side of the game board going down and right
    for(int i = 0; i < y; i++) {
        int tempX = 0, tempY = i, count = 0;
        while(tempX < x && tempY < y) {
            //if piece found increment count 1
            if(gameBoard[tempY][(tempX * 3) + 1] == playerPiece)
                count++;
            //if piece not found, possible sequence broken, reset count to 0
            else
                count = 0;
            //if count = 4, win found
            if(count == 4)
                return 1;
            //move the tempX and tempY diagonally right and down one
            tempX++;
            tempY++;
        }
    }
    //for diagonals starting on the top of the game board and going right and down
    for(int i = 1; i < x; i++) {
        int tempX = i, tempY = 0, count = 0;
        while(tempX < x && tempY < y) {
            //if piece found increment 1
            if(gameBoard[tempY][(tempX * 3) + 1] == playerPiece)
                count++;
            //if piece not found, possible sequence broken, reset count to 0
            else
                count = 0;
            //if count = 4, win found
            if(count == 4)
                return 1;
            //move the tempX and tempY diagonally right and down one
            tempX++;
            tempY++;
        }
    }
    //for diagonals starting on the right side of the game board going down and left
    for(int i = 0; i < y; i++) {
        int tempX = x - 1, tempY = i, count = 0;
        while(tempX >= 0 && tempY < y) {
            //if piece found increment count 1
            if(gameBoard[tempY][(tempX * 3) + 1] == playerPiece)
                count++;
            //if piece not found, possible sequence broken, reset count to 0
            else
                count = 0;
            //if count = 4, win found
            if(count == 4)
                return 1;
            //move the tempX and tempY diagonally left and down one
            tempX--;
            tempY++;
        }
    }
    //for diagonals starting on the top of the game board going left and down
    for(int i = x - 2; i > 0; i--) {
        int tempX = i, tempY = 0, count = 0;
        while(tempX >= 0 && tempY < y) {
            //if piece found, increment count 1
            if(gameBoard[tempY][(tempX * 3) + 1] == playerPiece)
                count++;
            //if piece not found, possible sequence broken, reset count to 0
            else
                count = 0;
            //if count = 4, win found
            if(count == 4)
                return 1;
            //move the tempX and tempY diagonally left and down one
            tempX--;
            tempY++;
        }
    }
    return 0;
}

/*
 * The checkForWin() function checks for a win in the game board for the provided player piece.
 * The function is passed a pointer to the game board, x - the width of the board, y - the height of the board,
 * and playerPiece - the char representing the player piece.
 * The function returns 1 if there is a win, 0 if not.
 */
int checkForWin(char **gameBoard, int x, int y, char playerPiece) {
    return (horizontalCheck(gameBoard, x, y, playerPiece) || verticalCheck(gameBoard, x, y, playerPiece) || diagonalCheck(gameBoard, x, y, playerPiece));
}

/*
 * The addSurroundingPieces() function checks all directly surrounding pieces (except for the piece directly above) for pieces of the same type that might help form a legal win,
 * and adds edges between the nodes in a graph.
 * The function is passed a pointer to the game board and relevant graph, the x dimension and y dimension of the board, the xPos and yPos of the piece to add edges to,
 * the char representing the player piece, and an integer representing whether the edges should be added in both directions or not.
 */
void addSurroundingPieces(char **gameBoard, struct Graph *graph, int x, int y, int xPos, int yPos, char playerPiece, int edgeToAdd) {
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

//The humanMove() function allows the user to make a move and play.
void humanMove(char **gameBoard, char *playerMove, struct Graph *graph, int x, int y, int playerNum, int mode, int scoreOne, int scoreTwo, char playerPiece) {
    int key, placed = 0, xPos = 0;
    //initialize playerMove back to 0
    setPlayerMove(playerMove, x, playerPiece);
    printHeader(playerNum);
    printPlayerMove(playerMove, x);
    printGameBoard(gameBoard, x, y);
    printScore(scoreOne, scoreTwo);
    keypad(stdscr, TRUE);
    //do not print to screen the values of the keys being pressed
    noecho();
    while(!placed) {
        //get value of key pressed
        key = getch();
        switch (key) {
            case KEY_LEFT:
                //if left arrow key and xPos of piece currently is greater than zero, move player piece left one
                if(xPos > 0)
                    updatePlayerMove(gameBoard, playerMove, x, y, xPos--, playerNum, scoreOne, scoreTwo, xPos, playerPiece);
                break;
            case KEY_RIGHT:
                //if right arrow key and xPos of piece currently is less than x-1, move player piece right one
                if(xPos < x - 1)
                    updatePlayerMove(gameBoard, playerMove, x, y, xPos++, playerNum, scoreOne, scoreTwo, xPos, playerPiece);
                break;
            case KEY_DOWN:
                placed = 1;
                //if down arrow key and at least one empty spot in the column, add piece to game board
                if(gameBoard[0][(xPos * 3) + 1] == ' ') {
                    int locFound = 0, yPos = y - 1;
                    //find lowest available yPos in the column
                    while(!locFound && yPos >= 0) {
                        if(gameBoard[yPos][(xPos * 3) + 1] == ' ')
                            locFound = 1;
                        else
                            yPos--;
                    }
                    updateGameBoard(gameBoard, playerMove, x, y, xPos, yPos, playerNum, playerPiece);
                    //if playing against ai, update the human player graph with the new piece
                    if(mode == 2)
                        addSurroundingPieces(gameBoard, graph, x, y, xPos, yPos, playerPiece, 2);
                }
                //if down arrow key, but no empty spot in the column is available
                else {
                    printw("\nThe column is full please choose a different one.\n");
                    getEnter();
                    humanMove(gameBoard, playerMove, graph, x, y, playerNum, mode, scoreOne, scoreTwo, playerPiece);
                }
            default:
                break;
        }
    }
    keypad(stdscr, FALSE);
}

/*
 * The willWin() function is a function to support the ai player,
 * and checks to see if a win will be achieved by playing a piece at the provided xPos and yPos.
 * The function returns 1 if the piece is a winning move, and 0 if not.
 */
int willWin(char **gameBoard, int x, int y, char playerNum, int xPos, int yPos) {
    int won = 0;
    //temporarily add piece to game board
    gameBoard[yPos][(xPos * 3) + 1] = playerNum;
    if(checkForWin(gameBoard, x, y, playerNum))
        won = 1;
    //remove piece from game board
    gameBoard[yPos][(xPos * 3) + 1] = ' ';
    return won;
}

//The makeAiMove() function is a function to support the ai player, and allows the ai to actually make its move.
void makeAiMove(char **gameBoard, char *playerMove, struct Graph *graph, int x, int y, int xPos, int yPos, int scoreOne, int scoreTwo) {
    setPlayerMove(playerMove, x, 'X');
    //update playerMove to clearly show where the ai has played
    updatePlayerMove(gameBoard, playerMove, x, y, 0, 2, scoreOne, scoreTwo, xPos, 'X');
    //update the game board with the piece
    updateGameBoard(gameBoard, playerMove, x, y, xPos, yPos, 2, 'X');
    printScore(scoreOne, scoreTwo);
    //notify the user that the ai has played
    printw("\nPlayer 2 has made their move.\n");
    getEnter();
    //add the newly played piece to the ai graph
    addSurroundingPieces(gameBoard, graph, x, y, xPos, yPos, 'X', 2);
}

//The aiMove() function is the main function that determines where the ai should play its piece and allows the ai to play.
void aiMove(char **gameBoard, char *playerMove, struct Graph *playerOneGraph, struct Graph *playerTwoGraph, int x, int y, int scoreOne, int scoreTwo) {
    int dfsLength1, dfsLength2, xPos1, xPos2, yPos1, yPos2, adjLength1, adjLength2, maxLength1 = -1, maxLength2 = -1, maxAdjLength1 = -1, maxAdjLength2 = -1;
    //check each potential position to play along the x axis of the game board
    for(int i = 0; i < x; i++) {
        int moveFound = 0, currentY = y - 1;
        //find the corresponding y position for the available move
        while(!moveFound && currentY >= 0) {
            if(gameBoard[currentY][(i * 3) + 1] == ' ') {
                moveFound = 1;
                //if the ai will win by playing at the position, play to win
                if(willWin(gameBoard, x, y, 'X', i, currentY)) {
                    makeAiMove(gameBoard, playerMove, playerTwoGraph, x, y, i, currentY, scoreOne, scoreTwo);
                    return;
                }
                //if the human player would win by playing at the position, play to block
                else if(willWin(gameBoard, x, y, 'O', i, currentY)) {
                    makeAiMove(gameBoard, playerMove, playerTwoGraph, x, y, i, currentY, scoreOne, scoreTwo);
                    return;
                }

                //find the opponent's best move by temporarily adding the piece to the opponent graph as if opponent were playing
                addSurroundingPieces(gameBoard, playerOneGraph, x, y, i, currentY, 'O', 1);
                //find the length of the DFS on that piece
                dfsLength1 = DFS(playerOneGraph, (x * currentY) + i);
                //find the length of the adjacency list for that piece
                adjLength1 = adjLength(playerOneGraph, (x * currentY) + i);
                //clear visited array and remove temporarily added nodes from the adjacency list
                clearVisited(playerOneGraph);
                freeAdjacencyList(playerOneGraph, (x * currentY) + i);

                //find the ai's best move by temporarily adding the piece to the ai graph
                addSurroundingPieces(gameBoard, playerTwoGraph, x, y, i, currentY, 'X', 1);
                //find the length of the DFS on that piece
                dfsLength2 = DFS(playerTwoGraph, (x * currentY) + i);
                //find the length of the adjacency list for that piece
                adjLength2 = adjLength(playerTwoGraph, (x * currentY) + i);
                //clear visited array and remove temporarily added nodes from the adjacency list
                clearVisited(playerTwoGraph);
                freeAdjacencyList(playerTwoGraph, (x * currentY) + i);

                //if the opponent DFS is longer or equal to the previous longest with a longer adjacency list, the move is better
                if(dfsLength1 > maxLength1 || (dfsLength1 == maxLength1 && adjLength1 > maxAdjLength1)) {
                    //update max lengths
                    maxLength1 = dfsLength1;
                    maxAdjLength1 = adjLength1;
                    //update best move,
                    xPos1 = i;
                    yPos1 = currentY;
                }
                //if the ai DFS is longer or equal to the previous longest with a longer adjacency list, the move is better
                if(dfsLength2 > maxLength2 || (dfsLength2 == maxAdjLength2 && adjLength2 > maxAdjLength2)) {
                    //update max lengths
                    maxLength2 = dfsLength2;
                    maxAdjLength2 = adjLength2;
                    //update best move
                    xPos2 = i;
                    yPos2 = currentY;
                }
            }
            //if position not found
            else
                currentY--;
        }
    }
    //if no useful move was found for the ai, play the opponent's best move
    if(maxLength2 == 0)
        makeAiMove(gameBoard, playerMove, playerTwoGraph, x, y, xPos1, yPos1, scoreOne, scoreTwo);
    //else play the ai's best move
    else
        makeAiMove(gameBoard, playerMove, playerTwoGraph, x, y, xPos2, yPos2, scoreOne, scoreTwo);
}

//The congratulateWinner() function outputs who won the current game of connect four.
void congratulateWinner(int playerNum){
    clear();
    printw("Player %d has won the game!\n", playerNum);
    getEnter();
}

//The tieGame() function outputs that the game was a tie.
void tieGame() {
    clear();
    printw("The game is a tie.\n");
    getEnter();
}

/*
 * The playGame() function handles the the sequence of plays in the game, updates the scores at the end of the game,
 * and frees the memory no longer needed at the end of the game.
 */
void playGame(struct GameStats *gameStats) {
    int x = gameStats->xDimension;
    int y = gameStats->yDimension;
    int mode = gameStats->mode;
    int gameWon = 0;
    //create new game board, player move, player one graph, and player two graph
    char **gameBoard = createGameBoard(x, y);
    char *playerMove = createPlayerMove(x);
    struct Graph *playerOneGraph;
    playerOneGraph = createGraph(x * y);
    struct Graph *playerTwoGraph;
    playerTwoGraph = createGraph(x * y);
    //while the game has not been won
    while(!gameWon) {
        //checks to see if the board is full
        if(boardFull(gameBoard, x)) {
            gameWon = 1;
            tieGame();
        }
        //if player two hasn't won,  allow player one to make a move
        else if(!checkForWin(gameBoard, x, y, 'X')) {
            humanMove(gameBoard, playerMove, playerOneGraph, x, y, 1, gameStats->mode, gameStats->playerOneScore,
                      gameStats->playerTwoScore, 'O');
            //check to see if the board is full
            if(boardFull(gameBoard, x)) {
                gameWon = 1;
                tieGame();
            }
            //if player one hasn't won and the mode is player vs. player, allow player two to make a move
            else if (!checkForWin(gameBoard, x, y, 'O') && mode == 1)
                humanMove(gameBoard, playerMove, playerTwoGraph, x, y, 2, gameStats->mode, gameStats->playerOneScore,
                          gameStats->playerTwoScore, 'X');
            //if player one hasn't won and the mode is player vs. ai, allow the ai to make a move
            else if(!checkForWin(gameBoard, x, y, 'O') && mode == 2)
                aiMove(gameBoard, playerMove, playerOneGraph, playerTwoGraph, x, y, gameStats->playerOneScore, gameStats->playerTwoScore);
            //player one has won
            else {
                updatePlayerOneScore(gameStats);
                congratulateWinner(1);
                gameWon = 1;
            }
        }
        //player two has won
        else {
            updatePlayerTwoScore(gameStats);
            congratulateWinner(2);
            gameWon = 1;
        }
    }
    //free memory allocated for the graphs, player move, and game board
    freeGraph(playerOneGraph);
    freeGraph(playerTwoGraph);
    freePlayerMove(playerMove);
    freeGameBoard(gameBoard, y);
}