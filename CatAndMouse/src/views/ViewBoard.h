#include <stdlib.h>
#include "../models/ModelBoard.h"
#include "../infrastructure/general/general.h"
#include "../infrastructure/gui/widgets.h"


#define NUMBER_BUTTONS_TOP_PANEL  6
#define NUMBER_BUTTONS_SIDE_BAR 5
#define NUMBER_BUTTONS_TOP_PANEL_CREATE_GAME 4
#define NUMBER_WORLD_TITELS 6


// all the possible events in the view
typedef enum {
	EXIT,
	RECONFIGURE_MOUSE,
	RECONFIGURE_CAT,
	RESTART_GAME,
	GO_TO_MAIN_MENU,
	SPACE,
	SAVE_WORLD,
	PLACE_MOUSE,
	PLACE_CAT,
	PLACE_CHEESE,
	PLACE_WALL,
	PLACE_EMPTY_SPACE,
	PLAYER_MOVED_TO,
}viewBoardEvents;

typedef struct viewBoard{
	Screen* topPanel;
	Screen* sideBar;
	Screen* gridArea;
	void (*HandleSystemEvent) (viewBoardEvents event, int x, int y);
	modelBoard* model;
	pos markedSquare;
}viewBoard;

SDL_Surface* allBoards;

// Those function are called from the controller

// Create new viewBoard (malloc)
// update the fields of the struct and return result
// view parameter is NULL
result createViewBoard(viewBoard** view, void (*HandleSystemEvent) (viewBoardEvents event, int x, int y),
					   modelBoard* model,int worldsIndex);

// This function show the view according to the model
// and than wait for SDL events than pass them to the controller
// by calling the function HandleSystemEvent
result showViewBoard(viewBoard* view, modelBoard* model);

// This function is called after Exit event from the controller
// also the loop waiting for events should stop
// thus function free the memory of the view
result freeViewBoard(viewBoard* view);

result refreshViewBoard(viewBoard* view);


// Those functions are for local use of the view

// Use any function you need to draw the view handle and
// translate SDL events to view events
viewBoard* buildBord();
viewBoard* create_boardView(Screen* topPanel, Screen* sideBar);
Screen* create_topPanel();
void show_top_panel(Screen* scr);
void show_side_bar(Screen* scr);
void show_grid_area(Screen* scr);
Screen* create_sideBar(char** imagesArr);
Screen* create_gridArea(modelBoard* model, viewBoard* v);
result CreateNewWorldBoard(viewBoard** view, void(*HandleSystemEvent) (viewBoardEvents event, int x, int y), modelBoard* model);
Screen* CreateWorld_topPanel(int worldsIndex);
void show_CreateWorld_top_panel(Screen* scr);
void apply_surfaceBoard(int x, int y, SDL_Surface* source, SDL_Surface* destination);
void handle_gui_event(SDL_Event *ev, viewBoard* v, modelBoard* model);
void mainviewboard();
void button_click_side_panel(Uint16 x, Uint16 y, viewBoard* v);
void button_click_side_panel_new_world(Uint16 x, Uint16 y, viewBoard* v);
void button_click_top_panel(Uint16 x, Uint16 y, viewBoard* v);
void button_click_top_panel_new_world(Uint16 x, Uint16 y, viewBoard* v);
void button_click_game_board(Uint16 x, Uint16 y, viewBoard* v);
void button_click_game_board_game(Uint16 x, Uint16 y, viewBoard* v);

