#ifndef WIDGETS_H_
#define WIDGETS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_HEIGHT 578
#define SCREEN_WIDTH 350
#define GAMEGAP 30 /*the gap between the buttons in the game state */
#define  offsetX 0 /*the offset of the window?*/
#define  offsetY 0


/*for the menu buttons*/
extern int BUTTON_WIDTH;
extern int  BUTTON_HEIGHT;
extern int MENUGAP;/*the gap between the buttons in the menu state */
extern int button_offsetX; /*the offset of the button*/
extern int button_offsetY;

/*component's type*/
typedef enum  ComponentType {
	BUTTON,
	IMAGE,
	PANEL,
	TEXT
} ComponentType;

/*propeties for a component and for a window*/
typedef struct Properties{
	SDL_Surface*            surface;		// if type: BUTTON or IMAGE, image surface to blit
	// if type: TEXT, text surface to blit
	// if type: WINDOW, window sdl surface to blit on

	SDL_Rect*               surface_rect;	// which part of the surface to blit (if surface is present)

	SDL_Rect*               dest_rect;		// where to draw the control to. if type is PANEL or WINDOW, contains height and width
	SDL_Color               background_color;		// if type PANEL/WINDOW, what is the background color
} properties;


typedef struct panel
{
	ComponentType				type;			// possible types: BUTTON, IMAGE, TEXT, PANEL
	int 						nextState;
	struct panel*           next;      // next control in list, that this control is contained in (NULL if last in list)
	struct panel*           prev;      // previous control in list, that this control is contained in(NULL if first in list)

	//void(*on_click)(struct Component* caller);  // on_click callback function, method receives the button control that was clicked
	// (only relevant for controls of type BUTTON)
	properties				componentProps;
	bool                   enabled;		// whether or not the button is enabled for clicking
	int						size;
	//int						markedButton;
	// can be also used to disable a panel (all controls contained will be not clickable)

}Panel;


typedef struct Screen
{
	Panel* head;
	SDL_Surface* screen;
}Screen;





extern int isError;
SDL_Event event;

Screen* create_screen();
Panel* create_panel(int width, int height, int x, int y, char* path, ComponentType type, int stateIndex, Screen* window, int number_buttons);
Screen* build_main_menu(int number_buttons, char* title, char** imagesArr, char** imagesArrChosen, int* stateArr, int marked_button);
int calc_height(int size, int height, int gap);
int calc_width(int width);
void add_child(Panel* item, Screen* window);

#endif
