#include "ViewBoard.h"

//array for the displayed images
char* displayed_top_panel_images[NUMBER_BUTTONS_TOP_PANEL] = { "images/Mouse's _move.bmp", "images/2.bmp", NULL, "images/).bmp", "images/Machine_computing.bmp", "images/Pause Before Next Move.bmp" }; 
//arrays for the images in the top panel
char* top_panel_animal_move[2] = { "images/Cat_move.bmp", "images/Mouse's _move.bmp" };
char* top_panel_numbers[11] = { "images/).bmp", "images/0.bmp", "images/1.bmp", "images/2.bmp", "images/3.bmp", "images/4.bmp", "images/5.bmp", "images/6.bmp", "images/7.bmp", "images/8.bmp", "images/9.bmp" };
char* top_panel_win_status[3] = { "images/Game Over – Cat Wins.bmp", "images/Game Over – Mouse Wins.bmp", "images/Game Over – Timeout.bmp" };
char* top_panel_game_status[4] = { "images/Human-waiting for next move….bmp","images/Human-paused.bmp","images/Machine_computing.bmp","images/Machine-paused.bmp"};

char* side_bar_images[NUMBER_BUTTONS_SIDE_BAR] = { "images/Reconfigue_mouse.bmp", "images/Reconfigue_cat.bmp", "images/Restart_game.bmp", "images/go_to_main_menu.bmp", "images/Quit_program.bmp" };



//change to this after the fixes in cuntrollerBoard
//result createViewBoard(viewBoard* view, void (*HandleSystemEvent) (viewBoardEvents event, int x, int y),
//					   modelBoard* model) {
//	result res;
//	viewBoard* board = (viewBoard*)malloc(sizeof(viewBoard));
//	if (board == NULL)
//	{
//		res.code = -1;
//		res.message = "ERROR: failed to allocate memory for board\n";
//		return res;
//	}
//	board->topPanel = create_topPanel();
//	board->sideBar = create_sideBar();
//	res.code = SUCCESS;
//	return res;
//}

result createViewBoard(viewBoard** view, void(*HandleSystemEvent) (viewBoardEvents event, int x, int y),
	modelBoard* model) {
	
	result res;
	Screen* sideBar;
	Screen* topPanel;
	Screen* gridArea;
	*view = (viewBoard*)malloc(sizeof(viewBoard));
	if (view == NULL)
	{
		res.code= -1;
		res.message = "ERROR: failed to allocate memory for board\n";
		return res;
	}
	sideBar = create_sideBar();
	topPanel = create_topPanel();
	gridArea = create_gridArea();

	if ((sideBar == NULL) || (topPanel == NULL)|| (gridArea==NULL))
	{
		res.code = -1;
		res.message = "ERROR: failed to allocate memory for game window\n";
		return res;
	}
	(*view)->topPanel = topPanel;
	(*view)->sideBar = sideBar;
	(*view)->gridArea = gridArea;

	res.code = SUCCESS;
	return res;
}

result showViewBoard(viewBoard* view) {
	result res;
	
	show_side_bar(view->sideBar);
	show_top_panel(view->topPanel);
	show_grid_area(view->gridArea);
	res.code = SUCCESS;
	return res;
}

result freeViewBoard(viewBoard* view) {

}

Screen* create_topPanel()
{
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
	}
	
	return scr;
}

void show_top_panel(Screen* scr)
{
	int yOffset = 0;
	int xOffset = 0;
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
			xOffset += 10;
			break;
		case 4:
			yOffset = 30;
			xOffset = 0;
			break;
		case 5:
			xOffset = 0;
			yOffset += 30;
			break;
		default:
			break;
		}

		apply_surfaceBoard(330 + xOffset, yOffset, currentHead->next->componentProps.surface, allBoards);
		currentHead = currentHead->next;
	}
	SDL_Flip(allBoards);
}

Screen* create_sideBar()
{
	Screen* scr = (Screen*)malloc(sizeof(Screen));
	if (scr == NULL)
	{
		isError - 1;
		printf("ERROR: failed to allocate memory for screen\n");
		return NULL;
	}
	scr->screen = allBoards;
	
	scr->head = create_panel(200, 600, 0, 0, "side_bar_grey.bmp", IMAGE, -1, scr, 1);
	apply_surfaceBoard(0, 100 , scr->head->componentProps.surface, allBoards);

	for (int i = 0; i < NUMBER_BUTTONS_SIDE_BAR; i++)
	{
		add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + i*MENUGAP+30, side_bar_images[i], BUTTON, 0, scr, 0), scr);
	}

	return scr;
}

void show_side_bar(Screen* scr)
{
	Panel* currentHead = scr->head;

	for (int i = 0; i < NUMBER_BUTTONS_SIDE_BAR; i++)
	{
		apply_surfaceBoard(15, 120 + i*MENUGAP + 30, currentHead->next->componentProps.surface, allBoards);
		currentHead = currentHead->next;
	}

	SDL_Flip(allBoards);
}


Screen* create_gridArea()
{
	Screen* scr = (Screen*)malloc(sizeof(Screen));
	if (scr == NULL)
	{
		isError - 1;
		printf("ERROR: failed to allocate memory for grid\n");
		return NULL;
	}
	scr->screen = allBoards;

	scr->head = create_panel(800, 200, 0, 0, NULL, PANEL, -1, scr, 1);
	//apply_surfaceBoard(0, 100, scr->head->componentProps.surface, allBoards);

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			add_child(create_panel(70, 70, 70 * j, 70 * i, "images/square.bmp", BUTTON, 0, scr, 0), scr);
		}
		
	}

	return scr;
}

void show_grid_area(Screen* scr)
{
	Panel* currentHead = scr->head;

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			apply_surfaceBoard(230 + j*70, 120 + i * 70, currentHead->next->componentProps.surface, allBoards);
			currentHead = currentHead->next;
		}
		
	}

	SDL_Flip(allBoards);
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

//convert the model to the right images to dispaly in the top panel
void convert_model(viewBoard* view)
{
	char* try = top_panel_animal_move[view->model->currentPlayer];
	displayed_top_panel_images[0] = try;

}

void mainviewboard()
{
	
	allBoards = SDL_SetVideoMode(800, 800, 0, 0);
	SDL_Color color = { 255, 255, 255 };
	SDL_FillRect(allBoards, 0, SDL_MapRGB(allBoards->format, color.r, color.g, color.b));
	createBoardController(EDIT, "hila", USER, COMPUTER, 2);
	showView();

	SDL_Delay(3000);
}

