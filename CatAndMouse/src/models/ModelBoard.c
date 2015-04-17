#include "ModelBoard.h"
#include <stdlib.h>

result createEmptyModel(modelBoard** model) {
	result res;

		*model = (modelBoard*)malloc(sizeof(modelBoard));
		if (model == NULL)
		{
			res.code = ERROR;
			res.message = "images/failed_to_allocate_memory.bmp";
			printMessages(res.message);
			return res;
		}
		(*model)->board = (type**)malloc(GRID_SIZE*sizeof(type*));
		if ((*model)->board != NULL) {

			for (int i=0; i<GRID_SIZE; i++) {
				(*model)->board[i]= (type*)malloc(GRID_SIZE*sizeof(type));

				/* Check if inner malloc failed and free memory*/
				if ((*model)->board[i] == NULL) {
					for (int j=0; j<i; j++)
					{
						free((*model)->board[j]);
					}
					free((*model)->board);
					free(model);

					res.code = ERROR;
					res.message = "images/failed_to_allocate_memory.bmp";
					printMessages(res.message);
					return res;
				}
			}
		}
		else if ((*model)->board == NULL){
			res.code = ERROR;
			res.message = "images/failed_to_allocate_memory.bmp";
			printMessages(res.message);
			return res;
		}

	(*model)->isValid = true;
	res.code = SUCCESS;
	return res;
}

result copyModel(modelBoard** toModel,modelBoard* fromModel) {

	result res;

	createEmptyModel(toModel);
	(*toModel)->cheesePos = fromModel->cheesePos;
	(*toModel)->currentPlayer = fromModel->currentPlayer;
	(*toModel)->isValid = fromModel->isValid;
	(*toModel)->modelMode = fromModel->modelMode;
	(*toModel)->movesBeforeTie = fromModel->movesBeforeTie;
	(*toModel)->name = fromModel->name;
	(*toModel)->players[0] = fromModel->players[0];
	(*toModel)->players[1] = fromModel->players[1];
	for (int row=0;row<GRID_SIZE;row++) {
		for (int col=0;col<GRID_SIZE;col++) {
			(*toModel)->board[row][col] = fromModel->board[row][col];
		}
	}
}

bool movePlayerTo(modelBoard* model, int x, int y) {
	if ( (x > GRID_SIZE-1) || (x<0) || (y > GRID_SIZE-1) || (y<0))
		return false;
	if (model->board[x][y] != EMPTY)
		return false;

	int cX = model->players[model->currentPlayer].playerPos.x;
	int cY = model->players[model->currentPlayer].playerPos.y;

	if (cX!=x && cY!=y)
		return false;

	if (abs(cX-x+cY-y) >= 2)
		return false;

	if (model->currentPlayer == MOUSE)
		model->board[x][y] = MOUSE_PIC;
	else
		model->board[x][y] = CAT_PIC;
	model->board[cX][cY] = EMPTY;
	model->players[model->currentPlayer].playerPos.x = x;
	model->players[model->currentPlayer].playerPos.y = y;
	return true;
}

result freeModel(modelBoard** model) {
	result res;

	for (int i=0; i<GRID_SIZE; i++) {
			free((*model)->board[i]);
		}

	free((*model)->board);
	free(*model);

	res.code = SUCCESS;
	return res;
}


