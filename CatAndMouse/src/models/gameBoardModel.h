#ifndef GAMEBOARDMODEL_H_
#define GAMEBOARDMODEL_H_

#include "../main/general.h"

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

typedef struct gameModel {
	type board[7][7];
	player currentPlayer;
	player cat;
	player mouse;
	int catLevel;
	player Winner;
}gameModel;

result createEmptyModel(gameModel* model);
result createModelFromData(gameModel* model, type board[7][7],player currentPlayer,
		                      player cat, player mouse, int catLevel);
result updateModel(gameModel* model, int rawPos, int colPos, type data, mode modelMode);

#endif




