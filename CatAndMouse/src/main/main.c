#include "main.h"


int main()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		int isError = - 1;
		// int quit = 0;
		printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);


	//mainviewboard();
	//exit(1);

	

	currentStateIndex = 0;
	initialize_states();
	
	currentView = states[currentStateIndex];
	draw_screen("Cat&Mouse", currentView->screen);
	//While the user hasn't quit
	while_handle_event();
	

	//SDL_FreeSurface(window);
	SDL_Quit();
}



