#ifndef CATANDMOUSEMINIMAX_H_
#define CATANDMOUSEMINIMAX_H_

#include "../infrastructure/minimax/MiniMax.h"
#include "../models/ModelBoard.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_PLAYER 1
#define MIN_PLAYER 0

typedef enum MOVE {
	UP,
	DOWN,
	LEFT,
	RIGHT
}MOVE;

int getBestMove(modelBoard* currentState,int numSteps);

playerAnimal checkForWinner(modelBoard* currentState);

int evaluate(void* state);

ListRef getChildren(void* state);

modelBoard buildBoard();

void FreeState(void* state);

#endif /* CONNECT4MINIMAX_H_ */
