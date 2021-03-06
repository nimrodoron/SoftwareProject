#include "controller.h"


int loadGame = 1; //indicate that we are/aren't in Load Game menu
int bTerminate = 0;
int WorldToOpen = 1; // indicate which world is loaded
int worldsMenus = 1; //indicate that we are in menus with arrows: save game, load game, edit game

/*photos for the worlds*/
char* worlds[NUMBER_OF_WORLDS] = { NULL, "world_1.txt", "world_2.txt", "world_3.txt", "world_4.txt", "world_5.txt" };

/*for main menu*/
char* main_menu_buttons_image[NUMBER_BUTTONS_MAIN_MENU] = { "images/cat_mouse_title.bmp", "images/new_game.bmp", "images/load_game.bmp", "images/create_game.bmp", "images/edit_game.bmp", "images/quit.bmp" }; /*the images in the main menu*/
char* main_menu_buttons_image_chosen[NUMBER_BUTTONS_MAIN_MENU] = { "images/cat_mouse_title.bmp", "images/new_game_chosen.bmp", "images/load_game_chosen.bmp", "images/create_game_chosen.bmp", "images/edit_game_chosen.bmp", "images/quit_chosen.bmp" };
int stateId_main_menu[NUMBER_BUTTONS_MAIN_MENU] = { 0, 1, 19, 18, 24, 7 };

/*for choose cat menu*/
char* choose_your_cat_menu_buttons_image[NUMBER_BUTTONS_CHOOSE_CAT_MENU] = { "images/choose_your_cat_title.bmp", "images/human.bmp", "images/machine.bmp", "images/back.bmp" }; /*the images in the choose cat menu menu*/
char* choose_your_cat_menu_buttons_image_chosen[NUMBER_BUTTONS_CHOOSE_CAT_MENU] = { "images/choose_your_cat_title.bmp", "images/human_chosen.bmp", "images/machine_chosen.bmp", "images/back_chosen.bmp" };
int stateId_choose_your_cat_menu[NUMBER_BUTTONS_CHOOSE_CAT_MENU] = {1, 2, 3, 0};

/*for choose mouse menu*/
char* choose_your_mouse_menu_buttons_image[NUMBER_BUTTONS_CHOOSE_MOUSE_MENU] = { "images/choose_your_mouse_title.bmp", "images/human.bmp", "images/machine.bmp", "images/back.bmp" }; /*the images in the choose mouse menu menu*/
char* choose_your_mouse_menu_buttons_image_chosen[NUMBER_BUTTONS_CHOOSE_MOUSE_MENU] = { "images/choose_your_mouse_title.bmp", "images/human_chosen.bmp", "images/machine_chosen.bmp", "images/back_chosen.bmp" };
int stateId_choose_your_mouse_menu[NUMBER_BUTTONS_CHOOSE_MOUSE_MENU] = {2, 9, 4, 1 };

/*for choose cat skill level menu*/
char* choose_cat_skills_menu_buttons_image[NUMBER_BUTTONS_CAT_SKILL_LEVEL_MENU+9] = { "images/choose_cat_skill_level_title.bmp", "images/skill_level5.bmp", "images/done.bmp", "images/back.bmp", "images/skill_level1.bmp", "images/skill_level2.bmp", "images/skill_level3.bmp", "images/skill_level4.bmp","images/skill_level5.bmp", "images/skill_level6.bmp", "images/skill_level7.bmp", "images/skill_level8.bmp", "images/skill_level9.bmp" }; /*the images in the choose mouse menu menu*/
char* choose_cat_skills_menu_buttons_image_chosen[NUMBER_BUTTONS_CAT_SKILL_LEVEL_MENU + 9] = { "images/choose_cat_skill_level_title.bmp", "images/skill_level5_chosen.bmp", "images/done_chosen.bmp", "images/back_chosen.bmp", "images/skill_level1_chosen.bmp", "images/skill_level2_chosen.bmp", "images/skill_level3_chosen.bmp", "images/skill_level4_chosen.bmp", "images/skill_level5_chosen.bmp", "images/skill_level6_chosen.bmp", "images/skill_level7_chosen.bmp", "images/skill_level8_chosen.bmp", "images/skill_level9_chosen.bmp" };
int stateId_choose_cat_skill_level[NUMBER_BUTTONS_CAT_SKILL_LEVEL_MENU] = { 3, 11, 8, 1 };


