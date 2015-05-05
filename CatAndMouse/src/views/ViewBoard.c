#include "../views/ViewBoard.h"


int pause = 0 ;

//array for the displayed images
char* displayed_top_panel_images[NUMBER_BUTTONS_TOP_PANEL-2] = { "images/Mouse's _move.bmp", "images/2.bmp", "images/Machine_computing.bmp", "images/Pause Before Next Move.bmp" };

//arrays for the images in the top panel
char* top_panel_animal_move[2] = { "images/Cat_move.bmp", "images/Mouse's _move.bmp" };
char* top_panel_numbers[11] = { "images/0.bmp", "images/1.bmp", "images/2.bmp", "images/3.bmp", "images/4.bmp", "images/5.bmp", "images/6.bmp", "images/7.bmp", "images/8.bmp", "images/9.bmp","images/).bmp" };
char* top_panel_win_status[3] = { "images/Game_Over_Cat_Wins.bmp", "images/Game_Over_Mouse_Wins.bmp", "images/Game_Over_Timeout.bmp" };
char* top_panel_game_status[4] = { "images/Human-waiting.bmp","images/Human-paused.bmp","images/Machine_computing.bmp","images/Machine-paused.bmp"};
char* top_panel_pause[3] = { "images/Pause Before Next Move.bmp", "images/Pause.bmp", "images/Resume Game.bmp" };

//arrays for the images in the side bar
char* side_bar_images[NUMBER_BUTTONS_SIDE_BAR] = { "images/Reconfigue_mouse.bmp", "images/Reconfigue_cat.bmp", "images/Restart_game.bmp", "images/go_to_main_menu.bmp", "images/Quit_program.bmp" };
char* side_bar_images_unable[NUMBER_BUTTONS_SIDE_BAR] = { "images/Reconfigue_mouse_unable.bmp", "images/Reconfigue_cat_unable.bmp", "images/Restart_game_unable.bmp", "images/go_to_main_menu_unable.bmp", "images/Quit_program_unable.bmp" };

//arrays for the images in the top panel in create game mode
char* creatGame_top_panel[NUMBER_BUTTONS_TOP_PANEL_CREATE_GAME] = { "images/New_World_title.bmp", "images/save_world.bmp", "images/go_to_main_menu_new_world_.bmp", "images/Quit_program_new_world.bmp"};
char* createGame_side_bar_images[NUMBER_BUTTONS_SIDE_BAR] = { "images/place_mouse.bmp", "images/place_cat.bmp", "images/place_cheese.bmp", "images/place_wall.bmp", "images/place_empty_space.bmp" };
char* creatGame_titels[NUMBER_WORLD_TITELS] = { "images/New_World_title.bmp", "images/world1_title.bmp", "images/world2_title.bmp", "images/world3_title.bmp", "images/world4_title.bmp", "images/world5_title.bmp" };


/*Create new viewBoard
update the fields of the struct and return result*/
result createViewBoard(viewBoard** view, void(*HandleSystemEvent) (viewBoardEvents event, int x, int y),
	modelBoard* model, int worldsIndex) {
	
	pause = 0;

	result res;
	Screen* sideBar = NULL;
	Screen* topPanel = NULL;
	Screen* gridArea = NULL;

	*view = (viewBoard*)malloc(sizeof(viewBoard));
	(*view)->GameTopPanel = NULL;
	if (view == NULL)
	{
		result res;
		res.code = ERROR;
		res.message = "images/failed_to_allocate_memory.bmp";
		printMessages(res.message);
		return res;
	}
	(*view)->model = model;
	(*view)->HandleSystemEvent = HandleSystemEvent;
	(*view)->markedSquare.x = UNVALID_POS;
	(*view)->markedSquare.y = UNVALID_POS;
	
	if (model->modelMode == GAME)
	{
		//sideBar = create_sideBar(side_bar_images);
		sideBar=NULL;
		create_topPanel(*view);
		(*view)->WinnerTopPanel = NULL;
		sideBar = create_sideBar(side_bar_images_unable);
		gridArea = create_gridArea(model,*view);

	}
	else // if mode==EDIT
	{
		(*view)->markedSquare.x = 0;
		(*view)->markedSquare.y = 0;
		sideBar = create_sideBar(createGame_side_bar_images);
		topPanel = CreateWorld_topPanel(worldsIndex);
		gridArea = create_gridArea(model, *view);
		(*view)->WinnerTopPanel = NULL;
		(*view)->GameTopPanel = NULL;
	}


	if ((sideBar == NULL) || (gridArea==NULL))
	{
		res.code = -1;
		res.message = "ERROR: failed to allocate memory for game window\n";
		return res;
	}
	(*view)->topPanel = topPanel;
	(*view)->sideBar = sideBar;
	(*view)->gridArea = gridArea;
	(*view)->quitView = 0;

	res.code = SUCCESS;
	return res;
}

