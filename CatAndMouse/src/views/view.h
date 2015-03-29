#include "../models/model.h"



typedef struct view{
	Model* model;
	Screen* screen;
}View;



View* create_view(Model* model, Screen* screen);
View* build_all_view(char** imagesArr, char** imagesArrChosen, int* stateArr, int marked_button, int level, int number_buttons);
int draw_screen(char* title, Screen* window);
void draw_components(Panel* comp, Screen* window);
void apply_surface(SDL_Surface* comp, int x, int y, SDL_Rect* clip, Screen* window);
