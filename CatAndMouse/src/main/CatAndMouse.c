#include "CatAndMouse.h"




int main(int argc, char* argv[]) {
	if (argc == 1) { //there isn't a parameter to the program. then initiallize the gui
		initGUI();
	} 
	else if (argc == 3){
		if (!strcmp(argv[1], "-console"))
		{
			if ((!strcmp(argv[2], "mouse")) || (!strcmp(argv[2], "cat")))
				{
					handle_event_console();
				}
			else
			{
				printf("%s","the arguments to the program are not valid\n");
				exit(1);
			}
		}
		else
		{
			printf("%s","the arguments to the program are not valid\n");
			exit(1);
		}
	}
	else{ //if the argument are not valid to the program - quit
		printf("%s","the number of arguments to the program is not valid\n");
		exit(1);
	}
	return 0;
}






