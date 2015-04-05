#include "controller.h"
#include <SDL_image.h>
#include <stdbool.h>
#include "../models/ModelBoard.h"
#include "ControllerBoard.h"


/*for main menu*/

char* main_menu_buttons_image[NUMBER_BUTTONS_MAIN_MENU] = { "images/cat_mouse_title.bmp", "images/new_game.bmp", "images/load_game.bmp", "images/create_game.bmp", "images/edit_game.bmp", "images/quit.bmp" }; /*the images in the main menu*/
char* main_menu_buttons_image_chosen[NUMBER_BUTTONS_MAIN_MENU] = { "images/cat_mouse_title.bmp", "images/new_game_chosen.bmp", "images/load_game_chosen.bmp", "images/create_game_chosen.bmp", "images/edit_game_chosen.bmp", "images/quit_chosen.bmp" };
int stateId_main_menu[NUMBER_BUTTONS_MAIN_MENU] = { 0, 1, 4, 5, 6, 7 };

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
// Hila change

/*for choose mouse skill level menu*/
char* choose_mouse_skills_menu_buttons_image[NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU + 9] = { "images/choose_mouse_skill_level_title.bmp", "images/skill_level5.bmp", "images/done.bmp", "images/back.bmp", "images/skill_level1.bmp", "images/skill_level2.bmp", "images/skill_level3.bmp", "images/skill_level4.bmp", "images/skill_level5.bmp", "images/skill_level6.bmp", "images/skill_level7.bmp", "images/skill_level8.bmp", "images/skill_level9.bmp" }; /*the images in the choose mouse menu menu*/
char* choose_mouse_skills_menu_buttons_image_chosen[NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU + 9] = { "images/choose_mouse_skill_level_title.bmp", "images/skill_level5_chosen.bmp", "images/done_chosen.bmp", "images/back_chosen.bmp", "images/skill_level1_chosen.bmp", "images/skill_level2_chosen.bmp", "images/skill_level3_chosen.bmp", "images/skill_level4_chosen.bmp","images/skill_level5_chosen.bmp", "images/skill_level6_chosen.bmp", "images/skill_level7_chosen.bmp", "images/skill_level8_chosen.bmp", "images/skill_level9_chosen.bmp" };
int stateId_choose_mouse_skill_level[NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU] = { 4, 10, 5, 2 };//change in the end- 5 should be the game screen and -1 should be up and down arrows!!!!!!!!!!!/
// Hila change
void initialize_states(){
	states[0] = build_all_view(main_menu_buttons_image, main_menu_buttons_image_chosen, stateId_main_menu, 1, -1, NUMBER_BUTTONS_MAIN_MENU);
	states[1] = build_all_view(choose_your_cat_menu_buttons_image, choose_your_cat_menu_buttons_image_chosen, stateId_choose_your_cat_menu, 1, -1, NUMBER_BUTTONS_CHOOSE_CAT_MENU);
	states[2] = build_all_view(choose_your_mouse_menu_buttons_image, choose_your_mouse_menu_buttons_image_chosen, stateId_choose_your_mouse_menu, 1, -1, NUMBER_BUTTONS_CHOOSE_MOUSE_MENU);
	states[3] = build_all_view(choose_cat_skills_menu_buttons_image, choose_cat_skills_menu_buttons_image_chosen, stateId_choose_cat_skill_level, 1, 5, NUMBER_BUTTONS_CAT_SKILL_LEVEL_MENU);
	states[4] = build_all_view(choose_mouse_skills_menu_buttons_image, choose_mouse_skills_menu_buttons_image_chosen, stateId_choose_mouse_skill_level, 1, 5, NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU);

}



