CFLAGS=-Wall -g -std=c99 -pedantic-errors -lm

all: main

clean:
	-rm Gui controller.o main.o model.o view.o widgets.o

main: controller.o main.o model.o view.o widgets.o
	gcc  -o main controller.o main.o model.o view.o widgets.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs` -lSDL_image

main.o: src/main/main.c src/gui/controller.c src/gui/model.c src/gui/view.c src/gui/widgets.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/main/main.c src/gui/controller.c src/gui/model.c src/gui/view.c src/gui/widgets.c `sdl-config --cflags`
	
widgets: widgets.o
	gcc  -o widgets widgets.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs` -lSDL_image

widgets.o: src/gui/widgets.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -src/gui/lm widgets.c `sdl-config --cflags`
	
model: model.o widgets.o
	gcc  -o model model.o widgets.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs` -lSDL_image

model.o: src/gui/widgets.c src/gui/model.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/gui/widgets.c src/gui/model.c `sdl-config --cflags`
	
view: view.o model.o widgets.o
	gcc  -o view view.o model.o widgets.o -lm -std=c99 src/gui/view.c src/gui/widgets.c src/gui/model.c `sdl-config --cflags` -lSDL_image
	
controller.o: src/gui/controller.c src/gui/view.c src/gui/widgets.c src/gui/model.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/gui/controller.c src/gui/view.c src/gui/widgets.c src/gui/model.c `sdl-config --cflags`
	

controller: controller.o view.o model.o widgets.o
	gcc  -o controller controller.o view.o model.o widgets.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs` -lSDL_image
