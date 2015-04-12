#ifndef GAMEBOARDMODEL_H_
#define GAMEBOARDMODEL_H_

#include "../infrastructure/general/general.h"
#include <stdbool.h>

#define GRID_SIZE 7
#define PLAYERS_NUM 2
#define UNVALID_POS -1

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
	type** board;
	player players[PLAYERS_NUM];
	playerAnimal currentPlayer;
	playerAnimal winner;
	int movesBeforeTie;
	pos cheesePos;
	char* name;
	bool isValid;
}modelBoard;

result createEmptyModel(modelBoard** model);
result copyModel(modelBoard** toModel,modelBoard* fromModel);
result freeModel(modelBoard** model);
bool movePlayerTo(modelBoard* model, int x, int y);

#endif