void handle_event(SDL_Event *ev, View* v)
{
	switch (ev->type)
	{
	case SDL_QUIT:
		quit_main_menu();
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
			if ((currentView->model->level != - 1) && (v->model->marked_button == 1))
				handale_up_level_button(v->screen->head->next,v);
			break;
		case SDLK_DOWN:
			if ((currentView->model->level != -1) && (v->model->marked_button == 1))
				handale_down_level_button(v->screen->head->next, v);
			break;
		}
	default:
		break;
	}
}
void enter_click(View* v){
	int markedButton = v->model->marked_button;
	Panel* current = v->screen->head->next;
	int i = 0;
	for (i = 0; i < markedButton; i++){
		current = current->next;
	}
	handale_click(current,0,0,v);
}

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
			current->componentProps.surface = SDL_LoadBMP(v->model->images[markedButton]);
			v->screen->head->next->next->componentProps.surface = SDL_LoadBMP(v->model->chosen_images[v->model->level+3]);
			v->model->marked_button = 1;
		}
		else
		{
			current->componentProps.surface = SDL_LoadBMP(v->model->images[markedButton]);
			v->screen->head->next->next->componentProps.surface = SDL_LoadBMP(v->model->chosen_images[1]);
			v->model->marked_button = 1;
		}
		
	}

	else //the standard move from one button to the next
	{
		if ((v->model->level != -1) && (markedButton == 1)) //if the skill-level button is the 'chosen'
		{
			current->componentProps.surface = SDL_LoadBMP(v->model->images[v->model->level + 3]);
			current->next->componentProps.surface = SDL_LoadBMP(v->model->chosen_images[markedButton + 1]);
			v->model->marked_button += 1;
		}
		else
		{
			current->componentProps.surface = SDL_LoadBMP(v->model->images[markedButton]);
			current->next->componentProps.surface = SDL_LoadBMP(v->model->chosen_images[markedButton + 1]);
			v->model->marked_button += 1;
		}
		
	}
	draw_screen("Cat&Mouse",v->screen);
}

void button_click(Uint16 x, Uint16 y,View* v)
{
	int markedButtonIndex = 0;
	int markedButton = v->model->marked_button;
	Panel *button = v->screen->head->next;
	Panel* current = v->screen->head->next;
	int level = v->model->level;
	while (button != NULL)
	{
		if (button->enabled == 1)
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
							//if ((level =!-1) && (markedButtonIndex == 1)){
							//	
							//	current->componentProps.surface = SDL_LoadBMP(v->model->images[markedButton + level + 1]); //update the button that was 'chosen' to regular
							//	//button->componentProps.surface = SDL_LoadBMP(v->model->chosen_images[markedButtonIndex++]); //update the button that was regular to 'chosen'
							//}
							//else
							//{
							//	current->componentProps.surface = SDL_LoadBMP(v->model->images[markedButton]); //update the button that was 'chosen' to regular
							//	button->componentProps.surface = SDL_LoadBMP(v->model->chosen_images[markedButtonIndex++]); //update the button that was regular to 'chosen'
							//}

							if (level != -1)
							{
								if ((markedButton == 1)&&(markedButtonIndex !=1))//the skill button was pressed
								{
									current->componentProps.surface = SDL_LoadBMP(v->model->images[markedButton + level + 2]); //update the button that was 'chosen' to regular
									button->componentProps.surface = SDL_LoadBMP(v->model->chosen_images[markedButtonIndex++]); //update the button that was regular to 'chosen'
								}
								else if ((markedButton!=1)&&(markedButtonIndex==1)){
									current->componentProps.surface = SDL_LoadBMP(v->model->images[markedButton]); //update the button that was 'chosen' to regular
									button->componentProps.surface = SDL_LoadBMP(v->model->chosen_images[level+3]); //update the button that was regular to 'chosen'
								}
							}
							else //the regulear screen
							{
								current->componentProps.surface = SDL_LoadBMP(v->model->images[markedButton]); //update the button that was 'chosen' to regular
								button->componentProps.surface = SDL_LoadBMP(v->model->chosen_images[markedButtonIndex++]); //update the button that was regular to 'chosen'
							}
							
						
							draw_screen("Cat&Mouse",v->screen);
							handale_click(button,x,y,v);

						}
				}
		}
		button = button->next;
		markedButtonIndex++;
	}
}

