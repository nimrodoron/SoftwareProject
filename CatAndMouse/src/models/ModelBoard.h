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
	CAT,
	MOUSE,
	CHEESE
}type;

typedef enum player {
	COMPUTER,
	USER
}player;

typedef enum events {
	MOUSE_MOVE,
	CHEESE_MOVE
}eventsType;

typedef struct modelBoard {
	type board[7][7];
	player currentPlayer;
	player cat;
	player mouse;
	int Level;
	player Winner;
	int movesBeforeTie;
}modelBoard;

result createEmptyModel(modelBoard* model);
result createModelFromData(modelBoard* model, type board[7][7]);
result updateModel(modelBoard* model, int rawPos, int colPos, type data, mode modelMode,
		int movesBeforeTie);
result freeModel(modelBoard* model);
#endif




