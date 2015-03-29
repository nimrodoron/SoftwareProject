#include "../models/model.h"

Model* create_model(char** imagesArr, char** imagesArrChosen, int* stateArr, int marked_button, int level)
{
	Model* mod = (Model*)malloc(sizeof(Model));
	if (mod==NULL)
	{
		isError -1;
		printf("ERROR: failed to allocate memory for model\n");
		return NULL;
	}
	mod->chosen_images = imagesArrChosen;
	mod->images = imagesArr;
	mod->marked_button = marked_button;
	mod->level = level;
	mod->stateId = stateArr;
	return mod;
}
