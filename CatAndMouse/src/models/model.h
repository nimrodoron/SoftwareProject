#include "../infrastructure/gui/widgets.h"


typedef struct model{
	char** images; // an array for the images for the buttons in this screen
	char** chosen_images; //an array for the chosen images for the buttons in this screen
	int* stateId; //the next state for each button in the screen
	int marked_button;
	int level;
}Model;




Model* create_model(char** imagesArr, char** imagesArrChosen, int* stateArr, int marked_button, int level);
