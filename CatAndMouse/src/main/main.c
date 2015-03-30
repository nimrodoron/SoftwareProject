#include "main.h"


int main()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		int isError = - 1;
		quit = 0;
		printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);

	//window = create_screen();
	//currentState = stateId_main_menu[0];
	

	int currentStateIndex = 0;
	initialize_states();
	
	currentView = states[currentStateIndex];
	draw_screen("Cat&Mouse", currentView->screen);
	//currentWindow = open_window_dialog(currentState);
	//While the user hasn't quit
	while (quit == 0)
	{
		//While there's events to handle
		while (SDL_PollEvent(&event) != 0)
		{
			handle_event(&event, currentView);
		}
	}

	//SDL_FreeSurface(window);
	SDL_Quit();
}