/* This function show the view according to the model
 and than wait for SDL events than pass them to the controller
 by calling the function HandleSystemEvent*/
result showViewBoard(viewBoard* view,modelBoard* model) {
	result res;
	
	allBoards = SDL_SetVideoMode(800, 800, 0, 0);
	if (allBoards == NULL) {
		result res;
		res.code = ERROR;
		res.message = "ERROR: failed to set video mode : %s\n";
		printf("ERROR: failed to set video mode: %s\n", SDL_GetError());
		return res;
	}
	SDL_Color color = { 255, 255, 255 };
	SDL_FillRect(allBoards, 0, SDL_MapRGB(allBoards->format, color.r, color.g, color.b));
	if (model->modelMode == GAME) //we are in the game board
	{
		show_side_bar(view->sideBar);
		show_top_panel(view);
		show_grid_area(view->gridArea);

		if (model->players[model->currentPlayer].type == COMPUTER)
			view->HandleSystemEvent(COMPUTER_MOVE,0,0);
	}
	else if (model->modelMode == EDIT)//we are in creating a new world board
	{
		show_side_bar(view->sideBar);
		show_CreateWorld_top_panel(view->topPanel);
		show_grid_area(view->gridArea);
	}

	while (view->quitView == 0)
	{
		//While there's events to handle
		while (SDL_PollEvent(&event) != 0)
		{
			handle_gui_event(&event, view,model);
		}
	}
	view->HandleSystemEvent(EXIT, 0, 0);
	res.code = SUCCESS;
	return res;
}


result freeViewBoard(viewBoard* view) {

	result res;
		res.code = 1;
		res.message="";

	if (view->GameTopPanel != NULL)
		// free top panel
		destroyList(view->GameTopPanel,freeWidget);
	if (view->WinnerTopPanel != NULL)
		freeWidget(view->WinnerTopPanel);
	if (view->sideBar != NULL)
		freeScreen(view->sideBar);
	if (view->gridArea != NULL)
		freeScreen(view->gridArea);
	if (view->topPanel!=NULL)
		freeScreen(view->topPanel);
	free(view);

	return res;
}

void handle_gui_event(SDL_Event *ev, viewBoard* v, modelBoard* model)
{
	if(ev->type ==  SDL_QUIT)
		v->quitView = 1;	
	if (model->modelMode == GAME) // if the mode is the game
	{
	if (pause == 1) { // can be clicked only if the game is paused
		switch (ev->type)
		{
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
				default:
					break;
			}
			break;
		default:
			break;
		}
		}
	else if(pause ==0){ // if the game isn't paused
		if (ev->type == SDL_MOUSEBUTTONUP){
			if ((ev->button.x > 200 && ev->button.x < 700) && (ev->button.y>0 && ev->button.y<110))
				button_click_top_panel(ev->button.x, ev->button.y, v);
		}
		else if (ev->type == SDL_KEYDOWN){
			switch(ev->key.keysym.sym){
			case SDLK_SPACE:
				pauseWasPressed(v);
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
		}
	}
}
	else if (model->modelMode == EDIT) //if the mode is edit
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
			break;
		default:
			break;
		}
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
	ListRef childrenlistTemp = v->GameTopPanel;

	do {
			widget* currentWidget= (widget*)headData(childrenlistTemp);
			if ((!strcmp(currentWidget->name,PAUSE_BUTTON_NAME)) && (checkClick(currentWidget,x,y)))
				pauseWasPressed(v);
			childrenlistTemp = tail(childrenlistTemp);
	} while (childrenlistTemp != NULL);
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

