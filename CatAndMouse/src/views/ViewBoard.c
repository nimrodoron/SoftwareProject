#include "ViewBoard.h"

//array for the displayed images
char* displayed_top_panel_images[NUMBER_BUTTONS_TOP_PANEL] = { "images/Mouse's _move.bmp", "images/2.bmp", "", "images/).bmp", "images/Machine_computing.bmp", "images/Pause Before Next Move.bmp" };
//arrays for the images in the top panel
char* top_panel_animal_move[2] = { "images/Cat_move.bmp", "images/Mouse's _move.bmp" };
char* top_panel_numbers[11] = { "images/).bmp", "images/0.bmp", "images/1.bmp", "images/2.bmp", "images/3.bmp", "images/4.bmp", "images/5.bmp", "images/6.bmp", "images/7.bmp", "images/8.bmp", "images/9.bmp" };
char* top_panel_win_status[3] = { "images/Game Over , Cat Wins.bmp", "images/Game Over , Mouse Wins.bmp", "images/Game Over , Timeout.bmp" };
char* top_panel_game_status[4] = { "images/Human-waiting for next move.bmp","images/Human-paused.bmp","images/Machine_computing.bmp","images/Machine-paused.bmp"};

char* side_bar_images[NUMBER_BUTTONS_SIDE_BAR] = { "images/Reconfigue_mouse.bmp", "images/Reconfigue_cat.bmp", "images/Restart_game.bmp", "images/go_to_main_menu.bmp", "images/Quit_program.bmp" };
char* side_bar_images_unable[NUMBER_BUTTONS_SIDE_BAR] = { "images/Reconfigue_mouse_unable.bmp", "images/Reconfigue_cat_unable.bmp", "images/Restart_game_unable.bmp", "images/go_to_main_menu_unable.bmp", "images/Quit_program_unable.bmp" };

char* creatGame_top_panel[NUMBER_BUTTONS_TOP_PANEL_CREATE_GAME] = { "images/New_World_title.bmp", "images/save_world.bmp", "images/go_to_main_menu_new_world_.bmp", "images/Quit_program_new_world.bmp"};
char* createGame_side_bar_images[NUMBER_BUTTONS_SIDE_BAR] = { "images/place_mouse.bmp", "images/place_cat.bmp", "images/place_cheese.bmp", "images/place_wall.bmp", "images/place_empty_space.bmp" };


//create main game board
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
	(*view)->model = model;
	(*view)->HandleSystemEvent = HandleSystemEvent;
	if (model->modelMode == GAME)
	{
		sideBar = create_sideBar(side_bar_images);
		topPanel = create_topPanel();
		gridArea = create_gridArea(model);

	}
	else // if mode==EDIT
	{
		sideBar = create_sideBar(createGame_side_bar_images);
		topPanel = CreateWorld_topPanel();
		gridArea = create_gridArea();
	}


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

result showViewBoard(viewBoard* view,modelBoard* model) {
	result res;
	int quit=0;
	
	allBoards = SDL_SetVideoMode(800, 800, 0, 0);
	SDL_Color color = { 255, 255, 255 };
	SDL_FillRect(allBoards, 0, SDL_MapRGB(allBoards->format, color.r, color.g, color.b));
	if (model->modelMode == GAME) //we are in the game board
	{
		show_side_bar(view->sideBar);
		show_top_panel(view->topPanel);
		show_grid_area(view->gridArea);
	}
	else if (model->modelMode == EDIT)//we are in creating a new world board
	{
		show_side_bar(view->sideBar);
		show_CreateWorld_top_panel(view->topPanel);
		show_grid_area(view->gridArea);
	}
	

	while (quit == 0)
	{
		//While there's events to handle
		while (SDL_PollEvent(&event) != 0)
		{
			handle_gui_event(&event, view,model);
		}
	}

	res.code = SUCCESS;
	return res;
}

result freeViewBoard(viewBoard* view) {

}


