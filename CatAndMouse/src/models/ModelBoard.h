#ifndef GAMEBOARDMODEL_H_
#define GAMEBOARDMODEL_H_

#include "../infrastructure/general/general.h"

#define GRID_SIZE 7
#define PLAYERS_NUM 2

typedef enum mode {
	EDIT,
	GAME
}mode;

typedef enum fillType {
	EMPTY,
	WALL,
	CAT_PIC,
	MOUSE_PIC,
	CHEESE
}type;

typedef enum playerType {
	COMPUTER,
	USER
}playerType;

typedef enum playerAnimal {
	CAT,
	MOUSE,
	NONE
}playerAnimal;

typedef struct position {
	int x;
	int y;
}pos;

typedef struct player {
	playerType type;
	pos playerPos;
	int level;
}player;

typedef struct modelBoard {
	mode modelMode;
	type board[GRID_SIZE][GRID_SIZE];
	player players[PLAYERS_NUM];
	playerAnimal currentPlayer;
	player winner;
	int movesBeforeTie;
	pos cheesePos;
}modelBoard;

result createEmptyModel(modelBoard** model);
result freeModel(modelBoard** model);
#endif




