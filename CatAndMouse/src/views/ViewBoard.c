#include "ViewBoard.h"

//change it
int pause = 0;

//array for the displayed images
char* displayed_top_panel_images[NUMBER_BUTTONS_TOP_PANEL-2] = { "images/Mouse's _move.bmp", "images/2.bmp", "images/Machine_computing.bmp", "images/Pause Before Next Move.bmp" };
//arrays for the images in the top panel
char* top_panel_animal_move[2] = { "images/Cat_move.bmp", "images/Mouse's _move.bmp" };
char* top_panel_numbers[11] = { "images/0.bmp", "images/1.bmp", "images/2.bmp", "images/3.bmp", "images/4.bmp", "images/5.bmp", "images/6.bmp", "images/7.bmp", "images/8.bmp", "images/9.bmp","images/).bmp" };
char* top_panel_win_status[3] = { "images/Game Over � Cat Wins.bmp", "images/Game Over � Mouse Wins.bmp", "images/Game Over � Timeout.bmp" };
char* top_panel_game_status[4] = { "images/Human-waiting.bmp","images/Human-paused.bmp","images/Machine_computing.bmp","images/Machine-paused.bmp"};
char* top_panel_pause[3] = { "images/Pause Before Next Move.bmp", "images/Pause.bmp", "images/Resume Game.bmp" };

char* side_bar_images[NUMBER_BUTTONS_SIDE_BAR] = { "images/Reconfigue_mouse.bmp", "images/Reconfigue_cat.bmp", "images/Restart_game.bmp", "images/go_to_main_menu.bmp", "images/Quit_program.bmp" };
char* side_bar_images_unable[NUMBER_BUTTONS_SIDE_BAR] = { "images/Reconfigue_mouse_unable.bmp", "images/Reconfigue_cat_unable.bmp", "images/Restart_game_unable.bmp", "images/go_to_main_menu_unable.bmp", "images/Quit_program_unable.bmp" };

char* creatGame_top_panel[NUMBER_BUTTONS_TOP_PANEL_CREATE_GAME] = { "images/New_World_title.bmp", "images/save_world.bmp", "images/go_to_main_menu_new_world_.bmp", "images/Quit_program_new_world.bmp"};
char* createGame_side_bar_images[NUMBER_BUTTONS_SIDE_BAR] = { "images/place_mouse.bmp", "images/place_cat.bmp", "images/place_cheese.bmp", "images/place_wall.bmp", "images/place_empty_space.bmp" };
char* creatGame_titels[NUMBER_WORLD_TITELS] = { "images/New_World_title.bmp", "images/world1_title.bmp", "images/world2_title.bmp", "images/world3_title.bmp", "images/world4_title.bmp", "images/world5_title.bmp" };