void handle_gui_event(SDL_Event *ev, viewBoard* v,modelBoard* model) 
{
	switch (ev->type)
	{
	case SDL_QUIT:
		v->HandleSystemEvent(EXIT, 0, 0);
		break;
	case SDL_MOUSEBUTTONUP:
		if (model->modelMode ==GAME)
		{
			if ((ev->button.x > 0 && ev->button.x < 200) && (ev->button.y>0 && ev->button.y<600))
				button_click_side_panel(ev->button.x, ev->button.y, v); 
				if ((ev->button.x > 200 && ev->button.x < 700) && (ev->button.y>0 && ev->button.y<110))
					button_click_top_panel(ev->button.x, ev->button.y, v);
		}
		if (model->modelMode == EDIT)
		{
			if ((ev->button.x > 0 && ev->button.x < 200) && (ev->button.y>0 && ev->button.y<600))
			button_click_side_panel_new_world(ev->button.x, ev->button.y, v);
			if ((ev->button.x > 0 && ev->button.x < 800) && (ev->button.y>0 && ev->button.y<110))
			button_click_top_panel_new_world(ev->button.x, ev->button.y, v);
		}
		if ((ev->button.x > 230 && ev->button.x < 720) && (ev->button.y>120 && ev->button.y<610))
			button_click_game_board(ev->button.x, ev->button.y, v);
		break;
	case SDL_KEYDOWN:
		if (model->modelMode == GAME)
		{
			switch (ev->key.keysym.sym)
			{
			case SDLK_F1:
				v->HandleSystemEvent(RECONFIGURE_MOUSE, 0, 0);
				break;
			case SDLK_F2:
				v->HandleSystemEvent(RECONFIGURE_CAT, 0, 0);
				break;
			case SDLK_F3:
				v->HandleSystemEvent(RESTART_GAME, 0, 0);
				break;
			case SDLK_F4:
				v->HandleSystemEvent(GO_TO_MAIN_MENU, 0, 0);
				break;
			case SDLK_ESCAPE:
				v->HandleSystemEvent(EXIT, 0, 0);
				break;
			case SDLK_RSUPER:
				//right key was pressed
				break;
			case SDLK_LSUPER:
				//left key was pressed
				break;
			}
		}
		
		else if (model->modelMode==EDIT)
		{
			switch (ev->key.keysym.sym)
			{
			case SDLK_F1:
				v->HandleSystemEvent(GO_TO_MAIN_MENU, 0, 0);
				break;
			}
		}
	default:
		break;
	}
}

//checking where the left click was in the top panel and send to the controller the logical event
void button_click_side_panel(Uint16 x, Uint16 y, viewBoard* v)
{
	if (x > 15 && x < 197)
	{
		if (y>150 && y < 210)
			v->HandleSystemEvent(RECONFIGURE_MOUSE, 0, 0);
		else if (y>150+88 && y < 210+88)
			v->HandleSystemEvent(RECONFIGURE_CAT, 0, 0);
		else if (y>150+88*2 && y < 210+88*2)
			v->HandleSystemEvent(RESTART_GAME, 0, 0);
		else if (y>150 + 88*3 && y < 210 + 88*3)
			v->HandleSystemEvent(GO_TO_MAIN_MENU, 0, 0);
		else if (y>150 + 88*4 && y < 210 + 88*4)
			v->HandleSystemEvent(EXIT, 0, 0);
	}

}

//checking where the left click was in the top panel int the new world menu and send to the controller the logical event
void button_click_side_panel_new_world(Uint16 x, Uint16 y, viewBoard* v)
{
	if (x > 15 && x < 197)
	{
		if (y>150 && y < 210)
			v->HandleSystemEvent(PLACE_MOUSE, x, y);
		else if (y>150 + 88 && y < 210 + 88)
			v->HandleSystemEvent(PLACE_CAT, x, y);
		else if (y>150 + 88 * 2 && y < 210 + 88 * 2)
			v->HandleSystemEvent(PLACE_CHEESE, x, y);
		else if (y>150 + 88 * 3 && y < 210 + 88 * 3)
			v->HandleSystemEvent(PLACE_WALL, x, y);
		else if (y>150 + 88 * 4 && y < 210 + 88 * 4)
			v->HandleSystemEvent(PLACE_EMPTY_SPACE, x, y);
	}

}

