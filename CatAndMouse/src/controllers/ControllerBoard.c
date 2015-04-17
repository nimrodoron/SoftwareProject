#include "ControllerBoard.h"
#include "../services/WorldsManager.h"
#include "../minimax/CatAndMouseMiniMax.h"

result createBoardController(mode Mode, char* name, player mouse,
							 player cat, playerAnimal currentPlayer, int worldsIndex) {
	result res;

	// Create singelton controller
	if (controller == NULL)
	{
		controller = (controllerBoard*)malloc(sizeof(controllerBoard));
		if (controller == NULL) {
			res.code = ERROR;
			res.message = "images/failed_to_allocate_memory.bmp";
			printMessages(res.message);
			return res;
		}
	}

	res = createEmptyModel(&(controller->model));
	if (!res.code) {
		freeBoardController();
		return res;
	}

	// Create the model

	if (Mode == EDIT) {
		if (name == NULL)
			createNewModel();
		else
			res = LoadWorldFromFile(controller->model, name);
	}
	else {
		controller->model->players[CAT] = cat;
		controller->model->players[MOUSE] = mouse;
		res = LoadWorldFromFile(controller->model, name);
		if (!res.code) {
			freeBoardController();
			return res;
		}
	}
	controller->model->modelMode = Mode;
	controller->model->name = name;

	// create the view
	res = createViewBoard(&(controller->view), HandleSystemEvent, controller->model,worldsIndex);
	if (!res.code)
	 {
		freeBoardController();
		return res;
	}

	res.code = SUCCESS;
	return res;
}

result showView() {
	result res = showViewBoard(controller->view,controller->model);
	return res;
}

result freeBoardController() {
	result res;
	if (controller != NULL) {
		if (controller->model != NULL) {
			freeModel(&controller->model);
			free(controller->model);
		}
		if (controller->view != NULL) {
			freeViewBoard(controller->view);
			free(controller->view);
		}
		free(controller);
	}
	res.code = SUCCESS;
	return res;
}

void HandleSystemEvent (viewBoardEvents event, int x, int y) {
	switch (event) {
		case(EXIT):
			break;
		case (RECONFIGURE_MOUSE) :
			reconfigureMouseFunction(controller->model->players[MOUSE].level, controller->model->players[MOUSE].type,controller->model);
			showViewBoard(controller->view,controller->model);
			break;
		case (RECONFIGURE_CAT) :
			reconfigureCatFunction(controller->model->players[CAT].level, controller->model->players[CAT].type, controller->model);
			showViewBoard(controller->view, controller->model);
			break;
		case (RESTART_GAME) :
			//nimrod fill - page 10 PDF
			break;
		case (GO_TO_MAIN_MENU):
			GoToMainMenu();
			break;
		case(SPACE):
			//fill - ?
			break;
		case (PLACE_MOUSE):
			placeMouse(x,y);
			break;
		case (PLACE_CAT):
			placeCat(x,y);
			break;
		case(PLACE_CHEESE):
			placeCheese(x,y);
			break;
		 case(PLACE_WALL):
			placeWall(x,y);
		 	break;
		  case(PLACE_EMPTY_SPACE):
			placeEmpty(x,y);
		  	break;
		  case(SAVE_WORLD) :
			  //TEMP
			  if (checkIfCanSaveModel(controller->model).code)
			  {
				  save_world(controller->model);
				  showViewBoard(controller->view, controller->model);
			  }
			  else 
			  {
				  //printMessages(checkIfCanSaveModel(controller->model).message);
				  printMessages("images/failed_to_create_game.bmp");
				  showViewBoard(controller->view, controller->model);
			  }
					
		  	  	  break;
		  case (PLAYER_MOVED_TO) :
			  playerMoveTo(x,y);
			  break;
	
		default:
			break;
	}
}



void createNewModel() {
	for (int i=0; i<GRID_SIZE; i++) {
		for (int j=0; j<GRID_SIZE; j++) {
			controller->model->board[i][j] = EMPTY;
		}
	}
	controller->model->cheesePos.x = UNVALID_POS;
	controller->model->cheesePos.y = UNVALID_POS;
	controller->model->players[MOUSE].playerPos.x = UNVALID_POS;
	controller->model->players[MOUSE].playerPos.y = UNVALID_POS;
	controller->model->players[CAT].playerPos.x = UNVALID_POS;
	controller->model->players[CAT].playerPos.y = UNVALID_POS;
	controller->model->currentPlayer = -1;
	controller->model->movesBeforeTie = 20;
}

player createPlayer(playerType type, int level)
{
	player ply;
	ply.type = type;
	ply.level = level;
	return ply;
}

void updateModelBoard(playerType cat, int catLevel, playerType mouse, int mouseLevel)
{
	updateModelBoardMouse(mouse, mouseLevel);
	updateModelBoardCat(cat, catLevel);
}

void updateModelBoardMouse(playerType mouse, int mouseLevel)
{
	controller->model->players[MOUSE].type = mouse;
	controller->model->players[MOUSE].level = mouseLevel;
}

void updateModelBoardCat(playerType cat, int catLevel)
{
	controller->model->players[CAT].type = cat;
	controller->model->players[CAT].level = catLevel;
}

void restartGame() {
	LoadWorldFromFile(controller->model, controller->model->name);
}