/*for choose mouse skill level menu*/
char* choose_mouse_skills_menu_buttons_image[NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU + 9] = { "images/choose_mouse_skill_level_title.bmp", "images/skill_level5.bmp", "images/done.bmp", "images/back.bmp", "images/skill_level1.bmp", "images/skill_level2.bmp", "images/skill_level3.bmp", "images/skill_level4.bmp", "images/skill_level5.bmp", "images/skill_level6.bmp", "images/skill_level7.bmp", "images/skill_level8.bmp", "images/skill_level9.bmp" }; /*the images in the choose mouse menu menu*/
char* choose_mouse_skills_menu_buttons_image_chosen[NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU + 9] = { "images/choose_mouse_skill_level_title.bmp", "images/skill_level5_chosen.bmp", "images/done_chosen.bmp", "images/back_chosen.bmp", "images/skill_level1_chosen.bmp", "images/skill_level2_chosen.bmp", "images/skill_level3_chosen.bmp", "images/skill_level4_chosen.bmp","images/skill_level5_chosen.bmp", "images/skill_level6_chosen.bmp", "images/skill_level7_chosen.bmp", "images/skill_level8_chosen.bmp", "images/skill_level9_chosen.bmp" };
int stateId_choose_mouse_skill_level[NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU] = { 4, 10, 5, 2 };


/*for load game menu*/
char* load_game_menu_buttons_image[NUMBER_BUTTONS_LOAD_GAME_MENU + 5] = { "images/Load_game_title.bmp", "images/world_1.bmp", "images/done.bmp", "images/back.bmp", "images/world_1.bmp", "images/world_2.bmp", "images/world_3.bmp", "images/world_4.bmp", "images/world_5.bmp" };
char* load_game_menu_buttons_image_chosen[NUMBER_BUTTONS_LOAD_GAME_MENU + 5] = { "images/Load_game_title.bmp", "images/world_1_chosen.bmp", "images/done_chosen.bmp", "images/back_chosen.bmp", "images/world_1_chosen.bmp", "images/world_2_chosen.bmp", "images/world_3_chosen.bmp", "images/world_4_chosen.bmp", "images/world_5_chosen.bmp" };
int stateId_load_game[NUMBER_BUTTONS_LOAD_GAME_MENU] = { 5, 22,20, 0 };

/*photos for the 'can't save world' errors*/
char* cant_save_world_images[5] = { "images/cant_save_invalid_world_title.bmp", "images/cat_is_missing.bmp", "images/mosue_is_missing.bmp", "images/cheese_is_missing.bmp", "images/back_chosen.bmp" };

/*for edit game menu*/
char* edit_game_menu_buttons_image[NUMBER_BUTTONS_LOAD_GAME_MENU + 5] = { "images/edit_game_title.bmp", "images/world_1.bmp", "images/done.bmp", "images/back.bmp", "images/world_1.bmp", "images/world_2.bmp", "images/world_3.bmp", "images/world_4.bmp", "images/world_5.bmp" };
char* edit_game_menu_buttons_image_chosen[NUMBER_BUTTONS_LOAD_GAME_MENU + 5] = { "images/edit_game_title.bmp", "images/world_1_chosen.bmp", "images/done_chosen.bmp", "images/back_chosen.bmp", "images/world_1_chosen.bmp", "images/world_2_chosen.bmp", "images/world_3_chosen.bmp", "images/world_4_chosen.bmp", "images/world_5_chosen.bmp" };
int stateId_edit_game[NUMBER_BUTTONS_LOAD_GAME_MENU] = { 6, 22, 23, 0 };

