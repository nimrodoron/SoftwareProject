#ifndef CONTROLLERBOARD_H_
#define CONTROLLERBOARD_H_

#include <stdlib.h>
//#include "../infrastructure/general/general.h"
#include "../models/ModelBoard.h"
#include "../views/ViewBoard.h"

typedef struct controllerBoard {
	modelBoard* model;
	viewBoard* view;
}controllerBoard;

controllerBoard* controller;

// Create new controller if not exist
result createBoardController(mode Mode, char* name, player cat,
		 	 	 	 	 	 player mouse, int Level);

// Show the view of the controller
result showView();

// Destroy the singelton controller
result freeBoardController();

// function used to handle view events update the model and view accordingly
void HandleSystemEvent (viewBoardEvents event, int x, int y);

#endif

