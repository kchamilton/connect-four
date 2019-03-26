//
// Created by Kayla Hamilton on 3/9/2019.
//

#ifndef CONNECT_FOUR_GAMESTATS_H
#define CONNECT_FOUR_GAMESTATS_H

/*
 * The struct GameStats stores important game information such as board dimensions, mode, and scores.
 */
typedef struct GameStats {
    int xDimension, yDimension, mode, playerOneScore, playerTwoScore;
}GameStats;

void setxDimension(GameStats *gameStats, int xValue);
void setyDimension(GameStats *gameStats, int yValue);
void setMode(GameStats *gameStats, int modeValue);
void updatePlayerOneScore(GameStats *gameStats);
void updatePlayerTwoScore(GameStats *gameStats);

#endif //CONNECT_FOUR_GAMESTATS_H
