#include "controller.h"
#include <SDL_image.h>
#include <stdbool.h>

/*for main menu*/

char* main_menu_buttons_image[NUMBER_BUTTONS_MAIN_MENU] = { "images/cat_mouse_title.png", "images/new_game.png", "images/load_game.png", "images/create_game.png", "images/edit_game.png", "images/quit.png" }; /*the images in the main menu*/
char* main_menu_buttons_image_chosen[NUMBER_BUTTONS_MAIN_MENU] = { "images/cat_mouse_title.png", "images/new_game_chosen.png", "images/load_game_chosen.png", "images/create_game_chosen.png", "images/edit_game_chosen.png", "images/quit_chosen.png" };
int stateId_main_menu[NUMBER_BUTTONS_MAIN_MENU] = { 0, 1, 4, 5, 6, 7 };

/*for choose cat menu*/
char* choose_your_cat_menu_buttons_image[NUMBER_BUTTONS_CHOOSE_CAT_MENU] = { "images/choose_your_cat_title.png", "images/human.png", "images/machine.png", "images/back.png" }; /*the images in the choose cat menu menu*/
char* choose_your_cat_menu_buttons_image_chosen[NUMBER_BUTTONS_CHOOSE_CAT_MENU] = { "images/choose_your_cat_title.png", "images/human_chosen.png", "images/machine_chosen.png", "images/back_chosen.png" };
int stateId_choose_your_cat_menu[NUMBER_BUTTONS_CHOOSE_CAT_MENU] = {1, 2, 3, 0};

/*for choose mouse menu*/
char* choose_your_mouse_menu_buttons_image[NUMBER_BUTTONS_CHOOSE_MOUSE_MENU] = { "images/choose_your_mouse_title.png", "images/human.png", "images/machine.png", "images/back.png" }; /*the images in the choose mouse menu menu*/
char* choose_your_mouse_menu_buttons_image_chosen[NUMBER_BUTTONS_CHOOSE_MOUSE_MENU] = { "images/choose_your_mouse_title.png", "images/human_chosen.png", "images/machine_chosen.png", "images/back_chosen.png" };
int stateId_choose_your_mouse_menu[NUMBER_BUTTONS_CHOOSE_MOUSE_MENU] = {2, 5, 4, 1 };//change in the end- 5 should be the game screen!!!!!!!!!!!/

/*for choose cat skill level menu*/
char* choose_cat_skills_menu_buttons_image[NUMBER_BUTTONS_CAT_SKILL_LEVEL_MENU] = { "images/choose_cat_skill_level_title.png", "images/skill_level5.png", "images/done.png", "images/back.png" }; /*the images in the choose mouse menu menu*/
char* choose_cat_skills_menu_buttons_image_chosen[NUMBER_BUTTONS_CAT_SKILL_LEVEL_MENU] = { "images/choose_cat_skill_level_title.png", "images/skill_level5_chosen.png", "images/done_chosen.png", "images/back_chosen.png" };
int stateId_choose_cat_skill_level[NUMBER_BUTTONS_CAT_SKILL_LEVEL_MENU] = { 3, 0, 5, 1 };//change in the end- 5 should be the game screen and -1 should be up and down arrows!!!!!!!!!!!/
// Hila change

/*for choose mouse skill level menu*/
char* choose_mouse_skills_menu_buttons_image[NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU+8] = { "images/choose_mouse_skill_level_title.png", "images/skill_level5.png", "images/done.png", "images/back.png","images/skill_level1.png","images/skill_level2.png","images/skill_level3.png","images/skill_level4.png","images/skill_level6.png","images/skill_level7.png","images/skill_level8.png","images/skill_level9.png" }; /*the images in the choose mouse menu menu*/
char* choose_mouse_skills_menu_buttons_image_chosen[NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU] = { "images/choose_mouse_skill_level_title.png", "images/skill_level5_chosen.png", "images/done_chosen.png", "images/back_chosen.png" };
int stateId_choose_mouse_skill_level[NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU] = { 4, 0, 5, 2 };//change in the end- 5 should be the game screen and -1 should be up and down arrows!!!!!!!!!!!/
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
		quit = 1;
		//free_UI_Tree(currentWindow);
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
	currentView = states[current->nextState];
	draw_screen("Cat&Mouse", currentView->screen);
}

void tab_click(View* v)
{
	int markedButton = v->model->marked_button;
	Panel* current = v->screen->head->next;
	int i = 0;
	for (i = 0; i < markedButton; i++){
		current = current->next;
	}
	if (markedButton == v->screen->head->size-1){
		current->componentProps.surface = IMG_Load(v->model->images[markedButton]);
		v->screen->head->next->next->componentProps.surface = IMG_Load(v->model->chosen_images[1]);
		v->model->marked_button = 1;
	}
	else {
		current->componentProps.surface = IMG_Load(v->model->images[markedButton]);
		current->next->componentProps.surface = IMG_Load(v->model->chosen_images[markedButton + 1]);
		v->model->marked_button += 1;
	}
	draw_screen("Cat&Mouse",v->screen);
}

void button_click(Uint16 x, Uint16 y,View* v)
{
	int markedButtonIndex = 0;
	int markedButton = currentView->model->marked_button;
	Panel *button = v->screen->head->next;
	Panel* current = v->screen->head->next;

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
							currentView->model->marked_button = markedButtonIndex; 
							for (int i = 0; i < markedButton; i++){
								current = current->next;
							}
							current->componentProps.surface = IMG_Load(v->model->images[markedButton]);
							button->componentProps.surface = IMG_Load(v->model->chosen_images[markedButtonIndex++]);
							draw_screen("Cat&Mouse", currentView->screen);
							currentView = states[button->nextState];
							draw_screen("Cat&Mouse",currentView->screen);
							break;
						}
				}
		}
		button = button->next;
		markedButtonIndex++;
	}
}