//checking where the left click was in the top panel and send to the controller the logical event
void button_click_top_panel(Uint16 x, Uint16 y, viewBoard* v)
{
	if ((x>230 && x < 616) && (y>60 && y < 97)){
		v->HandleSystemEvent(SPACE, 0, 0);
		// fill!
	}
}

//checking where the left click was in the top panel in the new world menu and send to the controller the logical event
void button_click_top_panel_new_world(Uint16 x, Uint16 y, viewBoard* v)
{
	if (y>60 && y < 97)
	{
		if (x>15 && x < 197)
			v->HandleSystemEvent(SAVE_WORLD, 0, 0);
		else if (x>320 && x < 502)
			v->HandleSystemEvent(GO_TO_MAIN_MENU, 0, 0);
		else if (x>610 && x < 792)
			v->HandleSystemEvent(EXIT, 0, 0);
	}
}
void button_click_game_board(Uint16 x, Uint16 y, viewBoard* v)
{
	v->HandleSystemEvent(CLICK_ON_BOARD, x, y);
	//fill
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

Screen* create_sideBar(char** imagesArr)
{
	Screen* scr = (Screen*)malloc(sizeof(Screen));
	if (scr == NULL)
	{
		isError - 1;
		printf("ERROR: failed to allocate memory for screen\n");
		return NULL;
	}
	scr->screen = allBoards;
	
	scr->head = create_panel(200, 600, 0, 0, "side_bar.bmp", IMAGE, -1, scr, 1);
	apply_surfaceBoard(0, 100 , scr->head->componentProps.surface, allBoards);

	for (int i = 0; i < NUMBER_BUTTONS_SIDE_BAR; i++)
	{
		add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + i*MENUGAP + 30, imagesArr[i], BUTTON, 0, scr, 0), scr);
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


//Screen* create_gridArea()
//{
//	Screen* scr = (Screen*)malloc(sizeof(Screen));
//	if (scr == NULL)
//	{
//		isError - 1;
//		printf("ERROR: failed to allocate memory for grid\n");
//		return NULL;
//	}
//	scr->screen = allBoards;
//
//	scr->head = create_panel(800, 200, 0, 0, NULL, PANEL, -1, scr, 1);
//
//	for (int i = 0; i < 7; i++)
//	{
//		for (int j = 0; j < 7; j++)
//		{
//			add_child(create_panel(70, 70, 70 * j, 70 * i, "images/square.bmp", BUTTON, 0, scr, 0), scr);
//		}
//		
//	}
//
//	return scr;
//}
//
//void show_grid_area(Screen* scr)
//{
//	Panel* currentHead = scr->head;
//
//	for (int i = 0; i < 7; i++)
//	{
//		for (int j = 0; j < 7; j++)
//		{
//			apply_surfaceBoard(230 + j*70, 120 + i * 70, currentHead->next->componentProps.surface, allBoards);
//			currentHead = currentHead->next;
//		}
//		
//	}
//
//	SDL_Flip(allBoards);
//}

Screen* create_gridArea(modelBoard* model)
{
//	type boardTemp[GRID_SIZE][GRID_SIZE];
//	for (int i = 0; i < GRID_SIZE; i++)
//	{
//		for (int j = 0; j < GRID_SIZE; j++)
//
//		{
//			if (i == j)
//				boardTemp[i][j] = WALL;
//			else
//				boardTemp[i][j] = EMPTY;
//		}
//	}
//	boardTemp[1][3] = CAT_PIC;
//	boardTemp[4][1] = MOUSE_PIC;
//	boardTemp[5][6] = CHEESE;

	Screen* scr = (Screen*)malloc(sizeof(Screen));
	if (scr == NULL)
	{
		isError - 1;
		printf("ERROR: failed to allocate memory for grid\n");
		return NULL;
	}
	scr->screen = allBoards;

	scr->head = create_panel(800, 200, 0, 0, NULL, PANEL, -1, scr, 1);

	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)

		{
			switch (model->board[i][j]){
			case(EMPTY) :
				add_child(create_panel(70, 70, 70 * j, 70 * i, "images/square.bmp", BUTTON, 0, scr, 0), scr);
				break;
			case(CAT_PIC) :
				add_child(create_panel(70, 70, 70 * j, 70 * i, "images/cat.bmp", BUTTON, 0, scr, 0), scr);
				break;
			case(MOUSE_PIC) :
				add_child(create_panel(70, 70, 70 * j, 70 * i, "images/mouse.bmp", BUTTON, 0, scr, 0), scr);
				break;
			case(CHEESE) :
				add_child(create_panel(70, 70, 70 * j, 70 * i, "images/cheese.bmp", BUTTON, 0, scr, 0), scr);
				break;
			case(WALL) :
				add_child(create_panel(70, 70, 70 * j, 70 * i, "images/wall.bmp", BUTTON, 0, scr, 0), scr);
				break;
			default:
				break;
			}
			
		}

	}

	return scr;
}