void placeMouse(int x, int y) {

	checkCurrentPos(x,y);

	if (x != UNVALID_POS && y != UNVALID_POS) {
		controller->model->board[x][y] = MOUSE_PIC;

		if (controller->model->players[MOUSE].playerPos.x != x ||
				controller->model->players[MOUSE].playerPos.y != y) {

			if (controller->model->players[MOUSE].playerPos.x != UNVALID_POS &&
					controller->model->players[MOUSE].playerPos.y != UNVALID_POS)
				controller->model->board[controller->model->players[MOUSE].playerPos.x][controller->model->players[MOUSE].playerPos.y] = EMPTY;

			controller->model->players[MOUSE].playerPos.x = x;
			controller->model->players[MOUSE].playerPos.y = y;
		}
	}

	controller->model->currentPlayer = MOUSE;
	controller->view->model = controller->model;
	refreshViewBoard(controller->view,controller->model);
}

void placeCat(int x, int y) {

	checkCurrentPos(x,y);

	if (x != UNVALID_POS && y != UNVALID_POS) {
		controller->model->board[x][y] = CAT_PIC;

		if (controller->model->players[CAT].playerPos.x != x ||
				controller->model->players[CAT].playerPos.y != y) {

			if (controller->model->players[CAT].playerPos.x != UNVALID_POS &&
					controller->model->players[CAT].playerPos.y != UNVALID_POS)
				controller->model->board[controller->model->players[CAT].playerPos.x][controller->model->players[CAT].playerPos.y] = EMPTY;

			controller->model->players[CAT].playerPos.x = x;
			controller->model->players[CAT].playerPos.y = y;
		}
	}

	controller->model->currentPlayer = CAT;
	controller->view->model = controller->model;
	refreshViewBoard(controller->view,controller->model);
}

void checkCurrentPos(int x,int y) {
	if (controller->model->board[x][y] == MOUSE_PIC) {
		controller->model->players[MOUSE].playerPos.x = UNVALID_POS;
		controller->model->players[MOUSE].playerPos.y = UNVALID_POS;
		if (controller->model->currentPlayer == MOUSE)
			controller->model->currentPlayer = -1;
	}
	if (controller->model->board[x][y] == CAT_PIC) {
		controller->model->players[CAT].playerPos.x = UNVALID_POS;
		controller->model->players[CAT].playerPos.y = UNVALID_POS;
		if (controller->model->currentPlayer == CAT)
			controller->model->currentPlayer = -1;
	}
	if (controller->model->board[x][y] == CHEESE) {
		controller->model->cheesePos.x = UNVALID_POS;
		controller->model->cheesePos.y = UNVALID_POS;
	}
}

void placeCheese(int x, int y) {
	checkCurrentPos(x,y);

	if (x != UNVALID_POS && y != UNVALID_POS) {
		controller->model->board[x][y] = CHEESE;

		if (controller->model->cheesePos.x != x ||
				controller->model->cheesePos.y != y) {

			if (controller->model->cheesePos.x != UNVALID_POS &&
					controller->model->cheesePos.y != UNVALID_POS)
				controller->model->board[controller->model->cheesePos.x][controller->model->cheesePos.y] = EMPTY;

			controller->model->cheesePos.x = x;
			controller->model->cheesePos.y = y;
		}
	}

	controller->view->model = controller->model;
	refreshViewBoard(controller->view,controller->model);
}
void placeWall(int x, int y) {
	checkCurrentPos(x,y);

	controller->model->board[x][y] = WALL;

	controller->view->model = controller->model;
	refreshViewBoard(controller->view, controller->model);
}
void placeEmpty(int x, int y) {
	checkCurrentPos(x,y);

	controller->model->board[x][y] = EMPTY;

	controller->view->model = controller->model;
	refreshViewBoard(controller->view, controller->model);
}

result checkIfCanSaveModel(modelBoard* model) {
	result res;
	res.code = ERROR;

	if (model->currentPlayer == -1) {
		res.message = "images/no_current_player.bmp";
		return res;
	}
	else if (model->cheesePos.x == UNVALID_POS || model->cheesePos.y == UNVALID_POS) {
		res.message = "images/cheese_is_missing.bmp";
	}
	else if (model->players[MOUSE].playerPos.x == UNVALID_POS || model->players[MOUSE].playerPos.y == UNVALID_POS) {
		res.message = "images/mosue_is_missing.bmp";
	}

	else if (model->players[CAT].playerPos.x == UNVALID_POS || model->players[CAT].playerPos.y == UNVALID_POS) {
		res.message = "images/cat_is_missing.bmp";
	}

	else {
		res.code = SUCCESS;
	}
	return res;
}

void playerMoveTo(int x, int y) {
	MOVE pmove;

	// move the player if possiable
	if(movePlayerTo(controller->model,x,y)) {



		 // check for winner
		 //controller->model->winner = checkForWinner(controller->model);

		 // switch player
		 controller->model->currentPlayer = !controller->model->currentPlayer;

		 // make computer turn
		 if (controller->model->players[controller->model->currentPlayer].type == COMPUTER) {
			 controller->model->movesBeforeTie--;
			 // pmove = getBestMove(controller->model,controller->model->players[controller->model->currentPlayer].level);
		 }

		controller->view->model = controller->model;
		refreshViewBoard(controller->view, controller->model);
	}
}

