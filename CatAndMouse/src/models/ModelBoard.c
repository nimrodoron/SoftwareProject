#include "ModelBoard.h"

result createEmptyModel(modelBoard** model) {
	result res;
		*model = (modelBoard*)malloc(sizeof(modelBoard));
		if (model == NULL)
		{
			res.code = -1;
			res.message = "ERROR: failed to allocate memory for model\n";
			return res;
		}
	(*model)->Level = 0;
	//(*model)->cat = NULL;
	//(*model)->mouse = NULL;
	//(*model)->currentPlayer = NULL;
	//(*model)->board; - todo with malloc
	(*model)->movesBeforeTie = -1;
	//(*model)->Winner = NULL;

	res.code = SUCCESS;
	return res;
}
result createModelFromData(modelBoard* model, type board[7][7]) {
	result res;

	res.code = SUCCESS;
	return res;
}
result updateModel(modelBoard* model, int rawPos, int colPos, type data, mode modelMode,
		int movesBeforeTie) {
	result res;

	res.code = SUCCESS;
	return res;
}
result freeModel(modelBoard* model) {
	result res;

	res.code = SUCCESS;
	return res;
}