void show_grid_area(Screen* scr)
{
	Panel* currentHead = scr->head;

	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			apply_surfaceBoard(230 + j * 70, 120 + i * 70, currentHead->next->componentProps.surface, allBoards);
			currentHead = currentHead->next;
		}

	}

	SDL_Flip(allBoards);
}

//create the 'create game' board
result CreateNewWorldBoard(viewBoard** view, void(*HandleSystemEvent) (viewBoardEvents event, int x, int y),
	modelBoard* model) {

	result res;
	Screen* sideBar;
	Screen* topPanel;
	Screen* gridArea;
	*view = (viewBoard*)malloc(sizeof(viewBoard));
	if (view == NULL)
	{
		res.code = -1;
		res.message = "ERROR: failed to allocate memory for board\n";
		return res;
	}
	(*view)->model = model;
	(*view)->HandleSystemEvent = HandleSystemEvent;
	sideBar = create_sideBar(createGame_side_bar_images);
	topPanel = CreateWorld_topPanel();
	gridArea = create_gridArea(model);

	if ((sideBar == NULL) || (topPanel == NULL) || (gridArea == NULL))
	{
		res.code = -1;
		res.message = "ERROR: failed to allocate memory for create game window\n";
		return res;
	}
	(*view)->topPanel = topPanel;
	(*view)->sideBar = sideBar;
	(*view)->gridArea = gridArea;

	res.code = SUCCESS;
	return res;
}

//create the 'create game' top_panel
Screen* CreateWorld_topPanel()
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
	for (int i = 0; i < NUMBER_BUTTONS_TOP_PANEL_CREATE_GAME; i++)
	{
		switch (i)
		{
		case 0:
			yOffset = 0;
			xOffset = 330;
			break;
		case 1:
			xOffset = 15;
			yOffset += 60;
			break;
		case 2:
			xOffset = 320;
			break;
		case 3:
			xOffset += 290;
			break;
		default:
			break;
		}

		add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + yOffset, creatGame_top_panel[i], type, 0, scr, 0), scr);
	}

	return scr;
}

//show the create new world top panel
void show_CreateWorld_top_panel(Screen* scr)
{
	int yOffset = 0;
	int xOffset = 0;
	Panel* currentHead = scr->head;
	for (int i = 0; i < NUMBER_BUTTONS_TOP_PANEL_CREATE_GAME; i++)
	{
		switch (i)
		{
		case 0:
			yOffset = 0;
			xOffset = 330;
			break;
		case 1:
			xOffset = 15;
			yOffset += 60;
			break;
		case 2:
			xOffset = 320;
			break;
		case 3:
			xOffset += 290;
			break;
		default:
			break;
		}

		apply_surfaceBoard(xOffset, yOffset, currentHead->next->componentProps.surface, allBoards);
		currentHead = currentHead->next;
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

