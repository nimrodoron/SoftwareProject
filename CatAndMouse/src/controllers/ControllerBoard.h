#ifndef CONTROLLERBOARD_H_
#define CONTROLLERBOARD_H_

#include <stdlib.h>
#include "../infrastructure/general/general.h"
#include "../models/ModelBoard.h"
#include "../views/ViewBoard.h"
#include "../controllers/controller.h"

typedef struct controllerBoard {
	modelBoard* model;
	viewBoard* view;
}controllerBoard;

controllerBoard* controller;

// Create new controller if not exist
result createBoardController(mode Mode, char* name, player player1,
		 	 	 	 	 	 player player2, playerAnimal currentPlayer,int worldsIndex);

// Show the view of the controller
result showView();

// Destroy the singelton controller
result freeBoardController();

// function used to handle view events update the model and view accordingly
void HandleSystemEvent (viewBoardEvents event, int x, int y);

void createNewModel();
player createPlayer(playerType type, int level);
void checkCurrentPos(int x,int y);
result checkIfCanSaveModel(modelBoard* model);

// Events
void placeMouse(int x, int y);
void placeCat(int x, int y);
void placeCheese(int x, int y);
void placeWall(int x, int y);
void placeEmpty(int x, int y);
void playerMoveTo(int x, int y);
void updateModelBoard(playerType cat, int catLevel, playerType mouse, int mouseLevel);
void updateModelBoardMouse(playerType mouse, int mouseLevel);
void updateModelBoardCat(playerType cat, int catLevel);

#endif

