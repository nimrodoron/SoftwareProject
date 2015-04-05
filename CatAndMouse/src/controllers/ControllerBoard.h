#ifndef CONTROLLERBOARD_H_
#define CONTROLLERBOARD_H_

#include <stdlib.h>
//#include "../infrastructure/general/general.h"
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
		 	 	 	 	 	 player player2, playerAnimal currentPlayer);

// Show the view of the controller
result showView();

// Destroy the singelton controller
result freeBoardController();

// function used to handle view events update the model and view accordingly
void HandleSystemEvent (viewBoardEvents event, int x, int y);

void createNewModel();
player createPlayer(playerType type, int level);
void updateModelBoard(playerType cat, int catLevel, playerType mouse, int mouseLevel);
void updateModelBoardMouse(playerType mouse, int mouseLevel);
void updateModelBoardCat(playerType cat, int catLevel);


#endif

