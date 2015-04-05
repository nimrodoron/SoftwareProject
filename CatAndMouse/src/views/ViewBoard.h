#include <stdlib.h>
#include "../models/ModelBoard.h"
#include "../infrastructure/general/general.h"
#include "../infrastructure/gui/widgets.h"


#define  NUMBER_BUTTONS_TOP_PANEL  6
#define NUMBER_BUTTONS_SIDE_BAR 5


// all the possible events in the view
typedef enum {
	EXIT,
	RECONFIGURE_MOUSE,
	RECONFIGURE_CAT,
	RESTART_GAME,
	GO_TO_MAIN_MENU
}viewBoardEvents;

typedef struct viewBoard{
	Screen* topPanel;
	Screen* sideBar;
	Screen* gridArea;
	void (*HandleSystemEvent) (viewBoardEvents event, int x, int y);
	modelBoard* model;
}viewBoard;

SDL_Surface* allBoards;

// Those function are called from the controller

// Create new viewBoard (malloc)
// update the fields of the struct and return result
// view parameter is NULL
result createViewBoard(viewBoard** view, void (*HandleSystemEvent) (viewBoardEvents event, int x, int y),
					   modelBoard* model);

// This function show the view according to the model
// and than wait for SDL events than pass them to the controller
// by calling the function HandleSystemEvent
result showViewBoard(viewBoard* view);

// This function is called after Exit event from the controller
// also the loop waiting for events should stop
// thus function free the memory of the view
result freeViewBoard(viewBoard* view);


// Those functions are for local use of the view

// Use any function you need to draw the view handle and
// translate SDL events to view events
viewBoard* buildBord();
viewBoard* create_boardView(Screen* topPanel, Screen* sideBar);
Screen* create_topPanel();
void show_top_panel(Screen* scr);
void show_side_bar(Screen* scr);
void show_grid_area(Screen* scr);
Screen* create_sideBar();
Screen* create_gridArea();
void apply_surfaceBoard(int x, int y, SDL_Surface* source, SDL_Surface* destination);
void handle_gui_event(SDL_Event *ev, viewBoard* v);
void mainviewboard();
void button_click_side_panel(Uint16 x, Uint16 y, viewBoard* v);