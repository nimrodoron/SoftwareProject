#ifndef WIDGETS_H_
#define WIDGETS_H_


#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>

extern int isError;
SDL_Event event;


/*the offset of the window*/
#define  offsetX 0 
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
	PANEL
} ComponentType;

/*propeties for a component and for a window*/
typedef struct Properties{
	SDL_Surface*            surface;		// if type: BUTTON or IMAGE, image surface to blit
	SDL_Rect*               dest_rect;		// where to draw the control to. if type is PANEL or WINDOW, contains height and width
	SDL_Color               background_color;		// if type PANEL/WINDOW, what is the background color
} properties;


typedef struct panel
{
	ComponentType				type;			// possible types: BUTTON, IMAGE, PANEL
	int 						nextState;
	struct panel*           next;      // next control in list, that this control is contained in (NULL if last in list)
	struct panel*           prev;      // previous control in list, that this control is contained in(NULL if first in list)
	properties				componentProps;
	bool                   enabled;		// whether or not the button is enabled for clicking
	int						size;
}Panel;


typedef struct Screen
{
	Panel* head;
	SDL_Surface* screen;
}Screen;

typedef struct widget {
	SDL_Surface*			widget_surface;
	SDL_Rect*               dest_rect;
	char*					name;
	ComponentType			widgetType;
	int						x;
	int						y;
	int						height;
	int						width;
}widget;


Screen* create_screen();
Panel* create_panel(int width, int height, int x, int y, char* path, ComponentType type, int stateIndex, Screen* window, int number_buttons);
Screen* build_main_menu(int number_buttons, char* title, char** imagesArr, char** imagesArrChosen, int* stateArr, int marked_button);
void add_child(Panel* item, Screen* window);
void update_panel_picture(Panel* item, char* path);
widget* createNewWidget(ComponentType widgetType, char* name);
bool checkClick(widget* wg, int x, int y);
void drawWidget(widget* wg,  SDL_Surface* surface);
void freeWidget(void* wg);
void freeScreen(Screen* screen);
void freePanel(Panel* panel);
void setWidgetImage(widget* wg, char* path);
void setImage(Panel* panel, char* path);

#endif
