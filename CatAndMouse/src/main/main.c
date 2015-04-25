#include "main.h"


int main()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);

	initialize_states();
	
	currentView = states[0];
	draw_screen("Cat&Mouse", currentView->screen);
	//While the user hasn't quit
	while_handle_event();
	
	//SDL_FreeSurface(window);
	SDL_Quit();
}



