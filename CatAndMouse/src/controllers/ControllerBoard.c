#include "ControllerBoard.h"
#include "../services/WorldsManager.h"

//result createBoardController(mode Mode, char* name, player cat,
//							 player mouse, int Level) {
//	result res;
//
//	// Create singelton controller
//	if (controller != NULL)
//		controller = (controllerBoard*)malloc(sizeof(controllerBoard));
//
//	if (controller == NULL) {
//		res.code = ERROR;
//		res.message = "Failed to malloc controller";
//		return res;
//	}
//
//	// Create the model
//	if (Mode == EDIT) {
//		res = createEmptyModel(controller->model);
//		if (!res.code) {
//			freeBoardController();
//			return res;
//		}
//	}
//	else {
//		res = LoadWorldFromFile(controller->model, name);
//		if (!res.code) {
//			freeBoardController();
//			return res;
//		}
//		controller->model->Level = Level;
//		controller->model->cat = cat;
//		controller->model->mouse = mouse;
//	}
//
//	// Create the view
//	res = createViewBoard(controller->view, HandleSystemEvent, controller->model);
//	if (!res.code) {
//		freeBoardController();
//		return res;
//	}
//
//	res.code = SUCCESS;
//	return res;
//}

result showView() {
	result res = showViewBoard(controller->view);
	return res;
}
result freeBoardController() {
	result res;
	if (controller != NULL) {
		if (controller->model != NULL) {
			freeModel(controller->model);
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