//create main game board
result createViewBoard(viewBoard** view, void(*HandleSystemEvent) (viewBoardEvents event, int x, int y),
	modelBoard* model, int worldsIndex) {
	
	pause = 0;

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
	(*view)->markedSquare.x = UNVALID_POS;
	(*view)->markedSquare.y = UNVALID_POS;
	
	if (model->modelMode == GAME)
	{
		sideBar = create_sideBar(side_bar_images);
		topPanel = create_topPanel(model);
		gridArea = create_gridArea(model,*view);

	}
	else // if mode==EDIT
	{
		(*view)->markedSquare.x = 0;
		(*view)->markedSquare.y = 0;
		sideBar = create_sideBar(createGame_side_bar_images);
		topPanel = CreateWorld_topPanel(worldsIndex);
		gridArea = create_gridArea(model, *view);
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
		show_top_panel(view->topPanel,model);
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

void handle_gui_event(SDL_Event *ev, viewBoard* v, modelBoard* model)
{
	if (model->modelMode == GAME)
	{
	if (pause == 0) {
		switch (ev->type)
		{
		case SDL_QUIT:
			v->HandleSystemEvent(EXIT, 0, 0);
			break;
		case SDL_MOUSEBUTTONUP :
				if ((ev->button.x > 0 && ev->button.x < 200) && (ev->button.y>0 && ev->button.y<600))
					button_click_side_panel(ev->button.x, ev->button.y, v);
				if ((ev->button.x > 200 && ev->button.x < 700) && (ev->button.y>0 && ev->button.y<110))
					button_click_top_panel(ev->button.x, ev->button.y, v);
				if ((ev->button.x > 230 && ev->button.x < 720) && (ev->button.y>120 && ev->button.y<610))
					button_click_game_board_game(ev->button.x, ev->button.y, v);
				break;
		case SDL_KEYDOWN:
			switch (ev->key.keysym.sym)
			{
			case (SDLK_SPACE) :
				pauseWasPressed(v);
				break;
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
				case SDLK_RIGHT://right key was pressed
					if (model->players[model->currentPlayer].playerPos.y < 6)
						v->HandleSystemEvent(PLAYER_MOVED_TO, model->players[model->currentPlayer].playerPos.x, model->players[model->currentPlayer].playerPos.y + 1);
					break;
				case SDLK_LEFT://left key was pressed
					if (model->players[model->currentPlayer].playerPos.y > 0)
						v->HandleSystemEvent(PLAYER_MOVED_TO, model->players[model->currentPlayer].playerPos.x, model->players[model->currentPlayer].playerPos.y - 1);
					break;
				case SDLK_UP:if (model->players[model->currentPlayer].playerPos.x > 0)
					v->HandleSystemEvent(PLAYER_MOVED_TO, model->players[model->currentPlayer].playerPos.x - 1, model->players[model->currentPlayer].playerPos.y);;
					break;
				case SDLK_DOWN:
					if (model->players[model->currentPlayer].playerPos.x < 6)
						v->HandleSystemEvent(PLAYER_MOVED_TO, model->players[model->currentPlayer].playerPos.x + 1, model->players[model->currentPlayer].playerPos.y);
					break;
				default:
					break;
			}
		default:
			break;
		}
		}
	else {
		if (ev->type == SDL_MOUSEBUTTONUP){
			if ((ev->button.x > 200 && ev->button.x < 700) && (ev->button.y>0 && ev->button.y<110))
				button_click_top_panel(ev->button.x, ev->button.y, v);
		}
		else if (ev->type == SDL_KEYDOWN){
			if (ev->key.keysym.sym == SDLK_SPACE)
				pauseWasPressed(v);
		}
	}
}
	else if (model->modelMode == EDIT)
	{
		switch (ev->type)
		{
		case SDL_QUIT:
			v->HandleSystemEvent(EXIT, 0, 0);
			break;
		case SDL_MOUSEBUTTONUP:
			if ((ev->button.x > 0 && ev->button.x < 200) && (ev->button.y>0 && ev->button.y < 600))
				button_click_side_panel_new_world(ev->button.x, ev->button.y, v);
			if ((ev->button.x > 0 && ev->button.x < 800) && (ev->button.y>0 && ev->button.y < 110))
				button_click_top_panel_new_world(ev->button.x, ev->button.y, v);
			if ((ev->button.x > 230 && ev->button.x < 720) && (ev->button.y>120 && ev->button.y < 610))
				button_click_game_board(ev->button.x, ev->button.y, v);
			break;
		case SDL_KEYDOWN:
			switch (ev->key.keysym.sym)
			{
			case SDLK_F1:
				v->HandleSystemEvent(GO_TO_MAIN_MENU, 0, 0);
				break;
			case SDLK_s:
				v->HandleSystemEvent(SAVE_WORLD, 0, 0);
				break;
			case SDLK_m:
				v->HandleSystemEvent(PLACE_MOUSE, v->markedSquare.x, v->markedSquare.y);
				break;
			case SDLK_c:
				v->HandleSystemEvent(PLACE_CAT, v->markedSquare.x, v->markedSquare.y);
				break;
			case SDLK_p:
				v->HandleSystemEvent(PLACE_CHEESE, v->markedSquare.x, v->markedSquare.y);
				break;
				case SDLK_w :
				v->HandleSystemEvent(PLACE_WALL, v->markedSquare.x, v->markedSquare.y);
				break;
				case (SDLK_SPACE) :
					v->HandleSystemEvent(PLACE_EMPTY_SPACE, v->markedSquare.x, v->markedSquare.y);
					break;
			case SDLK_ESCAPE:
				v->HandleSystemEvent(EXIT, 0, 0);
				break;
			case SDLK_RIGHT://right key was pressed
				if (v->markedSquare.y < 6){
					v->markedSquare.y++;
					refreshViewBoard(v);
				}
				break;
			case SDLK_LEFT://left key was pressed
				if (v->markedSquare.y > 0){
					v->markedSquare.y--;
					refreshViewBoard(v);
				}
				break;
			case SDLK_UP:
				if (v->markedSquare.x > 0){
					v->markedSquare.x--;
					refreshViewBoard(v);
				}
				break;
			case SDLK_DOWN:
				if (v->markedSquare.x  < 6){
					v->markedSquare.x++;
					refreshViewBoard(v);
				}
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}



//void handle_gui_event(SDL_Event *ev, viewBoard* v,modelBoard* model) 
//{
//
//	switch (ev->type)
//	{
//	case SDL_QUIT:
//		v->HandleSystemEvent(EXIT, 0, 0);
//		break;
//	case SDL_MOUSEBUTTONUP:
//		if (model->modelMode ==GAME)
//		{
//			if ((ev->button.x > 0 && ev->button.x < 200) && (ev->button.y>0 && ev->button.y<600))
//				button_click_side_panel(ev->button.x, ev->button.y, v); 
//				if ((ev->button.x > 200 && ev->button.x < 700) && (ev->button.y>0 && ev->button.y<110))
//					button_click_top_panel(ev->button.x, ev->button.y, v);
//		}
//		if (model->modelMode == EDIT)
//		{
//			if ((ev->button.x > 0 && ev->button.x < 200) && (ev->button.y>0 && ev->button.y<600))
//			button_click_side_panel_new_world(ev->button.x, ev->button.y, v);
//			if ((ev->button.x > 0 && ev->button.x < 800) && (ev->button.y>0 && ev->button.y<110))
//			button_click_top_panel_new_world(ev->button.x, ev->button.y, v);
//		}
//		if ((ev->button.x > 230 && ev->button.x < 720) && (ev->button.y>120 && ev->button.y<610))
//			button_click_game_board(ev->button.x, ev->button.y, v);
//		break;
//	case SDL_KEYDOWN:
//		if (model->modelMode == GAME)
//		{
//			{
//			case SDLK_F1:
//				v->HandleSystemEvent(RECONFIGURE_MOUSE, 0, 0);
//				break;
//			case SDLK_F2:
//				v->HandleSystemEvent(RECONFIGURE_CAT, 0, 0);
//				break;
//			case SDLK_F3:
//				v->HandleSystemEvent(RESTART_GAME, 0, 0);
//				break;
//			case SDLK_F4:
//				v->HandleSystemEvent(GO_TO_MAIN_MENU, 0, 0);
//				break;
//			case SDLK_ESCAPE:
//				v->HandleSystemEvent(EXIT, 0, 0);
//				break;
//			case SDLK_RSUPER:
//				//right key was pressed
//				break;
//			case SDLK_LSUPER:
//				//left key was pressed
//				break;
//			}
//		}
//		
//		else if (model->modelMode==EDIT)
//		{
//			switch (ev->key.keysym.sym)
//			{
//			case SDLK_F1:
//				v->HandleSystemEvent(GO_TO_MAIN_MENU, 0, 0);
//				break;
//			}
//		}
//	default:
//		break;
//	}
//}

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
			v->HandleSystemEvent(PLACE_MOUSE, v->markedSquare.x, v->markedSquare.y);
		else if (y>150 + 88 && y < 210 + 88)
			v->HandleSystemEvent(PLACE_CAT, v->markedSquare.x, v->markedSquare.y);
		else if (y>150 + 88 * 2 && y < 210 + 88 * 2)
			v->HandleSystemEvent(PLACE_CHEESE, v->markedSquare.x, v->markedSquare.y);
		else if (y>150 + 88 * 3 && y < 210 + 88 * 3)
			v->HandleSystemEvent(PLACE_WALL, v->markedSquare.x, v->markedSquare.y);
		else if (y>150 + 88 * 4 && y < 210 + 88 * 4)
			v->HandleSystemEvent(PLACE_EMPTY_SPACE, v->markedSquare.x, v->markedSquare.y);
	}

}

//checking where the left click was in the top panel and send to the controller the logical event
void button_click_top_panel(Uint16 x, Uint16 y, viewBoard* v)
{
	if ((x>230 && x < 616) && (y>60 && y < 97)){
		//v->HandleSystemEvent(SPACE, 0, 0);
		//if (pause == 0) // the pause wasn't clicked before
		//{
		//	pause = 1;
		//	pauseGame(v);
		//}
		//else //the pause was clicked before
		//{
		//	unpauseGame(v);
		//}
		pauseWasPressed(v);
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
	v->markedSquare.y =  (x-230) / 70;
	v->markedSquare.x =   (y-120) / 70;
	refreshViewBoard(v);
}

void button_click_game_board_game(Uint16 x, Uint16 y, viewBoard* v)
{
	int newX;
	int newY;
	newX = (y - 120) / 70;
	newY = (x - 230) / 70;
	v->HandleSystemEvent(PLAYER_MOVED_TO,newX, newY);
}



Screen* create_topPanel(modelBoard* model)
{
	int factor;
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
	for (int i = 0; i < NUMBER_BUTTONS_TOP_PANEL-2; i++)
	{

		switch (i)
		{
		case 0: //the <animal>move
			add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + yOffset, top_panel_animal_move[model->currentPlayer], type, 0, scr, 0), scr);
			break;
		case 1: //the moves before tie
			/*if (model->currentPlayer == MOUSE)
				xOffset = 140;
			else 
				xOffset = 120;*/
			factor = 1;
			int moveBeforeTie = model->movesBeforeTie;
			int temp = moveBeforeTie;
			while (temp)
			{
				temp = temp / 10;
				factor = factor * 10;
			}
			for (int j = 0; j <3;j++)
			//while (factor>1)
			{
				if (factor >1)
				{
					factor = factor / 10;

					add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + yOffset, top_panel_numbers[moveBeforeTie / factor], type, 0, scr, 0), scr);
					moveBeforeTie = moveBeforeTie % factor;
				}
				else {
					add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + yOffset, "images/empty_number.bmp", type, 0, scr, 0), scr);
				}
				xOffset += 7;

			}
			add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + yOffset, top_panel_numbers[10], type, 0, scr, 0), scr);
			break;
		case 2: //the game status (sewcond line)
			yOffset = 30;
			xOffset = 0;
			if (pause == 1)
			{
				if (model->players[model->currentPlayer].type == USER) //human and paused
					add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + yOffset, top_panel_game_status[1], type, 0, scr, 0), scr);
				else //machine and paused
					add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + yOffset, top_panel_game_status[3], type, 0, scr, 0), scr);
			}
			else
			{
				if (model->players[model->currentPlayer].type == USER) //human and not paused
					add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + yOffset, top_panel_game_status[0], type, 0, scr, 0), scr);
				else //machine and not paused
					add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + yOffset, top_panel_game_status[2], type, 0, scr, 0), scr);
			}
			break;
		case 3: //the third line
			xOffset = 0;
			yOffset += 30;
			if (model->players[model->currentPlayer].type == COMPUTER) //if the current player is a machine
				add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + yOffset, top_panel_pause[0], type, 0, scr, 0), scr);
			else if (model->players[model->currentPlayer].type == USER)//if the current player is a human
				add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + yOffset, top_panel_pause[1], type, 0, scr, 0), scr);
			else if (pause == 1) // if the game is paused
				add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + yOffset, top_panel_pause[2], type, 0, scr, 0), scr);
			break;
		default:
			break;
		}
	}
	
	return scr;
}

