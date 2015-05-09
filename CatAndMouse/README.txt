##########################################################################################

README file for the CatAndMouse project (2015)
Partners: Nimrod Oron & Hila Israeli

##########################################################################################

Our design choices:
	We choosed to implement the system using MVC design.

##########################################################################################

List of modules:
	main - CatAndMouse.c entry for the progrm.
	controllers - Controller for all the menus. ControllerBoard for the game view.
	views - view for all the menus and ViewBoard (Singelton) for the game screen.
	models - modelBoard is the main model fo the game.
	services - worldsManager which responsible to load and save games from files.

##########################################################################################

Utility evaluation function:
	high level description - 
							 If it is mouse we find the shortest path from the mouse
							 to the cat. thats how the cat(min player) will choose
							 the minimum distance to the mouse.
							 If it is cat we find the shortest path from the cat 
							 to the mouse and the shortest path from the mouse
							 to the cheese. the mouse (max player) will choose the
							 minimum distance to the cheese (1/shortest path to cheese)*10
							 and the maximum distance from the cat
	running time - according to the level (level=seconds)

##########################################################################################
