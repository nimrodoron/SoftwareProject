#include "ControllerBoard.h"
#include "../services/WorldsManager.h"

result createBoardController(mode Mode, char* name, player mouse,
							 player cat, playerAnimal currentPlayer) {
	result res;

	// Create singelton controller
	if (controller == NULL)
	{
		controller = (controllerBoard*)malloc(sizeof(controllerBoard));
		if (controller == NULL) {
			res.code = ERROR;
			res.message = "Failed to malloc controller";
			return res;
		}
	}

	res = createEmptyModel(&(controller->model));
	if (!res.code) {
		freeBoardController();
		return res;
	}

	// Create the model
	controller->model->modelMode = Mode;
	if (Mode == EDIT) {
		if (name == NULL)
			createNewModel();
		else
			res = LoadWorldFromFile(&(controller->model), name);
	}
	else {
		controller->model->players[CAT] = cat;
		controller->model->players[MOUSE] = mouse;
		controller->model->currentPlayer = currentPlayer;
		res = LoadWorldFromFile(&(controller->model), name);
		if (!res.code) {
			freeBoardController();
			return res;
		}
	}

	// create the view
	res = createViewBoard(&(controller->view), HandleSystemEvent, controller->model);
	if (!res.code)
	 {
		freeBoardController();
		return res;
	}

	res.code = SUCCESS;
	return res;
}

result showView() {
	result res = showViewBoard(controller->view);
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
}

player createPlayer(playerType type, int level)
{
	player ply;
	ply.type = type;
	ply.level = level;
	return ply;
}



