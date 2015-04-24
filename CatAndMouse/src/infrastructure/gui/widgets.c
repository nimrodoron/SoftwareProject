#include "widgets.h"


int BUTTON_WIDTH = 175;
int  BUTTON_HEIGHT = 58;
int MENUGAP = 58 + 30;
int button_offsetX = 300;
int button_offsetY = offsetY + 10;

Screen* create_screen()
{
	Screen* scr = (Screen*)malloc(sizeof(Screen));
	if (scr == NULL)
	{
		isError -1;
		perror("ERROR: failed to allocate memory for screen\n");
		return NULL;
	}
	scr->head = NULL;
	scr->screen = NULL;

	return scr;
}


/*create and initalize a new component*/
Panel* create_panel(int width, int height, int x, int y, char* path, ComponentType type, int stateIndex,Screen* window,int number_buttons)
{
	SDL_Color color = { 255, 255, 255 };
	SDL_Rect * dest_rect;

	dest_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	if (dest_rect == NULL)
	{
		isError -1;
		perror("ERROR: failed to allocate struct while creating destination rectangle\n");
		return NULL;
	}
	dest_rect->w = width;
	dest_rect->h = height;
	dest_rect->x = x;
	dest_rect->y = y;
	Panel* pan = (Panel*)malloc(sizeof(Panel));
	if (pan == NULL)
	{
		isError -1;
		perror("ERROR: failed to allocate memory for component\n");
		free(dest_rect);
		return NULL;
	}
	pan->type = type;
	pan->next = NULL;
	pan->prev = NULL;
	pan->componentProps.dest_rect = dest_rect;

	if (window->screen != NULL)
	{ /*to make sure it exists*/
		pan->componentProps.background_color = color;
	}
	if (type == BUTTON)
	{
		pan->componentProps.surface = SDL_LoadBMP(path);
		if (pan->componentProps.surface == NULL) {
			printf("ERROR: failed to load image: %s\n", SDL_GetError());
			return NULL;
		}
		pan->enabled = true;
	}
	else if (type == IMAGE)
	{
		pan->componentProps.surface = SDL_LoadBMP(path);
		if (pan->componentProps.surface == NULL) {
			printf("ERROR: failed to load image: %s\n", SDL_GetError());
			return NULL;
		}
		pan->enabled = false;
	}
	else if (type == PANEL)
	{
		pan->componentProps.surface = window->screen;
		pan->enabled = false;
		pan->size = number_buttons;
	}
	else
	{
		pan->componentProps.surface = window->screen;
		pan->enabled = false;
		pan->size = 0;
	}
	if (stateIndex != -1)
		pan->nextState = stateIndex;
	else
	{
		pan->nextState = -1;
	}

	return pan;
}

void update_panel_picture(Panel* item, char* path) {
	item->componentProps.surface = SDL_LoadBMP(path);
	if (item->componentProps.surface == NULL) {
		printf("ERROR: failed to load image: %s\n", SDL_GetError());
	}
}

/*to build the main menu*/
Screen* build_main_menu(int number_buttons, char* title, char** imagesArr, char** imagesArrChosen, int* stateArr,int marked_button)
{
	int screen_width=800;
	int screen_height=800;
	//screen_width = calc_width(BUTTON_WIDTH);
	//screen_height = calc_height(number_buttons, BUTTON_HEIGHT, MENUGAP);

	Screen* window = create_screen();
	
	window->screen = SDL_SetVideoMode(screen_width, screen_height, 0, 0);
	if (window == NULL) {
		isError -1;
		printf("ERROR: failed to set video mode: %s\n", SDL_GetError());
		return NULL;
	}
	window->head = create_panel(screen_width, screen_height, 0, 0, NULL, PANEL, -1 ,window, number_buttons);

	for (int i = 0; i < number_buttons; i++)
	{
		if (i == marked_button)
		{
			add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + i*MENUGAP, imagesArrChosen[i], BUTTON, stateArr[i],window,0),window);
		}
		else if (i == 0)
		{
			add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + i*MENUGAP, imagesArr[i], IMAGE, stateArr[i], window,0),window);
		}
		else
		{
			add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + i*MENUGAP, imagesArr[i], BUTTON, stateArr[i], window,0),window);
		}
	}
	return window;
}




/*calculates the height of the window*/
int calc_height(int size, int height, int gap)
{
	return  size*(gap)+50;
}

/*calculates the width of the window*/
int calc_width(int width)
{
	return  width * 2;
}

/*adds child to linked list*/
void add_child(Panel* item, Screen* window)
{
	Panel* current = window->head;
	if (!current || !item)
	{
		return;
	}
	else
	{
		//if this is the first item in the list
		if (current->next == NULL)
		{
			current->next = item;
		}
		else
		{
			while (current->next != NULL)
			{
				current = current->next;
			}
			current->next = item;
		}
	}
}

widget* createNewWidget(ComponentType widgetType, char* name) {

	widget* newWidget = (widget*)malloc(sizeof(widget));

	if (newWidget == NULL)
	{
		return NULL;
	}

	newWidget->dest_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));

	if (newWidget->dest_rect == NULL)
	{
		return NULL;
	}

	newWidget->widgetType = widgetType;
	newWidget->name = name;
	return newWidget;
}
void drawWidget(widget* wg, SDL_Surface* surface) {

	//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;

	//Give the offsets to the rectangle
	offset.x = wg->x;
	offset.y = wg->y;
	offset.h = 0;
	offset.w = 0;

	wg->dest_rect->x = 0;
	wg->dest_rect->y = 0;
	wg->dest_rect->h = wg->height;
	wg->dest_rect->w = wg->width;

	//Blit the surface
	SDL_BlitSurface(wg->widget_surface, wg->dest_rect, surface, &offset);
}

bool checkClick(widget* wg, int x, int y) {
	if (wg->widgetType == BUTTON)
		if ((x > wg->x) && (x < wg->x + wg->width) && (y > wg->y) && (y < wg->y+wg->height))
			return true;
	return false;
}

void setWidgetImage(widget* wg, char* path)
{
	if (wg->widget_surface != NULL){
		SDL_FreeSurface(wg);
	}
	wg->widget_surface = SDL_LoadBMP(path);
}

void setImage(Panel* panel, char* path)
{
	if (panel->componentProps.surface != NULL)
		SDL_FreeSurface(panel->componentProps.surface);
	panel->componentProps.surface = SDL_LoadBMP(path);
}

void freeWidget(void* wgv) {
	;
	widget* wg = (widget*)wgv;
	if (wg->dest_rect != NULL) {
		free(wg->dest_rect);
	}
	SDL_FreeSurface(wg->widget_surface);
	if (wg != NULL)
		free(wg);
}

void freeScreen(Screen* screen)
{
	Panel* currentHead = screen->head;
	while (screen->head != NULL){
		currentHead = screen->head;
		screen->head = currentHead->next;
		freePanel(currentHead);
	}
	free(screen);
}
void freePanel(Panel* panel)
{
	if (panel->componentProps.dest_rect!=NULL)
		free(panel->componentProps.dest_rect);
	if (panel->componentProps.surface != NULL)
		SDL_FreeSurface(panel->componentProps.surface);
	if (panel!=NULL)
		free(panel);
}