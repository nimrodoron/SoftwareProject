#ifndef CATANDMOUSEMINIMAX_H_
#define CATANDMOUSEMINIMAX_H_

#include "../main/MiniMax.h"
#include "../models/ModelBoard.h"
#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_PLAYER 1
#define MIN_PLAYER 0
#define CHECK(X,Y) if ((X>=0) && (X<GRID_SIZE) && (Y>=0) && (Y<GRID_SIZE)) if (board[in][jn] == EMPTY) graph[i*GRID_SIZE+j][in*GRID_SIZE+jn] = 1;

typedef enum MOVE {
	UP,
	DOWN,
	LEFT,
	RIGHT
}MOVE;

typedef enum nodeVisit {
	NOT_VISIT,
	IN_QUEUE,
	COMPLETED
}Visit;

int getBestMove(modelBoard* currentState,int numSteps);

playerAnimal checkForWinner(modelBoard* currentState);

int evaluate(void* state);

ListRef getChildren(void* state);

modelBoard buildBoard();

void FreeState(void* state);

void bfs(int v, int** a,int visited[], int q[], int n, int f,int r,int dis[]);

int findShortPath(int** matrix, int s_row, int s_col,  int d_row, int d_col);

int** GenerateGraphFromMatrix(modelBoard* board, type toType);

bool ChceckNeighbours(type** board, int i,int j, type type);

void destryGraph(int** graph);

#endif /* CONNECT4MINIMAX_H_ */
