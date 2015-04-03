#include <stdlib.h>
#include "../models/ModelBoard.h"
#include "../infrastructure/general/general.h"
#include "../infrastructure/gui/widgets.h"


#define  NUMBER_BUTTONS_TOP_PANEL  6
#define NUMBER_BUTTONS_SIDE_BAR 5

//extern char* displayed_top_panel_images[NUMBER_BUTTONS_TOP_PANEL];
//extern char* side_bar_images[NUMBER_BUTTONS_SIDE_BAR];

// all the possible events in the view
typedef enum {
	EXIT
}viewBoardEvents;

typedef struct viewBoard{
	Screen* topPanel;
	Screen* sideBar;
	//Screen* gridArea;
	void (*HandleSystemEvent) (viewBoardEvents event, int x, int y);
	modelBoard* model;
}viewBoard;

SDL_Surface* allBoards;

// Those function are called from the controller

// Create new viewBoard (malloc)
// update the fields of the struct and return result
// view parameter is NULL
result createViewBoard(viewBoard* view, void (*HandleSystemEvent) (viewBoardEvents event, int x, int y),
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
Screen* create_sideBar();
void* create_gridArea();
void apply_surfaceBoard(int x, int y, SDL_Surface* source, SDL_Surface* destination);

void mainviewboard();