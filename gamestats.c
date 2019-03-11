//
// Created by Kayla Hamilton on 3/9/2019.
//

#include "gamestats.h"

void setxDimension(GameStats *gameStats, int xValue){
    gameStats->xDimension = xValue;
}

void setyDimension(GameStats *gameStats, int yValue) {
    gameStats->yDimension = yValue;
}

void setMode(GameStats *gameStats, int modeValue) {
    gameStats->mode = modeValue;
}

void updatePlayerOneScore(GameStats *gameStats) {
    gameStats->playerOneScore = gameStats->playerOneScore + 1;
}

void updatePlayerTwoScore(GameStats *gameStats) {
    gameStats->playerTwoScore = gameStats->playerTwoScore + 1;
}