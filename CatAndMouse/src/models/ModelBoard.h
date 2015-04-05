#ifndef GAMEBOARDMODEL_H_
#define GAMEBOARDMODEL_H_

#include "../infrastructure/general/general.h"

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

typedef enum player {
	COMPUTER,
	USER
}player;

typedef enum currentAnimalPlayer {
	CAT,
	MOUSE
}currentAnimalPlayer;

typedef enum events {
	MOUSE_MOVE,
	CHEESE_MOVE
}eventsType;

typedef struct modelBoard {
	type board[7][7];
	currentAnimalPlayer currentPlayer;
	player cat;
	player mouse;
	int Level;
	player Winner;
	int movesBeforeTie;
}modelBoard;

result createEmptyModel(modelBoard** model);
result freeModel(modelBoard** model);
#endif




