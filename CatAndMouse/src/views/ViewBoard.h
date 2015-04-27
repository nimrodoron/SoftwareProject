#ifndef VIEWBOARD_H_
#define VIEWBOARD_H_

#include <stdlib.h>
#include "../models/ModelBoard.h"
#include "../infrastructure/general/general.h"
#include "../infrastructure/gui/widgets.h"
#include "../main/ListUtils.h"


#define NUMBER_BUTTONS_TOP_PANEL  6
#define NUMBER_BUTTONS_SIDE_BAR 5
#define NUMBER_BUTTONS_TOP_PANEL_CREATE_GAME 4
#define NUMBER_WORLD_TITELS 6

#define TOP_PANEL_WIDGET_NAME "topPanelWidget"
#define TURNS_WIDGET_NAME "turnsWidget"
#define THIRD_DIGIT_WIDGET_NAME "thirdDigitWidget"
#define SECOND_DIGIT_WIDGET_NAME "secondDigitWidget"
#define FIRST_DIGIT_WIDGET_NAME "firstDigitWidget"
#define BRACE_CLOSE_WIDGET_NAME "braceCloseWidget"
#define FREE_TEXT_WIDGET_NAME	"freeTextWidget"
#define PAUSE_BUTTON_NAME		"pause"


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
	COMPUTER_MOVE
}viewBoardEvents;

typedef struct viewBoard{
	ListRef GameTopPanel;
	widget* WinnerTopPanel;
	Screen* topPanel;
	Screen* sideBar;
	Screen* gridArea;
	void (*HandleSystemEvent) (viewBoardEvents event, int x, int y);
	modelBoard* model;
	pos markedSquare;
	int quitView;
}viewBoard;

SDL_Surface* allBoards;



result createViewBoard(viewBoard** view, void (*HandleSystemEvent) (viewBoardEvents event, int x, int y),
					   modelBoard* model,int worldsIndex);
result showViewBoard(viewBoard* view, modelBoard* model);
result freeViewBoard(viewBoard* view);
result refreshViewBoard(viewBoard* view);
result refreshTopPanel(viewBoard* view);
result refreshSidePanel(viewBoard* view);
viewBoard* buildBord();
viewBoard* create_boardView(Screen* topPanel, Screen* sideBar);
void create_topPanel(viewBoard* view);
void free_top_pnael(viewBoard* view);
void show_top_panel(viewBoard* view);
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
void printWinnerTopPaenl(playerAnimal winner, viewBoard* view);
void pauseWasPressed(viewBoard* view);
void printMessages(char* message);
void createMessage(char* message);
void restartGame();

#endif
