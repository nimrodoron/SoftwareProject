#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL_image.h>
#include <stdbool.h>
#include "../views/view.h"
#include "../models/ModelBoard.h"
#include "../controllers/ControllerBoard.h"
#include "../services/WorldsManager.h"



View* currentView;

playerType cat;
playerType mouse;
int catLevel;
int mouseLevel;
int worldNumber;

#define NUMBER_OF_WORLDS 6
char* worlds[NUMBER_OF_WORLDS];

/*for main menu*/
#define  NUMBER_BUTTONS_MAIN_MENU  6
extern char* main_menu_buttons_image[NUMBER_BUTTONS_MAIN_MENU];
extern char* main_menu_buttons_image_chosen[NUMBER_BUTTONS_MAIN_MENU];
extern int stateId_main_menu[NUMBER_BUTTONS_MAIN_MENU];

/*for choose cat menu*/
#define NUMBER_BUTTONS_CHOOSE_CAT_MENU 4
extern char* choose_your_cat_menu_buttons_image[NUMBER_BUTTONS_CHOOSE_CAT_MENU]; /*the images in the choose cat menu menu*/
extern char* choose_your_cat_menu_buttons_image_chosen[NUMBER_BUTTONS_CHOOSE_CAT_MENU];
extern int stateId_choose_your_cat_menu[NUMBER_BUTTONS_CHOOSE_CAT_MENU];

/*for choose mouse menu*/
#define NUMBER_BUTTONS_CHOOSE_MOUSE_MENU 4
extern char* choose_your_mouse_menu_buttons_image[NUMBER_BUTTONS_CHOOSE_MOUSE_MENU]; /*the images in the choose mouse menu menu*/
extern char* choose_your_mouse_menu_buttons_image_chosen[NUMBER_BUTTONS_CHOOSE_MOUSE_MENU];
extern int stateId_choose_your_mouse_menu[NUMBER_BUTTONS_CHOOSE_MOUSE_MENU];

/*for choose cat skill level menu*/
#define NUMBER_BUTTONS_CAT_SKILL_LEVEL_MENU 4
extern char* choose_cat_skills_menu_buttons_image[NUMBER_BUTTONS_CAT_SKILL_LEVEL_MENU+9]; /*the images in the choose mouse menu menu*/
extern char* choose_cat_skills_menu_buttons_image_chosen[NUMBER_BUTTONS_CAT_SKILL_LEVEL_MENU+9];
extern int stateId_choose_cat_skill_level[NUMBER_BUTTONS_CAT_SKILL_LEVEL_MENU];

/*for choose mouse skill level menu*/
#define NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU 4
char* choose_mouse_skills_menu_buttons_image[NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU+9];
extern char* choose_mouse_skills_menu_buttons_image_chosen[NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU+9];
extern int stateId_choose_mouse_skill_level[NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU];

/*for load game menu*/
#define NUMBER_BUTTONS_LOAD_GAME_MENU 4
char* load_game_menu_buttons_image[NUMBER_BUTTONS_LOAD_GAME_MENU + 5];
extern char* load_game_menu_buttons_image_chosen[NUMBER_BUTTONS_LOAD_GAME_MENU + 5];
extern int stateId_load_game[NUMBER_BUTTONS_LOAD_GAME_MENU];

/*for save game menu*/
char* save_game_menu_buttons_image[NUMBER_BUTTONS_LOAD_GAME_MENU + 5];
extern char* save_game_menu_buttons_image_chosen[NUMBER_BUTTONS_LOAD_GAME_MENU + 5];
extern int stateId_save_game[NUMBER_BUTTONS_LOAD_GAME_MENU];

/*for edit game menu*/
char* edit_game_menu_buttons_image[NUMBER_BUTTONS_LOAD_GAME_MENU + 5];
extern char* edit_game_menu_buttons_image_chosen[NUMBER_BUTTONS_LOAD_GAME_MENU + 5];
extern int stateId_edit_game[NUMBER_BUTTONS_LOAD_GAME_MENU];

 int quit;


#define NUMBER_MENUES 8
View* states[NUMBER_MENUES];

void while_handle_event();
void initialize_states();
void handle_event(SDL_Event *ev, View* v);
void tab_click(View* v);
void button_click(Uint16 x, Uint16 y, View* v);
void enter_click(View* v);
void quit_main_menu();
void handale_click(Panel* button, Uint16 x, Uint16 y, View* v);
void handaleUpDoawArrowas(Panel* button, Uint16 x, Uint16 y, View* v, playerAnimal editedPlayer);
void handale_down_level_button(Panel* button, View* v);
void handale_up_level_button(Panel* button, View* v);
void mainviewboard(playerType catType, playerType mouseType, int catLevel, int mouseLevel, mode mod, int worldIndex);
void reconfigureMouseFunction(int level, playerType type, modelBoard* model);
void reconfigureCatFunction(int level, playerType type, modelBoard* model);
void GoToMainMenu();
void save(int worldsIndex);
void save_world(modelBoard* model);
void freeStates();


#endif
