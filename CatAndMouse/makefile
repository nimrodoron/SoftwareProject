CFLAGS=-Wall -g -std=c99 -pedantic-errors -lm

all: main

clean:
	-rm Gui controller.o main.o model.o view.o widgets.o

main: controller.o main.o model.o view.o widgets.o
	gcc  -o main controller.o main.o model.o view.o widgets.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs` -lSDL_image

main.o: src/main/main.c src/controllers/controller.c src/models/model.c src/views/view.c src/infrastructure/gui/widgets.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/main/main.c src/controllers/controller.c src/models/model.c src/views/view.c src/infrastructure/gui/widgets.c `sdl-config --cflags`
	
widgets: widgets.o
	gcc  -o widgets widgets.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs` -lSDL_image

widgets.o: src/infrastructure/gui/widgets.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -src/infrastructure/gui/widgets.c `sdl-config --cflags`
	
model: model.o widgets.o
	gcc  -o model model.o widgets.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs` -lSDL_image

model.o: src/infrastructure/gui/widgets.c src/models/model.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/infrastructure/gui/widgets.c src/models/model.c `sdl-config --cflags`
	
view: view.o model.o widgets.o
	gcc  -o view view.o model.o widgets.o -lm -std=c99 src/gui/view.c src/gui/widgets.c src/model/model.c `sdl-config --cflags` -lSDL_image
	
controller.o: src/controllers/controller.c src/views/view.c src/infrastructure/gui/widgets.c src/models/model.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm src/controllers/controller.c src/views/view.c src/infrastructure/gui/widgets.c src/models/model.c `sdl-config --cflags`
	
controller: controller.o view.o model.o widgets.o
	gcc  -o controller controller.o view.o model.o widgets.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs` -lSDL_image
