#ifndef CONNECT_FOUR_GAMEBOARD_H
#define CONNECT_FOUR_GAMEBOARD_H

void printHeader(int playerNum);
void printScore(int playerOneScore, int playerTwoScore);
char *createPlayerMove(int x);
void setPlayerMove(char *playerMove, int x, char playerPiece);
void printPlayerMove(char *playerMove, int x);
void updatePlayerMove(char **gameBoard, char *playerMove, int x, int y, int location, int playerNum, int scoreOne,
                      int scoreTwo, int newLocation, char playerPiece);
void freePlayerMove(char *playerMove);
char **createGameBoard(int x, int y);
void updateGameBoard(char **gameBoard, char *playerMove, int x, int y, int xPos, int yPos, int playerNum, char playerPiece);
int boardFull(char **gameBoard, int x);
void printGameBoard(char **gameBoard, int x, int y);
void freeGameBoard(char **gameBoard, int y);

#endif //CONNECT_FOUR_GAMEBOARD_H
