#include "main.h"




int main(int argc, char* argv[]) {
	if (argc == 1) { //there isn't a parameter to the program. then initiallize the gui
		initGUI();
	} 
	else if (argc == 3){
		if (!strcmp(argv[1], "-console"))
			if ((!strcmp(argv[2], "mouse")) || (!strcmp(argv[2], "cat")))
				handle_event_console();
	}
	else{ //if the argument are not valid to the program - quit
		perror("the arguments are not valid");
		exit(1);
	}
	return 0;
}





int initGUI()
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

void handle_event_console()
{
	printf("%s\n", "q\n");
	exit(0);
}