/*for save game menu*/
char* save_game_menu_buttons_image[NUMBER_BUTTONS_LOAD_GAME_MENU + 5] = { "images/save-world_title.bmp", "images/world_1.bmp", "images/done.bmp", "images/back.bmp", "images/world_1.bmp", "images/world_2.bmp", "images/world_3.bmp", "images/world_4.bmp", "images/world_5.bmp" };
char* save_game_menu_buttons_image_chosen[NUMBER_BUTTONS_LOAD_GAME_MENU + 5] = { "images/save-world_title.bmp", "images/world_1_chosen.bmp", "images/done_chosen.bmp", "images/back_chosen.bmp", "images/world_1_chosen.bmp", "images/world_2_chosen.bmp", "images/world_3_chosen.bmp", "images/world_4_chosen.bmp", "images/world_5_chosen.bmp" };
int stateId_save_game[NUMBER_BUTTONS_LOAD_GAME_MENU] = { 7, 22, 25, 12 };

/*if we didn't get parameters in the console mode then start the program with the gui*/
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

	quit_main_menu();

	SDL_Quit();

}

/*if we get in the console mode the arguments -console cat or -console mouse
 * then print q and exit*/
void handle_event_console()
{
	printf("%s", "q\n");
	exit(0);
}

/*initializing the array of the menus*/
void initialize_states(){
	states[0] = build_all_view(main_menu_buttons_image, main_menu_buttons_image_chosen, stateId_main_menu, 1, -1, NUMBER_BUTTONS_MAIN_MENU);
	states[1] = build_all_view(choose_your_cat_menu_buttons_image, choose_your_cat_menu_buttons_image_chosen, stateId_choose_your_cat_menu, 1, -1, NUMBER_BUTTONS_CHOOSE_CAT_MENU);
	states[2] = build_all_view(choose_your_mouse_menu_buttons_image, choose_your_mouse_menu_buttons_image_chosen, stateId_choose_your_mouse_menu, 1, -1, NUMBER_BUTTONS_CHOOSE_MOUSE_MENU);
	states[3] = build_all_view(choose_cat_skills_menu_buttons_image, choose_cat_skills_menu_buttons_image_chosen, stateId_choose_cat_skill_level, 1, 5, NUMBER_BUTTONS_CAT_SKILL_LEVEL_MENU);
	states[4] = build_all_view(choose_mouse_skills_menu_buttons_image, choose_mouse_skills_menu_buttons_image_chosen, stateId_choose_mouse_skill_level, 1, 5, NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU);
	states[5] = build_all_view(load_game_menu_buttons_image, load_game_menu_buttons_image_chosen, stateId_load_game, 1, 1, NUMBER_BUTTONS_LOAD_GAME_MENU);
	states[6] = build_all_view(edit_game_menu_buttons_image, edit_game_menu_buttons_image_chosen, stateId_edit_game, 1, 1, NUMBER_BUTTONS_LOAD_GAME_MENU);
	states[7] = build_all_view(save_game_menu_buttons_image, save_game_menu_buttons_image_chosen, stateId_save_game, 1, 1, NUMBER_BUTTONS_LOAD_GAME_MENU);
	
}

/*for the menus events*/
void while_handle_event()
{
	while (quit == 0)
	{
		//While there's events to handle
		while (SDL_PollEvent(&event) != 0)
		{
			handle_event(&event, currentView);
		}
	}
}

