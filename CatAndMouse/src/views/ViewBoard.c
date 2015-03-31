#include "ViewBoard.h"


char* displayed_top_panel_images[NUMBER_BUTTONS_TOP_PANEL] = { "Mouse's _move.png", "2.png", NULL, ").png", "Machine_computing.png", "Pause Before Next Move.png" };

char* side_bar_images[NUMBER_BUTTONS_SIDE_BAR] = { "Reconfigue_mouse.png", "Reconfigue_cat.png", "Restart_game.png", "go_to_main_menu.png", "Quit_program.png" };


result createViewBoard(viewBoard* view, void (*HandleSystemEvent) (viewBoardEvents event, int x, int y),
					   modelBoard* model) {
	result res;
	res.code = SUCCESS;
	return res;
}

result showViewBoard(viewBoard* view) {
	result res;
	res.code = SUCCESS;
	return res;
}

result freeViewBoard(viewBoard* view) {

}

viewBoard* create_boardView(Screen* topPanel, Screen* sideBar)
{
	viewBoard* board = (viewBoard*)malloc(sizeof(viewBoard));
	if (board == NULL)
	{
		isError - 1;
		printf("ERROR: failed to allocate memory for board\n");
		return NULL;
	}
	board->topPanel = topPanel;
	board->sideBar = sideBar;
	return board;
}

viewBoard* buildBord()
{
	viewBoard* board;
	Screen* topPanel = create_topPanel();
	Screen* sideBar = create_sideBar();

	board =  create_boardView(topPanel, sideBar);

	return board;
}

Screen* create_topPanel()
{
	int screen_width = 800;
	int screen_height = 200;

	Screen* scr = (Screen*)malloc(sizeof(Screen));
	if (scr == NULL)
	{
		isError - 1;
		printf("ERROR: failed to allocate memory for screen\n");
		return NULL;
	}
	scr->screen = allBoards;
	scr->head = create_panel(800, 200, 0, 0, NULL, PANEL, -1, scr, 1);
	int yOffset = 0;
	int xOffset = 0;
	int type = 1;
	Panel* currentHead = scr->head;
	for (int i = 0; i < NUMBER_BUTTONS_TOP_PANEL; i++)
	{
		if (displayed_top_panel_images[i] == NULL)
			i++;
		switch (i)
		{
		case 1:
			xOffset = 140;
				break;
		case 2:
			xOffset += 7;
			break;
		case 3:
			xOffset +=10;
			break;
		case 4:
			yOffset = 30;
			xOffset = 0;
			break;
		case 5:
			xOffset = 0;
			yOffset += 30;
			type--;
			break;
		default:
			break;
		}
		
		add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + yOffset, displayed_top_panel_images[i],type, 0, scr, 0), scr);	
		apply_surfaceBoard(330 + xOffset, yOffset, currentHead->next->componentProps.surface, allBoards);
		currentHead = currentHead->next;
	}
	
	SDL_Flip(allBoards);
	return scr;
}

Screen* create_sideBar()
{
	int screen_width = 800;
	int screen_height = 200;

	Screen* scr = (Screen*)malloc(sizeof(Screen));
	if (scr == NULL)
	{
		isError - 1;
		printf("ERROR: failed to allocate memory for screen\n");
		return NULL;
	}
	scr->screen = allBoards;
	
	scr->head = create_panel(200, 600, 0, 0, "side_bar_grey.png", IMAGE, -1, scr, 1);
	apply_surfaceBoard(0, 100 , scr->head->componentProps.surface, allBoards);

	Panel* currentHead = scr->head;

	for (int i = 0; i < NUMBER_BUTTONS_SIDE_BAR; i++)
	{
		add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + i*MENUGAP+30, side_bar_images[i], BUTTON, 0, scr, 0), scr);

		apply_surfaceBoard(15, 120 + i*MENUGAP+30, currentHead->next->componentProps.surface, allBoards);
		currentHead = currentHead->next;
	}

	SDL_Flip(allBoards);
	return scr;
}

void apply_surfaceBoard(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
	//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;

	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;

	
	//Blit the surface
	SDL_BlitSurface(source, NULL, destination, &offset);
}

void mainviewboard()
{
	allBoards = SDL_SetVideoMode(800, 800, 0, 0);
	/*SDL_Color color = { 255, 255, 255 };
	SDL_FillRect(allBoards, 0, SDL_MapRGB(allBoards->format, color.r, color.g, color.b));
*/
	viewBoard* board = buildBord();
	
	SDL_Delay(3000);
}

