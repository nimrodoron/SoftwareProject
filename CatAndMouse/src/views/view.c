#include "../views/view.h"



View* create_view(Model* model, Screen* screen){
	View* view = (View*)malloc(sizeof(View));

	if (view == NULL)
	{
		isError - 1;
		perror("ERROR: failed to allocate memory for view\n");
		return NULL;
	}
	view->model = model;
	view->screen = screen;
	return view;
}

View* build_all_view(char** imagesArr, char** imagesArrChosen, int* stateArr, int marked_button, int level, int number_buttons){
	View* view;
	Model* model = create_model(imagesArr, imagesArrChosen, stateArr,marked_button,level);
	Screen* screen = build_main_menu(number_buttons, "Cat&Mouse", imagesArr, imagesArrChosen, stateArr,marked_button);
	 view = create_view(model, screen);
	return view;
}

/**/
int draw_screen(char* title, Screen* window)
{

	// Create window surface
	SDL_WM_SetCaption(title, title);

	SDL_BlitSurface(window->screen, NULL, window->screen, NULL);

	SDL_Color color = window->head->componentProps.background_color;
	//SDL_FillRect(window->screen, 0, SDL_MapRGB(window->screen->format, color.r, color.g, color.b));
	if (SDL_FillRect(window->screen, 0, SDL_MapRGB(window->screen->format, color.r, color.g, color.b)) != 0) {
		isError - 1;
		perror("ERROR: failed to draw rect: %s\n", SDL_GetError());
		return NULL;
	}
	draw_components(window->head->next, window);
}


/*draws all the component in the tree */
void draw_components(Panel* comp, Screen* window){
	SDL_Rect frame[1];
	frame[0].x = 0;
	frame[0].y = 0;
	frame[0].w = 350;
	frame[0].h = 58;
	int i = 0;
	while (comp != NULL){
		if (comp->type == BUTTON || comp->type == IMAGE){
			apply_surface(comp->componentProps.surface, button_offsetX, button_offsetY + i*MENUGAP, &frame[0], window);
		}
		comp = comp->next;
		i++;
	}
	if (SDL_Flip(window->screen) != 0) {
		perror("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}


void apply_surface(SDL_Surface* comp, int x, int y, SDL_Rect* clip, Screen* window)
{
	//Holds offsets
	SDL_Rect offset;

	//Get offsets
	offset.x = x;
	offset.y = y;

	//Blit
	if (SDL_BlitSurface(comp, clip, window->screen, &offset) != 0) {
		isError - 1;
		printf("ERROR: failed to blit image: %s\n", SDL_GetError());
	}
}

