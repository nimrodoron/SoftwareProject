#include "view.h"

View* currentView;
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
extern char* choose_cat_skills_menu_buttons_image[NUMBER_BUTTONS_CAT_SKILL_LEVEL_MENU]; /*the images in the choose mouse menu menu*/
extern char* choose_cat_skills_menu_buttons_image_chosen[NUMBER_BUTTONS_CAT_SKILL_LEVEL_MENU];
extern int stateId_choose_cat_skill_level[NUMBER_BUTTONS_CAT_SKILL_LEVEL_MENU];

#define NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU 4
char* choose_mouse_skills_menu_buttons_image[NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU+8];
extern char* choose_mouse_skills_menu_buttons_image_chosen[NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU];
extern int stateId_choose_mouse_skill_level[NUMBER_BUTTONS_MOUSE_SKILL_LEVEL_MENU];


 int quit;
//char* currentState;
#define NUMBER_MENUES 4
View* states[NUMBER_MENUES];
/*supposed to be {main_menu, choose your cat, choose your mouse, choose cat skill level, load game, create game, edit game, quit}*/



void initialize_states();
void handle_event(SDL_Event *ev, View* v);
void tab_click(View* v);
void button_click(Uint16 x, Uint16 y, View* v);
void enter_click(View* v);
//void init_arrays();