void show_top_panel(Screen* scr, modelBoard* model)
{
	int yOffset = 0;
	int xOffset = 0;
	int moveBeforeTie = 0;
	Panel* currentHead = scr->head;
	for (int i = 0; i < NUMBER_BUTTONS_TOP_PANEL-2; i++)
	{

		switch (i)
		{
		case 0: //the <animal>move
			apply_surfaceBoard(330 + xOffset, yOffset, currentHead->next->componentProps.surface, allBoards);
			currentHead = currentHead->next;
			break;
		case 1: //the moves before tie
			moveBeforeTie = model->movesBeforeTie;

			if (model->currentPlayer == MOUSE)
				xOffset = 140;
			else
				xOffset = 120;

			//while (moveBeforeTie > 0)
			for (int j = 0; j < 3;j++)
			{
				apply_surfaceBoard(330 + xOffset, yOffset, currentHead->next->componentProps.surface, allBoards);
				//moveBeforeTie = moveBeforeTie / 10;
				xOffset += 9;
				currentHead = currentHead->next;
			}
			xOffset += 7;
			apply_surfaceBoard(330 + xOffset, yOffset, currentHead->next->componentProps.surface, allBoards);
			currentHead = currentHead->next;
			break;
		case 2: //the game status (sewcond line)
			yOffset = 30;
			xOffset = 0;
			apply_surfaceBoard(330 + xOffset, yOffset, currentHead->next->componentProps.surface, allBoards);
			currentHead = currentHead->next;
			break;
		case 3: //the third line
			xOffset = 0;
			yOffset += 30;
			apply_surfaceBoard(330 + xOffset, yOffset, currentHead->next->componentProps.surface, allBoards);
			currentHead = currentHead->next;
			break;
		default:
			break;
		}
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

Screen* create_gridArea(modelBoard* model,viewBoard* v)
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
			if (i == v->markedSquare.x && j == v->markedSquare.y && model->board[i][j] == EMPTY)
			{
				add_child(create_panel(70, 70, 70 * i, 70 * j, "images/red_square.bmp", BUTTON, 0, scr, 0), scr);
			}
			else
			{
				switch (model->board[i][j]){
				case(EMPTY) :
					add_child(create_panel(70, 70, 70 * i, 70 * j, "images/square.bmp", BUTTON, 0, scr, 0), scr);
					break;
				case(CAT_PIC) :
					add_child(create_panel(70, 70, 70 * i, 70 * j, "images/cat.bmp", BUTTON, 0, scr, 0), scr);
					break;
				case(MOUSE_PIC) :
					add_child(create_panel(70, 70, 70 * i, 70 * j, "images/mouse.bmp", BUTTON, 0, scr, 0), scr);
					break;
				case(CHEESE) :
					add_child(create_panel(70, 70, 70 * i, 70 * j, "images/cheese.bmp", BUTTON, 0, scr, 0), scr);
					break;
				case(WALL) :
					add_child(create_panel(70, 70, 70 * i, 70 * j, "images/wall.bmp", BUTTON, 0, scr, 0), scr);
					break;
				default:
					break;
				}
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


//create the 'create game' top_panel
Screen* CreateWorld_topPanel(int worldsndex)
{

	Screen* scr = (Screen*)malloc(sizeof(Screen));
	if (scr == NULL)
	{
		isError - 1;
		printf("ERROR: failed to allocate memory for screen\n");
		return NULL;
	}
	creatGame_top_panel[0] = creatGame_titels[worldsndex];
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

result refreshTopPanel(viewBoard* view)
{
	int factor;
	// refresh the top panel
	Panel* currentHead = view->topPanel->head;
	modelBoard* model = view->model;
	//Panel *item = view->topPanel->head->next;
	int moveBeforeTie = 0;
	for (int i = 0; i < NUMBER_BUTTONS_TOP_PANEL-2; i++)
	{
		switch (i)
		{
		case 0: //the <animal>move
			update_panel_picture(currentHead, top_panel_animal_move[model->currentPlayer]);
			currentHead = currentHead->next;
			break;
		case 1: //the moves before tie
			/*if (model->currentPlayer == MOUSE)
			xOffset = 140;
			else
			xOffset = 120;*/
			factor = 1;
			int moveBeforeTie = model->movesBeforeTie;
			int temp = moveBeforeTie;
			while (temp)
			{
				temp = temp / 10;
				factor = factor * 10;
			}
			for (int j = 0; j < 3; j++)
			//while (factor>1)
			{
				if (factor > 1) {
					factor = factor / 10;
					update_panel_picture(currentHead, top_panel_numbers[moveBeforeTie / factor]);
					moveBeforeTie = moveBeforeTie % factor;
				}
				else {
					update_panel_picture(currentHead, "images/empty_number.bmp");
				}
				
				currentHead = currentHead->next;
			}
			update_panel_picture(currentHead, top_panel_numbers[10]);
			currentHead = currentHead->next;
			//i = i + 2;
			break;
		case 2: //the game status (sewcond line)
			if (pause == 1)
			{
				if (model->players[model->currentPlayer].type == USER) //human and paused
					update_panel_picture(currentHead, top_panel_game_status[1]);
				else //machine and paused
					update_panel_picture(currentHead, top_panel_game_status[3]);
			}
			else
			{
				if (model->players[model->currentPlayer].type == USER) //human and not paused
					update_panel_picture(currentHead, top_panel_game_status[0]);
				else //machine and not paused
					update_panel_picture(currentHead, top_panel_game_status[2]);
			}
			currentHead = currentHead->next;
			break;
		case 3: //the third line
			if (model->players[model->currentPlayer].type == COMPUTER) //if the current player is a machine
				update_panel_picture(currentHead, top_panel_pause[0]);
			else if (model->players[model->currentPlayer].type == USER)//if the current player is a human
				update_panel_picture(currentHead, top_panel_pause[1]);
			else if (pause == 1) // if the game is paused
				update_panel_picture(currentHead, top_panel_pause[2]);		
			currentHead = currentHead->next;
			break;
		default:
			break;
		}
	}
	show_top_panel(view->topPanel, model); // hila - check if this is the right model
}
result refreshViewBoard(viewBoard* view) {
	//refresh the top panel
	if (view->model->modelMode == GAME)
	{
		refreshTopPanel(view,view->model);
		//create_topPanel(view->model);
		//show_top_panel(view->topPanel,view->model);		
	}		

	// refresh the grid
	Panel *item = view->gridArea->head->next;

	for (int i = 0 ; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j ++) {
			if (i == view->markedSquare.x && j == view->markedSquare.y)
			{
				switch (view->model->board[i][j]){
				case EMPTY:
					update_panel_picture(item, "images/red_square.bmp");
					break;
				case MOUSE_PIC:
					update_panel_picture(item, "images/red_square_mouse.bmp");
					break;
				case CHEESE:
					update_panel_picture(item, "images/red_square_cheese.bmp");
					break;
				case CAT_PIC:
					update_panel_picture(item, "images/red_square_cat.bmp");
					break;

				}
			}
			else
			{
				switch (view->model->board[i][j]) {
				case(EMPTY) :
					update_panel_picture(item, "images/square.bmp");
					break;
				case(CAT_PIC) :
					update_panel_picture(item, "images/cat.bmp");
					break;
				case(MOUSE_PIC) :
					update_panel_picture(item, "images/mouse.bmp");
					break;
				case(CHEESE) :
					update_panel_picture(item, "images/cheese.bmp");
					break;
				case(WALL) :
					update_panel_picture(item, "images/wall.bmp");
					break;
				default:
					break;
				}
			}
			item = item->next;
		}
	}
	show_grid_area(view->gridArea);
}


//nimrod add it when there is a winner to the game
void printWinnerTopPaenl(playerAnimal winner,viewBoard* view)
{
	//freeTopPanel_List(view->topPanel);
	if (winner == CAT)
	{
		add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + 0, top_panel_win_status[0], 1, 0, view->topPanel, 0), view->topPanel);
	}
	else if (winner == MOUSE)
	{
		add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + 0, top_panel_win_status[1], 1, 0, view->topPanel, 0), view->topPanel);
	}
	else
	{
		add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + 0, top_panel_win_status[2], 1, 0, view->topPanel, 0), view->topPanel);
	}
	show_top_panel(view, view->model);
	//pauseGame(view);
}