//checking where the left click was in the grid and send to the controller the logical event - in edit mode
void button_click_game_board(Uint16 x, Uint16 y, viewBoard* v)
{
	v->markedSquare.y =  (x-230) / 70;
	v->markedSquare.x =   (y-120) / 70;
	refreshViewBoard(v);
}

//checking where the left click was in the grid and send to the controller the logical event - in the game mode
void button_click_game_board_game(Uint16 x, Uint16 y, viewBoard* v)
{
	int newX;
	int newY;
	newX = (y - 120) / 70;
	newY = (x - 230) / 70;
	v->HandleSystemEvent(PLAYER_MOVED_TO,newX, newY);
}

/*creates the top panel*/
void create_topPanel(viewBoard* view)
{
	// Create empty widget that contain the panel
	widget* emptyPanelWidget = createNewWidget(PANEL,TOP_PANEL_WIDGET_NAME);
	emptyPanelWidget->x = 0;
	emptyPanelWidget->y = 0;
	emptyPanelWidget->width = 800;
	emptyPanelWidget->height = 200;

	// Create who turns widget
	widget* turnsWidget = createNewWidget(IMAGE,TURNS_WIDGET_NAME);
	turnsWidget->x = 300;
	turnsWidget->y = 10;
	turnsWidget->width = 150;
	turnsWidget->height = 30;

	// Create Hundreds digit widget
	widget* HundredsDigitWidget = createNewWidget(IMAGE,THIRD_DIGIT_WIDGET_NAME);
	HundredsDigitWidget->x = 300+150;
	HundredsDigitWidget->y = 10;
	HundredsDigitWidget->width = 10;
	HundredsDigitWidget->height = 50;

	// Create Hundreds digit widget
	widget* TensDigitWidget = createNewWidget(IMAGE,SECOND_DIGIT_WIDGET_NAME);
	TensDigitWidget->x = 300+150+10;
	TensDigitWidget->y = 10;
	TensDigitWidget->width = 10;
	TensDigitWidget->height = 50;

	// Create last digit widget
	widget* DigitWidget = createNewWidget(IMAGE,FIRST_DIGIT_WIDGET_NAME);
	DigitWidget->x = 300+150+10+10;
	DigitWidget->y = 10;
	DigitWidget->width = 10;
	DigitWidget->height = 50;

	// Create brace close widget
	widget* braceCloseWiget = createNewWidget(IMAGE,BRACE_CLOSE_WIDGET_NAME);
	braceCloseWiget->x = 300+150+10+10+20;
	braceCloseWiget->y = 10;
	braceCloseWiget->width = 10;
	braceCloseWiget->height = 50;

	// Create free text widget
	widget* freeTextWidget = createNewWidget(IMAGE,FREE_TEXT_WIDGET_NAME);
	freeTextWidget->x = 250;
	freeTextWidget->y = 35;
	freeTextWidget->width = 300;
	freeTextWidget->height = 50;

	// Create pause button widget
	widget* pauseButtonWodget = createNewWidget(BUTTON,PAUSE_BUTTON_NAME);
	pauseButtonWodget->x = 230;
	pauseButtonWodget->y = 65;
	pauseButtonWodget->width = 500;
	pauseButtonWodget->height = 50;

	// Create the list and save in the view
	ListRef tempListRef;
	view->GameTopPanel = newList(emptyPanelWidget);
	tempListRef = append(view->GameTopPanel,turnsWidget);
	tempListRef = append(tempListRef,HundredsDigitWidget);
	tempListRef = append(tempListRef,TensDigitWidget);
	tempListRef = append(tempListRef,DigitWidget);
	tempListRef = append(tempListRef,braceCloseWiget);
	tempListRef = append(tempListRef,freeTextWidget);
	tempListRef = append(tempListRef,pauseButtonWodget);
}

