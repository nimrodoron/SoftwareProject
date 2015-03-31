CFLAGS=-Wall -g -std=c99 -pedantic-errors -lm

all: main

clean:
	-rm Gui controller.o main.o model.o view.o widgets.o ModelBoard.o ViewBoard.o ControllerBoard.o

main: controller.o main.o model.o view.o widgets.o ModelBoard.o ViewBoard.o ControllerBoard.o
	gcc  -o main controller.o main.o model.o view.o widgets.o ModelBoard.o ViewBoard.o ControllerBoard.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs` -lSDL_image

main.o: src/main/main.c src/controllers/controller.c src/models/model.c src/views/view.c src/infrastructure/gui/widgets.c src/controllers/ControllerBoard.c src/views/ViewBoard.c src/models/ModelBoard.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/main/main.c src/controllers/controller.c src/models/model.c src/views/view.c src/infrastructure/gui/widgets.c src/controllers/ControllerBoard.c src/views/ViewBoard.c src/models/ModelBoard.c `sdl-config --cflags`
	
widgets: widgets.o
	gcc  -o widgets widgets.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs` -lSDL_image

widgets.o: src/infrastructure/gui/widgets.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -src/infrastructure/gui/widgets.c `sdl-config --cflags`
	
model: model.o widgets.o
	gcc  -o model model.o widgets.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs` -lSDL_image

model.o: src/infrastructure/gui/widgets.c src/models/model.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/infrastructure/gui/widgets.c src/models/model.c `sdl-config --cflags`
	
ModelBoard: ModelBoard.o	
	gcc  -o ModelBoard ModelBoard.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs` -lSDL_image
	
ModelBoard.o: src/models/ModelBoard.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/models/ModelBoard.c `sdl-config --cflags`
	
view: view.o model.o widgets.o
	gcc  -o view view.o model.o widgets.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs` -lSDL_image

view.o: src/views/view.c src/infrastructure/gui/widgets.c src/models/model.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/views/view.c src/infrastructure/gui/widgets.c src/models/model.c `sdl-config --cflags`
	
ViewBoard: ViewBoard.o ModelBoard.o widgets.o
	gcc  -o ViewBoard ViewBoard.o ModelBoard.o widgets.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs` -lSDL_image

ViewBoard.o: src/views/ViewBoard.c src/infrastructure/gui/widgets.c src/models/ModelBoard.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/views/ViewBoard.c src/infrastructure/gui/widgets.c src/models/ModelBoard.c `sdl-config --cflags`
	
controller: controller.o view.o model.o widgets.o
	gcc  -o controller controller.o view.o model.o widgets.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs` -lSDL_image

controller.o: src/controllers/controller.c src/views/view.c src/infrastructure/gui/widgets.c src/models/model.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/controllers/controller.c src/views/view.c src/infrastructure/gui/widgets.c src/models/model.c `sdl-config --cflags`	 
	
ControllerBoard: ControllerBoard.o ModelBoard.o ViewBoard.o widgets.o
	gcc  -o ControllerBoard ControllerBoard.o ViewBoard.o ModelBoard.o widgets.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs` -lSDL_image	

ControllerBoard.o: src/controllers/ControllerBoard.c src/views/ViewBoard.c src/infrastructure/gui/widgets.c src/models/ModelBoard.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/controllers/ControllerBoard.c src/views/ViewBoard.c src/infrastructure/gui/widgets.c src/models/ModelBoard.c `sdl-config --cflags`