//void pauseGame(viewBoard* view)
//{
//	refreshSidePanel(view);
//}
//
//void unpauseGame(viewBoard* view)
//{
//
//}
void pauseWasPressed(viewBoard* view)
{
	if (pause == 0) // the pause wasn't clicked before
	{
		pause = 1;
	}
	else if (pause == 1) //the pause was clicked before
	{
		pause = 0;
	}
	refreshSidePanel(view);
}

result refreshSidePanel(viewBoard* view) {
	SDL_Color color = { 60, 60, 60 };
	SDL_Color colorWhite = { 255, 255, 255 };
	Panel *item = view->sideBar->head->next;
		if (pause == 0) // if the game is not paused (mean that it was paused before and the puase button was pressed
		{
			for (int i = 0; i < NUMBER_BUTTONS_SIDE_BAR; i++)
			{
				update_panel_picture(item, side_bar_images[i]);
				item = item->next;
			}
			
		}
		else if (pause == 1){ //if the game is paused (mean that it was not paused before and the puase button was pressed
			for (int i = 0; i < NUMBER_BUTTONS_SIDE_BAR; i++)
			{
				update_panel_picture(item, side_bar_images_unable[i]);
				item = item->next;
			}
		}
		refreshTopPanel(view);
	show_side_bar(view->sideBar);
}