/*shows the top panel*/
void show_top_panel(viewBoard* view)
{
	ListRef childrenlistTemp = view->GameTopPanel;

	do {
		widget* currentWidget= (widget*)headData(childrenlistTemp);

		if (!strcmp(currentWidget->name,TOP_PANEL_WIDGET_NAME))
				currentWidget->widget_surface = allBoards;

		if (!strcmp(currentWidget->name,TURNS_WIDGET_NAME)) {
				if (view->model->currentPlayer == MOUSE)
					setWidgetImage(currentWidget,top_panel_animal_move[1]);
				else if (view->model->currentPlayer == CAT)
					setWidgetImage(currentWidget, top_panel_animal_move[0]);
		}

		if (!strcmp(currentWidget->name,THIRD_DIGIT_WIDGET_NAME)) {
			int i = (view->model->movesBeforeTie) / 100;
			setWidgetImage(currentWidget, top_panel_numbers[i]);
		}

		if (!strcmp(currentWidget->name,SECOND_DIGIT_WIDGET_NAME)) {
			int i = (view->model->movesBeforeTie) / 10;
			setWidgetImage(currentWidget, top_panel_numbers[i]);
		}

		if (!strcmp(currentWidget->name,FIRST_DIGIT_WIDGET_NAME)) {
			int i = (view->model->movesBeforeTie) % 10;
			setWidgetImage(currentWidget, top_panel_numbers[i]);
		}

		if (!strcmp(currentWidget->name,BRACE_CLOSE_WIDGET_NAME)) {
			setWidgetImage(currentWidget, top_panel_numbers[10]);
		}

		if (!strcmp(currentWidget->name,FREE_TEXT_WIDGET_NAME)) {
			if (!pause &&
				(view->model->players[view->model->currentPlayer].type == USER))
				setWidgetImage(currentWidget, top_panel_game_status[0]);
			if (!pause &&
				(view->model->players[view->model->currentPlayer].type == COMPUTER))
				setWidgetImage(currentWidget, top_panel_game_status[2]);
			if (pause &&
				(view->model->players[view->model->currentPlayer].type == USER))
				setWidgetImage(currentWidget, top_panel_game_status[1]);
			if (pause &&
				(view->model->players[view->model->currentPlayer].type == COMPUTER))
				setWidgetImage(currentWidget, top_panel_game_status[3]);
		}

		if (!strcmp(currentWidget->name,PAUSE_BUTTON_NAME)) {
			if (!pause &&
				(view->model->players[view->model->currentPlayer].type == USER))
				setWidgetImage(currentWidget, top_panel_pause[0]);
			if (pause &&
				(view->model->players[view->model->currentPlayer].type == USER))
				setWidgetImage(currentWidget, top_panel_pause[1]);
			if (pause &&
				(view->model->players[view->model->currentPlayer].type == COMPUTER))
				setWidgetImage(currentWidget, top_panel_pause[1]);;
		}

		drawWidget(currentWidget,allBoards);
		childrenlistTemp = tail(childrenlistTemp);
	} while (childrenlistTemp != NULL);

	SDL_Flip(allBoards);
}

/*creates the side bar*/
Screen* create_sideBar(char** imagesArr)
{
	Screen* scr = (Screen*)malloc(sizeof(Screen));
	if (scr == NULL)
	{
		result res;
		res.code = ERROR;
		res.message = "images/failed_to_allocate_memory.bmp";
		printMessages(res.message);
		return NULL;
	}
	scr->screen = allBoards;
	
	scr->head = create_panel(200, 600, 0, 0, "images/side_bar.bmp", IMAGE, -1, scr, 1);

	for (int i = 0; i < NUMBER_BUTTONS_SIDE_BAR; i++)
	{
		add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + i*MENUGAP + 30, imagesArr[i], BUTTON, 0, scr, 0), scr);
	}

	return scr;
}

