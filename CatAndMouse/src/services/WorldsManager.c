#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "WorldsManager.h"

result LoadWorldFromFile(modelBoard* model, char* name) {
	result res;


    FILE *fp = NULL;
	char input[100];
    char c;

    char buf[100] = "";
    strcat(buf, "./worlds/");
    strcat(buf, name);

    if((fp = fopen(buf, "r")) == NULL) {
        res.code = ERROR;
        res.message = "File not exist";
        return res;
    }

    // read num of steps
    fscanf(fp,"%s", input);
    model->movesBeforeTie = atoi(input);

    // read who start
    fscanf(fp,"%s", input);
    if (input[0] = 'c')
    	model->currentPlayer = CAT;
    else
    	model->currentPlayer = MOUSE;

    for (int row = 0; row < GRID_SIZE; row++) {
    	fscanf(fp,"%s", input);

    	for(int col = 0; col < GRID_SIZE; col++) {
    		c = input[col];

    		switch (c) {
    			case(WALL_CELL):
    				model->board[row][col] = WALL;
    				break;
    			case(CAT_CELL):
    				model->board[row][col] = CAT_PIC;
    				model->players[CAT].playerPos.x = row;
    				model->players[CAT].playerPos.y = col;
    				break;
    			case(MOUSE_CELL):
					model->board[row][col] = MOUSE_PIC;
					model->players[MOUSE].playerPos.x = row;
					model->players[MOUSE].playerPos.y = col;
					break;
    			case(CHEESE_CELL):
    				model->board[row][col] = CHEESE;
    				model->cheesePos.x = row;
    				model->cheesePos.y = col;
    				break;
    			default:
    				model->board[row][col] = EMPTY;
    				break;
    		}
    	}
    }

   if(fclose(fp)) {
		res.code = ERROR;
		res.message = "Error closing file";
		return res;
   }

	res.code = SUCCESS; //to delete! it is just for compilation
	res.message = "";
	return res;
}


result SaveWorldToFile(modelBoard* model, char* name) {
	result res;

    FILE *fp = NULL;

    char buf[100] = "";
    strcat(buf, "./worlds/");
    strcat(buf, name);

    if((fp = fopen(buf, "wt")) == NULL) {
        res.code = ERROR;
        res.message = "File not exist";
        return res;
    }

    fflush(stdin); //cleaning the buffer

    fprintf(fp,"%d",model->movesBeforeTie);
    fprintf(fp,"%c", '\n');

    if (model->currentPlayer == CAT)
    	fprintf(fp, "%s", CAT_START);
    else
    	fprintf(fp, "%s", MOUSE_START);

    for (int row = 0; row < GRID_SIZE; row++) {
    	fprintf(fp, "%c", '\n');
    	for(int col = 0; col < GRID_SIZE; col++) {
    		switch (model->board[row][col]) {
    			case(WALL):
					fprintf(fp, "%c", 'W');
    				break;
    			case(CAT_PIC):
					fprintf(fp, "%c", 'C');
    				break;
    			case(MOUSE_PIC):
					fprintf(fp, "%c", 'M');
					break;
    			case(CHEESE):
					fprintf(fp, "%c", 'P');
    				break;
    			default:
    				fprintf(fp, "%c", '#');
    				break;
    		}
    	}
	}

    if(fclose(fp)) {
 		res.code = ERROR;
 		res.message = "Error closing file";
 		return res;
    }


	res.code = SUCCESS;//to delete! it is just for compilation
	res.message = "";
	return res;
}
