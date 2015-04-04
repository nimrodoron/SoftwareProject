#include "ModelBoard.h"
#include <stdlib.h>

result createEmptyModel(modelBoard** model) {
	result res;
		*model = (modelBoard*)malloc(sizeof(modelBoard));
		if (model == NULL)
		{
			res.code = -1;
			res.message = "ERROR: failed to allocate memory for model\n";
			return res;
		}

	res.code = SUCCESS;
	return res;
}
result freeModel(modelBoard** model) {
	result res;

	res.code = SUCCESS;
	return res;
}
