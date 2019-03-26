/*
 * Functions to update values within the GameStats struct.
 */

#include "gamestats.h"

/*
 * The setxDimension() function allows the x dimension value to be updated within the GameStats struct.
 * The function is passed a pointer to the struct to update as well as the desired x value.
 */
void setxDimension(GameStats *gameStats, int xValue){
    gameStats->xDimension = xValue;
}

/*
 * The setyDimension() function allows the y dimension value to be updated within the GameStats struct.
 * The function is passed a pointer to the struct to update as well as the desired y value.
 */
void setyDimension(GameStats *gameStats, int yValue) {
    gameStats->yDimension = yValue;
}

/*
 * The setMode() function allows the mode value to be updated within the GameStats struct.
 * The function is passed a pointer to the struct to update as well as the desired game mode.
 */
void setMode(GameStats *gameStats, int modeValue) {
    gameStats->mode = modeValue;
}

/*
 * The updatePlayerOneScore() function adds one to the player one score within the GameStats struct.
 * The function is passed a pointer to the struct to update.
 */
void updatePlayerOneScore(GameStats *gameStats) {
    gameStats->playerOneScore = gameStats->playerOneScore + 1;
}

/*
 * The updatePlayerTwoScore() function adds one to the player two score within the GameStats struct.
 * The function is passed a pointer to the struct to update.
 */
void updatePlayerTwoScore(GameStats *gameStats) {
    gameStats->playerTwoScore = gameStats->playerTwoScore + 1;
}