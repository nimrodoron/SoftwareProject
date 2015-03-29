#include "main.h"
#include "ControllerBoard.h"

typedef struct board{
	Screen* topPanel;
	Screen* sideBar;
	//Screen* gridArea;
}Board;

SDL_Surface* allBoards;

Board* buildBord();
Board* create_boardView(Screen* topPanel, Screen* sideBar);
Screen* create_topPanel();
Screen* create_sideBar();
void* create_gridArea();
void apply_surfaceBoard(int x, int y, SDL_Surface* source, SDL_Surface* destination);

void mainviewboard();