void quit_main_menu()
{
	quit = 1;
	//free_UI_Tree(currentWindow);
}

void handale_click(Panel* button, Uint16 x, Uint16 y,View* v)
{
	currentAnimalPlayer editedPlayer = MOUSE;


	switch(button->nextState){
	case 9: //in 'choose your mouse menu' human was chosen and then go to step 5 to the main game screen
		mouse = USER;
	case 5: //going to the main game
		if (cat == USER){
			catLevel = -1;
		}
		if (mouse == USER){
			mouseLevel = -1;
		}
		mainviewboard(cat,mouse,catLevel,mouseLevel);
		break;
	case 7: //quit was pressed
		quit_main_menu();
		break;
	case 2:
		cat = USER;
	case 8: // 'in choose your cat menu' human was chosen
		currentView = states[2];
		//currentStateIndex++;
		draw_screen("Cat&Mouse", currentView->screen);
		break;
	case 3: //'in choose your cat menu' machine was chosen
		cat = COMPUTER;
		currentView = states[button->nextState];
		//currentStateIndex++;
		draw_screen("Cat&Mouse", currentView->screen);
		break;
	case 4: //in 'choose your mouse menu' human was chosen
		mouse = COMPUTER;
		currentView = states[button->nextState];
		//currentStateIndex++;
		draw_screen("Cat&Mouse", currentView->screen);
		break;
	case 11: //level button was pressed from 'choose your cat skill level menu'
		editedPlayer = CAT;

	case 10: //level button was pressed for 'choose your mouse skill level menu'
		if (v->model->level!=-1)
		{
			if (x >= button->componentProps.dest_rect->x+147)
							if (x <= button->componentProps.dest_rect->x + button->componentProps.dest_rect->w)
							{
								if (y >= button->componentProps.dest_rect->y)
									if (y <= button->componentProps.dest_rect->y + button->componentProps.dest_rect->h -36)
									{

										handale_up_level_button(button,v);
									}
									else
									{
									if(y >= button->componentProps.dest_rect->y+26)
										if (y <= button->componentProps.dest_rect->y + button->componentProps.dest_rect->h)
									{
										handale_down_level_button(button,v);
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
		break;
	default:
	currentView = states[button->nextState];
	currentStateIndex++;
	draw_screen("Cat&Mouse",currentView->screen);
	break;
}
	}
}

void handale_up_level_button(Panel* button,View* v)
{
	if(v->model->level<9){
		v->model->level++;
		char* chosenImagePath = v->model->chosen_images [currentView->model->level +4-1];
		v->screen->head->next->next->componentProps.surface = SDL_LoadBMP(chosenImagePath);// the next chosen image from the array
		draw_screen("Cat&Mouse", v->screen);
}

}
void handale_down_level_button(Panel* button, View* v)
{
	if(v->model->level>1){
		v->model->level--;
			char* chosenImagePath = v->model->chosen_images [v->model->level +4-1];
			v->screen->head->next->next->componentProps.surface = SDL_LoadBMP(chosenImagePath);// the next chosen image from the array
			draw_screen("Cat&Mouse", v->screen);
	}

}

void mainviewboard(player cat, player mouse, int catLevel, int mouseLevel)
{

	//allBoards = SDL_SetVideoMode(800, 800, 0, 0);
	//SDL_Color color = { 255, 255, 255 };
	//SDL_FillRect(allBoards, 0, SDL_MapRGB(allBoards->format, color.r, color.g, color.b));
	/*viewBoard* view =  createViewBoard(NULL, NULL, NULL);
	showViewBoard(view);*/
	 createBoardController(EDIT, "hila", cat, mouse, catLevel);
	 showView();
}
