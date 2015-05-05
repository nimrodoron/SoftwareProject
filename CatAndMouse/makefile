CFLAGS=-Wall -g -std=c99 -pedantic-errors -lm

all: CatAndMouse MiniMaxDemo

clean:
	-rm CatAndMouse MiniMaxDemo ListUtilsDemo controller.o main.o model.o view.o widgets.o ModelBoard.o ViewBoard.o ControllerBoard.o ListUtils.o MiniMax.o MiniMaxDemo.o CatAndMouseMiniMax.o WorldsManager.o

CatAndMouse: controller.o CatAndMouse.o model.o view.o widgets.o ModelBoard.o ViewBoard.o ControllerBoard.o WorldsManager.o ListUtils.o MiniMax.o CatAndMouseMiniMax.o
	gcc  -o CatAndMouse controller.o CatAndMouse.o model.o view.o widgets.o ModelBoard.o ViewBoard.o ControllerBoard.o WorldsManager.o ListUtils.o MiniMax.o CatAndMouseMiniMax.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs` -lSDL_image

MiniMaxDemo: MiniMaxDemo.o MiniMax.o ListUtils.o
	gcc  -o MiniMaxDemo MiniMaxDemo.o MiniMax.o ListUtils.o  -lm -std=c99 -pedantic-errors -g `sdl-config --libs`
	
ListUtilsDemo: ListUtilsDemo.o ListUtils.o
	gcc  -o ListUtilsDemo.o ListUtils.o  -lm -std=c99 -pedantic-errors -g `sdl-config --libs`
	
CatAndMouse.o: src/main/CatAndMouse.c src/controllers/controller.c src/models/model.c src/views/view.c src/infrastructure/gui/widgets.c src/controllers/ControllerBoard.c src/views/ViewBoard.c src/models/ModelBoard.c src/services/WorldsManager.c src/infrastructure/general/ListUtils.c  src/infrastructure/minimax/MiniMax.c src/minimax/CatAndMouseMiniMax.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/main/CatAndMouse.c src/controllers/controller.c src/models/model.c src/views/view.c src/infrastructure/gui/widgets.c src/controllers/ControllerBoard.c src/views/ViewBoard.c src/models/ModelBoard.c src/services/WorldsManager.c  src/infrastructure/general/ListUtils.c src/infrastructure/minimax/MiniMax.c src/minimax/CatAndMouseMiniMax.c `sdl-config --cflags`
	
MiniMaxDemo.o: src/main/MiniMaxDemo.c src/infrastructure/minimax/MiniMax.c src/infrastructure/general/ListUtils.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/main/MiniMaxDemo.c src/infrastructure/minimax/MiniMax.c src/infrastructure/general/ListUtils.c

widgets.o: src/infrastructure/gui/widgets.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -src/infrastructure/gui/widgets.c `sdl-config --cflags`
	
model.o: src/infrastructure/gui/widgets.c src/models/model.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/infrastructure/gui/widgets.c src/models/model.c `sdl-config --cflags`
	
ModelBoard.o: src/models/ModelBoard.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/models/ModelBoard.c `sdl-config --cflags`

view.o: src/views/view.c src/infrastructure/gui/widgets.c src/models/model.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/views/view.c src/infrastructure/gui/widgets.c src/models/model.c `sdl-config --cflags`

ViewBoard.o: src/views/ViewBoard.c src/infrastructure/gui/widgets.c src/models/ModelBoard.c src/infrastructure/general/ListUtils.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/views/ViewBoard.c src/infrastructure/gui/widgets.c src/models/ModelBoard.c src/infrastructure/general/ListUtils.c `sdl-config --cflags`

controller.o: src/controllers/controller.c src/views/view.c src/infrastructure/gui/widgets.c src/models/model.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/controllers/controller.c src/views/view.c src/infrastructure/gui/widgets.c src/models/model.c `sdl-config --cflags`	 

ControllerBoard.o: src/controllers/ControllerBoard.c src/views/ViewBoard.c src/infrastructure/gui/widgets.c src/models/ModelBoard.c src/services/WorldsManager.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/controllers/ControllerBoard.c src/views/ViewBoard.c src/infrastructure/gui/widgets.c src/models/ModelBoard.c src/services/WorldsManager.c `sdl-config --cflags`

WorldsManager.o: src/services/WorldsManager.c src/models/ModelBoard.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm  src/services/WorldsManager.c src/models/ModelBoard.c `sdl-config --cflags`

ListUtilsDemo.o: src/infrastructure/general/ListUtils.c src/main/ListUtilsDemo.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/infrastructure/general/ListUtils.c src/main/ListUtilsDemo.c

ListUtils.o: src/infrastructure/general/ListUtils.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/infrastructure/general/ListUtils.c
	
MiniMax.o: src/infrastructure/minimax/MiniMax.c src/infrastructure/general/ListUtils.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/infrastructure/minimax/MiniMax.c src/infrastructure/general/ListUtils.c
	
CatAndMouseMiniMax.o: src/minimax/CatAndMouseMiniMax.c src/models/ModelBoard.c src/infrastructure/minimax/MiniMax.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/minimax/CatAndMouseMiniMax.c src/models/ModelBoard.c src/infrastructure/minimax/MiniMax.c