/*for the menus events*/
void handle_event(SDL_Event *ev, View* v)
{
	switch (ev->type)
	{
	case SDL_QUIT:
		quit = 1;
		break;
	case SDL_MOUSEBUTTONUP:
		button_click(ev->button.x, ev->button.y, v);
		break;
	case SDL_KEYDOWN:
		switch (ev->key.keysym.sym){
		case SDLK_TAB:
			tab_click(v);
			break;
		case SDLK_RETURN:
			enter_click(v);
			break;
		case SDLK_UP:
			if ((currentView->model->level != -1) && (v->model->marked_button == 1)){
				Panel* current = v->screen->head->next->next;
				handale_click(current, 458, 108, v);
			}
			break;
		case SDLK_DOWN:
			if ((currentView->model->level != -1) && (v->model->marked_button == 1))
			{
				Panel* current = v->screen->head->next->next;
				handale_click(current, 456, 133, v);
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

/*if enter was pressed*/
void enter_click(View* v){
	int markedButton = v->model->marked_button;
	Panel* current = v->screen->head->next;
	int i = 0;
	for (i = 0; i < markedButton; i++){
		current = current->next;
	}
	handale_click(current,0,0,v);
}

/*if tab was pressed*/
void tab_click(View* v)
{
	int markedButton = v->model->marked_button;
	Panel* current = v->screen->head->next;
	int i = 0;
	for (i = 0; i < markedButton; i++){
		current = current->next;
	}
	if (markedButton == v->screen->head->size-1) //if the 'chosen' is the last button and should move to the first one
	{
		if ((v->model->level != -1) && (markedButton == 3)) //for update the skill-level button 
		{
			setImage(current, v->model->images[markedButton]);
			current->enabled = false;
			setImage(v->screen->head->next->next, v->model->chosen_images[v->model->level + 3]);
			v->screen->head->next->next->enabled = true;
			v->model->marked_button = 1;
		}
		else
		{
			setImage(current, v->model->images[markedButton]);
			current->enabled = false;
			setImage(v->screen->head->next->next, v->model->chosen_images[1]);
			v->screen->head->next->next->enabled = true;
			v->model->marked_button = 1;
		}
	}

	else //the standard move from one button to the next
	{
		if ((v->model->level != -1) && (markedButton == 1)) //if the skill-level button is the 'chosen'
		{
			setImage(current, v->model->images[v->model->level + 3]);
			current->enabled = false;
			setImage(current->next, v->model->chosen_images[markedButton + 1]);
			current->next->enabled = true;
			v->model->marked_button += 1;
		}
		else
		{
			setImage(current, v->model->images[markedButton]);
			current->enabled = false;
			setImage(current->next, v->model->chosen_images[markedButton + 1]);
			current->next->enabled = true;
			v->model->marked_button += 1;
		}
		
	}
	draw_screen("Cat&Mouse",v->screen);
}

/*Identifies which button was pressed, change the view and passed the right button to 'handale_click'*/
void button_click(Uint16 x, Uint16 y,View* v)
	{
	int markedButtonIndex = 0;
	int markedButton = v->model->marked_button;
	Panel *button = v->screen->head->next;
	Panel* current = v->screen->head->next;
	int level = v->model->level;
	while (button != NULL && quit == 0)
	{
			if (x >= button->componentProps.dest_rect->x)
				if (x <= button->componentProps.dest_rect->x + button->componentProps.dest_rect->w)
				{
					if (y >= button->componentProps.dest_rect->y)
						if (y <= button->componentProps.dest_rect->y + button->componentProps.dest_rect->h)
						{
							/*for update the current screen before moving to the next*/
							v->model->marked_button = markedButtonIndex; 
							for (int i = 0; i < markedButton; i++){
								current = current->next;
							}
							if (level != -1)
							{
								if ((markedButton == 1)&&(markedButtonIndex !=1))//the skill button was pressed
								{
									setImage(current, v->model->images[markedButton + level + 2]); //update the button that was 'chosen' to regular		
									current->enabled = false;
									setImage(button, v->model->chosen_images[markedButtonIndex++]); //update the button that was regular to 'chosen'					
									button->enabled = true;
								}
								else if ((markedButton!=1)&&(markedButtonIndex==1)){//the skill button was pressed but wasn't highlithed before
									setImage(current, v->model->images[markedButton]);//update the button that was 'chosen' to regular
									current->enabled = false;
									setImage(button, v->model->chosen_images[level + 3]); //update the button that was regular to 'chosen'
									if (x >= button->componentProps.dest_rect->x + 147){ // if the press was in the levels buttons 
										if (x <= button->componentProps.dest_rect->x + button->componentProps.dest_rect->w)
										{
											if (y >= button->componentProps.dest_rect->y){
												if (y <= button->componentProps.dest_rect->y + button->componentProps.dest_rect->h - 36)
												{
													button->enabled = false;
												}
											}
										}
									}
									else //  the press was on the button itself 
									button->enabled = true;
								}
							}
							else //the regulear screen
							{
								setImage(current, v->model->images[markedButton]); //update the button that was 'chosen' to regular
								current->enabled = false;
								setImage(button, v->model->chosen_images[markedButtonIndex++]); //update the button that was regular to 'chosen'
								button->enabled = true;
							}
							draw_screen("Cat&Mouse",v->screen);
							handale_click(button,x,y,v);
						}
				}
		button = button->next;
		markedButtonIndex++;
	}
}


/*doing the right action according the buttons thag was pressed and the currently menu*/
void handale_click(Panel* button, Uint16 x, Uint16 y,View* v)
{
	//playerAnimal editedPlayer = MOUSE;
	switch(button->nextState){
	case 0: // if the back was pressed from the choose your cat menu
		if (loadGame == 0 && currentView == states[1]) // the load game menu was pressed before 
		{
			loadGame = 1;
			currentView = states[5];
		}
		else
		{
			loadGame = 1;
			currentView = states[0];
		}
		worldsMenus = 1;
		draw_screen("Cat&Mouse", currentView->screen);
		break;
	case 20: //load game was pressed, update the flag and then go to choose your cat menu
		loadGame = 0; 
		worldsMenus = 1;
		currentView = states[1];
		draw_screen("Cat&Mouse", currentView->screen);
		break;
	case 1: // from main menu go to choose your cat menu
		currentView = states[1];
		draw_screen("Cat&Mouse", currentView->screen);
		break;
	case 19://load game was pressed
		currentView = states[5];
		draw_screen("Cat&Mouse", currentView->screen);
		worldsMenus =0;
		break;
	case 23://if the done button was pressed from the edit mode menu
		quit = 1;
		mainviewboard(cat, mouse, catLevel, mouseLevel, EDIT, WorldToOpen);
		break;
	case 24: //the edit game was preesed from the main menu 
		currentView = states[6];
		draw_screen("Cat&Mouse", currentView->screen);
		worldsMenus = 0;
		break;
	case 18: //if create game was pressed from the main menu
		quit = 1;
		mainviewboard(cat, mouse, catLevel, mouseLevel, EDIT,0);
		break;
	case 9: //in 'choose your mouse menu' human was chosen and then go to the main game screen
		mouse = USER;
		if (cat == USER){
			catLevel = -1;
		}
		if (mouse == USER){
			mouseLevel = -1;
		}
		quit = 1;
		mainviewboard(cat, mouse, catLevel, mouseLevel, GAME, WorldToOpen);
		break;
	case 5: //going to the main game
		if (cat == USER){
			catLevel = -1;
		}
		if (mouse == USER){
			mouseLevel = -1;
		}
		quit = 1;
		mainviewboard(cat, mouse, catLevel, mouseLevel, GAME, WorldToOpen);
		break;
	case 12: //selecting back from type selection menu for the mouse in reconfigure mouse mode
		quit = 1;
		break;
	case 14:
		mouse = USER;
		updateModelBoardMouse(mouse, mouseLevel);
		quit = 1;
		break;
	case 13://selecting done in mouse skill level menu in reconfigure mouse mode
		updateModelBoardMouse(mouse, mouseLevel);
		quit = 1;
		break;
	case 15: //selecting human in choose your cat menu in reconfigure mode
			cat = USER;
			updateModelBoardCat(cat, catLevel);
			quit = 1;
			break;
	case 17://selecting done in mouse skill level menu in reconfigure mouse mode
		updateModelBoardCat(cat, catLevel);
		quit = 1;
		break;
	case 7: //quit was pressed
		quit = 1;
		break;
	case 2:
		cat = USER;
		currentView = states[2];
		draw_screen("Cat&Mouse", currentView->screen);
		break;
	case 8: // 'in choose your cat menu' human was chosen
		currentView = states[2];
		draw_screen("Cat&Mouse", currentView->screen);
		break;
	case 3: //'in choose your cat menu' machine was chosen
		cat = COMPUTER;
		currentView = states[button->nextState];
		draw_screen("Cat&Mouse", currentView->screen);
		break;
	case 4: //in 'choose your mouse menu' machine was chosen
		mouse = COMPUTER;
		currentView = states[button->nextState];
		currentView->model->level = 5;
		draw_screen("Cat&Mouse", currentView->screen);
		break;
	case 16: //in 'choose your cat menu' machine was chosen
		cat = COMPUTER;
		currentView = states[3];
		currentView->model->level = 5;
		draw_screen("Cat&Mouse", currentView->screen);
		break;
	case 22: //we are in the worlds menus: load game, save game, edit game
		worldsMenus = 0;
		handaleUpDoawArrowas(button, x, y, v, MOUSE);
		break;
	case 11: //level button was pressed from 'choose your cat skill level menu'
		handaleUpDoawArrowas(button, x, y, v, cat);
		break;
	case 10: //level button was pressed for 'choose your mouse skill level menu'
		handaleUpDoawArrowas(button, x, y, v, MOUSE);
		break;
	case 25://if the done button was pressed in the save world menu;
		save(WorldToOpen);
		quit =1;
		break;
	default:
	currentView = states[button->nextState];
	draw_screen("Cat&Mouse",currentView->screen);
	break;

	}
}


void handaleUpDoawArrowas(Panel* button, Uint16 x, Uint16 y, View* v, playerAnimal editedPlayer)
{
	if (v->model->level != -1)
	{
		if (x >= button->componentProps.dest_rect->x + 147)
			if (x <= button->componentProps.dest_rect->x + button->componentProps.dest_rect->w)
			{
				if (y >= button->componentProps.dest_rect->y)
					if (y <= button->componentProps.dest_rect->y + button->componentProps.dest_rect->h - 36)
					{
						if (button->enabled == true)
							handale_up_level_button(button, v);
						else
						{
							button->enabled = true;
						}
					}
					else
					{
						if (y >= button->componentProps.dest_rect->y + 26)
							if (y <= button->componentProps.dest_rect->y + button->componentProps.dest_rect->h)
							{
								if (button->enabled == true)
									handale_down_level_button(button, v);
								else
								{
									button->enabled = true;
								}
							}
					}
			}

		if (editedPlayer == CAT)
		{
			catLevel = v->model->level;
		}
		else
		{
			mouseLevel = v->model->level;
		}
		if (worldsMenus == 0)
			WorldToOpen = v->model->level;
	}

}

/*when pressing on the up arrow*/
void handale_up_level_button(Panel* button,View* v)
{
	if (worldsMenus == 0)
	{
		if (v->model->level<5){
			v->model->level++;
			char* chosenImagePath = v->model->chosen_images[currentView->model->level + 4 - 1];
			setImage(v->screen->head->next->next, chosenImagePath);// the next chosen image from the array
			draw_screen("Cat&Mouse", v->screen);
		}
	}
	else
	{
		if (v->model->level<9){
			v->model->level++;
			char* chosenImagePath = v->model->chosen_images[currentView->model->level + 4 - 1];
			setImage(v->screen->head->next->next, chosenImagePath);// the next chosen image from the array
			draw_screen("Cat&Mouse", v->screen);
		}
	}
}

/*when pressing on the down arrow*/
void handale_down_level_button(Panel* button, View* v)
{
	if(v->model->level>1){
		v->model->level--;
			char* chosenImagePath = v->model->chosen_images [v->model->level +4-1];
			setImage(v->screen->head->next->next, chosenImagePath);// the next chosen image from the array
			draw_screen("Cat&Mouse", v->screen);
	}

}

/*going to the game board with the right mode EDIT or GAME*/
void mainviewboard(playerType catType, playerType mouseType, int catLevel, int mouseLevel,mode mod,int worldsIndex)
{
	char* filename = worlds[worldsIndex];
	player cat;
	player mouse;


	if (catLevel ==0) catLevel = 5;
	if (mouseLevel == 0) mouseLevel = 5;

	mouse.type = mouseType;
	mouse.level = mouseLevel;
	cat.type = catType;
	cat.level = catLevel;

	if (mod == EDIT)
	{
		createBoardController(EDIT, filename, cat, mouse, NONE,worldsIndex);

	}
	else if (mod == GAME){
		createBoardController(GAME, filename, mouse, cat, MOUSE, worldsIndex);
	}
	 showView();
}

/*when pressing on reconfigure Mouse button*/
void reconfigureMouseFunction(int level, playerType type,modelBoard* model)
{
	quit = 0;
	int marked_button_choose_menu;
	// the global parameters of the mouse and level
	mouseLevel = level; 
	mouse = type;

	if (type == COMPUTER)
	{
		marked_button_choose_menu = 2;
		choose_mouse_skills_menu_buttons_image_chosen[1] = choose_mouse_skills_menu_buttons_image_chosen[level + 3];
	}
	else if (type == USER)
	{
		marked_button_choose_menu = 1;
	}
	int stateId_choose_your_mouse_menu_recon[NUMBER_BUTTONS_CHOOSE_MOUSE_MENU] = { 2, 14, 4, 12 };
	int stateId_choose_mouse_skill_level_recon[NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU] = { 4, 10, 13, 2 };
	states[2] = build_all_view(choose_your_mouse_menu_buttons_image, choose_your_mouse_menu_buttons_image_chosen, stateId_choose_your_mouse_menu_recon, marked_button_choose_menu, -1, NUMBER_BUTTONS_CHOOSE_MOUSE_MENU);
	states[4] = build_all_view(choose_mouse_skills_menu_buttons_image, choose_mouse_skills_menu_buttons_image_chosen, stateId_choose_mouse_skill_level_recon, 1, level, NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU);

	if (type == COMPUTER)
	{
		currentView = states[4];
	}
	else if (type == USER)
	{
		currentView = states[2];
	}
	draw_screen("Cat&Mouse", currentView->screen);
	while_handle_event();
	freeStates();
}

/*when pressing on reconfigure cat button*/
void reconfigureCatFunction(int level, playerType type, modelBoard* model)
{
	quit = 0;
	int marked_button_choose_menu;
	// the global parameters of the mouse and level
	catLevel = level;
	cat = type;

	if (type == COMPUTER)
	{
		marked_button_choose_menu = 2;
		choose_cat_skills_menu_buttons_image_chosen[1] = choose_cat_skills_menu_buttons_image_chosen[level + 3];
	}
	else if (type == USER)
	{
		marked_button_choose_menu = 1;
	}
	int stateId_choose_your_cat_menu_recon[NUMBER_BUTTONS_CHOOSE_CAT_MENU] = { 1, 15, 16, 12 };
	int stateId_choose_cat_skill_level_recon[NUMBER_BUTTONS_CAT_SKILL_LEVEL_MENU] = { 3, 11, 17, 1 };
	states[1] = build_all_view(choose_your_cat_menu_buttons_image, choose_your_cat_menu_buttons_image_chosen, stateId_choose_your_cat_menu_recon, marked_button_choose_menu, -1, NUMBER_BUTTONS_CHOOSE_CAT_MENU);
	states[3] = build_all_view(choose_cat_skills_menu_buttons_image, choose_cat_skills_menu_buttons_image_chosen, stateId_choose_cat_skill_level_recon, 1,level, NUMBER_BUTTONS_CAT_SKILL_LEVEL_MENU);

	if (type == COMPUTER)
	{
		currentView = states[3];
	}
	else if (type == USER)
	{
		currentView = states[1];
	}
	draw_screen("Cat&Mouse", currentView->screen);
	while_handle_event();
	freeStates();
}

/*when pressing on Go the main menu button*/
void GoToMainMenu()
{
	//freeControllerAfterEventsFinished();
	//initialize_states();
	currentView = states[0];
	draw_screen("Cat&Mouse", currentView->screen);
	//restore the defult states
	quit = 0;
	WorldToOpen = 1;
	loadGame = 1; 
	worldsMenus = 1;

	//While the user hasn't quit
	while_handle_event();
}

/*opens the save world menu after it was pressed from the game board*/
void save_world(modelBoard* model)
{
	quit = 0;
	WorldToOpen = 1;
	worldsMenus = 0;
	states[7] = build_all_view(save_game_menu_buttons_image, save_game_menu_buttons_image_chosen, stateId_save_game, 1, 1, NUMBER_BUTTONS_LOAD_GAME_MENU);
	currentView = states[7];
	draw_screen("Cat&Mouse", currentView->screen);
	while_handle_event();
}

/*saving the game and continue to the game board*/
void save(int worldsIndex)
{
	char* filename = worlds[worldsIndex];
	SaveWorldToFile(controller->model, filename);
	mainviewboard(cat, mouse, catLevel, mouseLevel, EDIT, worldsIndex);
}

void quit_main_menu()
{
	freeStates();
}

/*frees the state array*/
void freeStates()
{
	for (int i = 0; i < 8; i++)
	{
		if (states[i] != NULL)
			freeView(states[i]);
		states[i]=NULL;
	}
}