/*shows the side bar*/
void show_side_bar(Screen* scr)
{
	Panel* currentHead = scr->head;

	for (int i = 0; i < NUMBER_BUTTONS_SIDE_BAR; i++)
	{
		apply_surfaceBoard(15, 120 + i*MENUGAP + 30, currentHead->next->componentProps.surface, allBoards);
		currentHead = currentHead->next;
	}

	if (SDL_Flip(allBoards) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}

/*creates the grid area*/
Screen* create_gridArea(modelBoard* model,viewBoard* v)
{
	Screen* scr = (Screen*)malloc(sizeof(Screen));
	if (scr == NULL)
	{
		result res;
		res.code = ERROR;
		res.message = "images/failed_to_allocate_memory.bmp";
		printMessages(res.message);
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

/*shoes the grid area*/
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

	if (SDL_Flip(allBoards) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}


//create the 'create game' top_panel - in edit mode
Screen* CreateWorld_topPanel(int worldsndex)
{

	Screen* scr = (Screen*)malloc(sizeof(Screen));
	if (scr == NULL)
	{
		result res;
		res.code = ERROR;
		res.message = "images/failed_to_allocate_memory.bmp";
		printMessages(res.message);
		return NULL;
	}
	creatGame_top_panel[0] = creatGame_titels[worldsndex];
	scr->screen = allBoards;
	scr->head = create_panel(800, 200, 0, 0, NULL, PANEL, -1, scr, 1);
	int yOffset = 0;
	int xOffset = 0;
	int type = 1;
	//Panel* currentHead = scr->head;
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
	if (SDL_Flip(allBoards) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}
void apply_surfaceBoard(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
	//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;

	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;

	
	//Blit the surface
	if (SDL_BlitSurface(source, NULL, destination, &offset) != 0) {
		printf("ERROR: failed to blit image: %s\n", SDL_GetError());
	}
}

/*upfate the pictures according to the current state in the model 
and show the view again*/
result refreshViewBoard(viewBoard* view) {

	result res;
		res.code = 1;
		res.message="";

	//refresh the top panel
	if (view->model->modelMode == GAME)
	{
		//create_topPanel(view->model);
		if ((view->model->winner == NONE) && (view->model->movesBeforeTie>0))
			show_top_panel(view);
		else
			printWinnerTopPaenl(view->model->winner,view);
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
				case WALL:
					update_panel_picture(item, "images/red_square_wall.bmp");
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

	if (view->model->modelMode == GAME) {
		if (view->model->players[view->model->currentPlayer].type == COMPUTER &&
				view->model->winner == NONE)
			view->HandleSystemEvent(COMPUTER_MOVE,0,0);
	}
	return res;
}


//nimrod add it when there is a winner to the game
void printWinnerTopPaenl(playerAnimal winner,viewBoard* view)
{

	widget* winnerTopPanel = createNewWidget(IMAGE,"");
	winnerTopPanel->x = 0;
	winnerTopPanel->y = 0;
	winnerTopPanel->width = 800;
	winnerTopPanel->height = 200;
	//freeTopPanel_List(view->topPanel);
	if (winner == CAT)
	{
		setWidgetImage(winnerTopPanel, top_panel_win_status[0]);
		drawWidget(winnerTopPanel,allBoards);
		//add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + 0, top_panel_win_status[0], 1, 0, view->topPanel, 0), view->topPanel);
	}
	else if (winner == MOUSE)
	{
		setWidgetImage(winnerTopPanel, top_panel_win_status[1]);
		drawWidget(winnerTopPanel,allBoards);
		//add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + 0, top_panel_win_status[1], 1, 0, view->topPanel, 0), view->topPanel);
	}
	else
	{
		setWidgetImage(winnerTopPanel, top_panel_win_status[2]);
		//add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + 0, top_panel_win_status[2], 1, 0, view->topPanel, 0), view->topPanel);
		drawWidget(winnerTopPanel,allBoards);
	}
	//show_top_panel(view->topPanel, view->model);
	pause = 1; //  the game enters to the pause state
	refreshSidePanel(view);
}

/*if pause was pressed refresh the side bar to be available/unavailable
and show the right photo on the top panel*/
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
	show_top_panel(view);
}

/*refresh the side bar to be available/unavailable*/
result refreshSidePanel(viewBoard* view) {

	result res;
		res.code = 1;
		res.message="";

	Panel *item = view->sideBar->head->next;
		if (pause == 1) //if the game is paused (mean that it was not paused before and the puase button was pressed
		{
			for (int i = 0; i < NUMBER_BUTTONS_SIDE_BAR; i++)
			{
				update_panel_picture(item, side_bar_images[i]);
				item = item->next;
			}
			
		}
		else if (pause == 0){ // if the game is not paused (mean that it was paused before and the puase button was presse
			for (int i = 0; i < NUMBER_BUTTONS_SIDE_BAR; i++)
			{
				update_panel_picture(item, side_bar_images_unable[i]);
				item = item->next;
			}
		}
		show_side_bar(view->sideBar);

		return res;
}

/*prints the error message*/
void printMessages(char* message) 
{
	createMessage(message);
}

/*creates the error message*/
void createMessage(char* message)
{
	int quit = 0;
	Screen* scr = (Screen*)malloc(sizeof(Screen));
	if (scr == NULL)
	{
		result res;
		res.code = ERROR;
		res.message = "images/failed_to_allocate_memory.bmp";
		printMessages(res.message);
	}
	scr->screen = allBoards;

	scr->head = create_panel(300, 200, 0, 0, "images/message_white.bmp", IMAGE, -1, scr, 1);
	Panel* currentHead = scr->head;
	apply_surfaceBoard(300, 200, currentHead->componentProps.surface, allBoards);
	if (!strcmp(message, "images/no_current_player.bmp") || !strcmp(message, "images/cheese_is_missing.bmp") || !strcmp(message, "images/mosue_is_missing.bmp") || !strcmp(message, "images/cat_is_missing.bmp"))
	{
		add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY +108, "images/cant_save_invalid_world_title.bmp", IMAGE, 0, scr, 0), scr);
		apply_surfaceBoard(345, 210, currentHead->next->componentProps.surface, allBoards);
	}
	else {
		add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + 108, "images/erroe_title.bmp", IMAGE, 0, scr, 0), scr);
		apply_surfaceBoard(345, 210, currentHead->next->componentProps.surface, allBoards);
	}
		add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + 138, message, IMAGE, 0, scr, 0), scr);
		apply_surfaceBoard(375, 210 + 50, currentHead->next->next->componentProps.surface, allBoards);
		add_child(create_panel(BUTTON_WIDTH, BUTTON_HEIGHT, button_offsetX, button_offsetY + 188, "images/back_chosen.bmp", BUTTON, 0, scr, 0), scr);
		apply_surfaceBoard(385, 210 + 120, scr->head->next->next->next->componentProps.surface, allBoards);
		if (SDL_Flip(allBoards) != 0) {
			printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
		}


		while (quit == 0)
		{
			//While there's events to handle
			while (SDL_PollEvent(&event) != 0)
			{
				if ((&event)->type == SDL_MOUSEBUTTONUP){
					if ((&event)->button.x >= 385)
						if ((&event)->button.x <= 385 + 175 )
						{
							if ((&event)->button.y >= 330)
								if ((&event)->button.y <= 330 + 58)
								{
									quit = 1;
									break;
								}
						}
				}
			}
		}

}

