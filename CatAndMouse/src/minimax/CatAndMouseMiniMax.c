#include "CatAndMouseMiniMax.h"

//const int constantVector[CONST_VECTOR_SIZE] = {-5,-2,-1,0,1,2,5};

/* this function gets the best move for the current player 
according the current state of the game and set_number_steps*/
int getBestMove(modelBoard* currentState,int numSteps) {
	int isMaxPlayer =0;
	if (currentState.currentPlayer==MAX_PLAYER) isMaxPlayer=1;
	return (getBestChild(currentState,numSteps,getChildren,FreeState,evaluate,isMaxPlayer).index);
	}

/*this function evaluates the score of the game */
int evaluate(void* state) {
//	int scoresTable[SCORES_TABLES_SIZE] = {0,0,0,0,0,0,0,0,0};
//	int score;
//	int value;
//	int result;
//
//	if (((StateOfBoard*)state)->isValid) {
//		for (int row=0; row<MAT_ROWS; row++) {
//			for (int col=0; col<MAT_COLS; col++) {
//
//				// Check horizontal
//				if (col <= MAT_COLS-WIN_SEQ_SIZE)
//				{
//					score = 0;
//					for (int colIndex=0; colIndex<WIN_SEQ_SIZE; colIndex++)
//					{
//						value = ((StateOfBoard*)state)->boradMatrix[row][col+colIndex];
//						if (value == MAX_PLAYER) score += MAX_PLAYER;
//						if (value == MIN_PLAYER) score += MIN_PLAYER;
//					}
//					scoresTable[score+WIN_SEQ_SIZE] += 1;
//				}
//				// Check vertical
//				if (row <= MAT_ROWS-WIN_SEQ_SIZE)
//				{
//					score = 0;
//					for (int rowIndex=0; rowIndex<WIN_SEQ_SIZE; rowIndex++)
//					{
//						value = ((StateOfBoard*)state)->boradMatrix[row+rowIndex][col];
//						if (value == MAX_PLAYER) score += MAX_PLAYER;
//						if (value == MIN_PLAYER) score += MIN_PLAYER;
//					}
//					scoresTable[score+WIN_SEQ_SIZE] += 1;
//				}
//
//				// Check Diagonal right down
//				if (col <= MAT_COLS-WIN_SEQ_SIZE && row <= MAT_ROWS-WIN_SEQ_SIZE)
//				{
//					score = 0;
//					for (int appendIndex=0; appendIndex<WIN_SEQ_SIZE; appendIndex++)
//					{
//						value = ((StateOfBoard*)state)->boradMatrix[row+appendIndex][col+appendIndex];
//						if (value == MAX_PLAYER) score += MAX_PLAYER;
//						if (value == MIN_PLAYER) score += MIN_PLAYER;
//					}
//					scoresTable[score+WIN_SEQ_SIZE] += 1;
//				}
//
//				// Check Diagonal left down
//				if ((col >= MAT_COLS-WIN_SEQ_SIZE) && (row <= MAT_ROWS-4))
//				{
//					int tempRow = row;
//					int tempCol = col;
//					score = 0;
//					value = ((StateOfBoard*)state)->boradMatrix[tempRow][tempCol];
//					if (value == MAX_PLAYER) score += MAX_PLAYER;
//					if (value == MIN_PLAYER) score += MIN_PLAYER;
//					for (int index=1; index < WIN_SEQ_SIZE; index ++)
//					{
//						tempRow++;
//						tempCol--;
//						value = ((StateOfBoard*)state)->boradMatrix[tempRow][tempCol];
//						if (value == MAX_PLAYER) score += MAX_PLAYER;
//						if (value == MIN_PLAYER) score += MIN_PLAYER;
//					}
//					scoresTable[score+WIN_SEQ_SIZE] += 1;
//				}
//			}
//		}
//		/*if there is a winner*/
//		if (scoresTable[MIN_4_SCORE+4] >= 1) {
//			return MIN_EVALUATION;
//		}
//		if (scoresTable[MAX_4_SCORE+4] >= 1) {
//			return MAX_EVALUATION;
//		}
//
//		// calculate the score
//		result = 0;
//		for (int i=0; i<CONST_VECTOR_SIZE; i++)
//		{
//			if ((i+1) != WIN_SEQ_SIZE) result += scoresTable[i+1]*constantVector[i];
//		}
//	}
//	else { // In case the board is not valid (couldn't add disc)
//		if (((StateOfBoard*)state)->player == MIN_PLAYER) result = MIN_EVALUATION;
//		if (((StateOfBoard*)state)->player == MAX_PLAYER) result = MAX_EVALUATION;
//	}
//
//	return result;
}

/*this function returns the children of the current node, as a list*/
ListRef getChildren(void* state) {

	// this may actually return NULL if inner malloc call fails!
	ListRef list = newList(NULL);
	ListRef tempList = NULL;
	modelBoard *childstateRef;
	if (((modelBoard*)state)->isValid) {

	    int x = ((modelBoard*)state)->players[((modelBoard*)state)->currentPlayer].playerPos.x;
		int y = ((modelBoard*)state)->players[((modelBoard*)state)->currentPlayer].playerPos.y;

	    // try move up
	    copyModel(&childstateRef,state);
	    childstateRef->isValid = false;
	    childstateRef->currentPlayer = !childstateRef->currentPlayer;
	    if (movePlayerTo(x-1,y)) {
	    	childstateRef->isValid = true;
	    }
	    tempList = append(list,childstateRef);

	    // try move down
	    copyModel(&childstateRef,state);
	    childstateRef->isValid = false;
	    childstateRef->currentPlayer = !childstateRef->currentPlayer;
	    if (movePlayerTo(x+1,y)) {
	    	childstateRef->isValid = true;
	    }
	    tempList = append(tempList,childstateRef);

	    // try move left
	    copyModel(&childstateRef,state);
	    childstateRef->isValid = false;
	    childstateRef->currentPlayer = !childstateRef->currentPlayer;
	    if (movePlayerTo(x,y-1)) {
	    	childstateRef->isValid = true;
	    }
	    tempList = append(tempList,childstateRef);

	    // try move right
	    copyModel(&childstateRef,state);
	    childstateRef->isValid = false;
	    childstateRef->currentPlayer = !childstateRef->currentPlayer;
	    if (movePlayerTo(x,y+1)) {
	    	childstateRef->isValid = true;
	    }
	    tempList = append(tempList,childstateRef);
	}

	return list;
}

void FreeState(void* state) {
	freeModel(&state);
	free((modelBoard*)state);
}

/*this function checking if there is a winner */
playerAnimal checkForWinner(modelBoard* currentState) {
	//if (evaluate(currentState) == MAX_EVALUATION) return MAX_PLAYER;
	//if (evaluate(currentState) == MIN_EVALUATION) return MIN_PLAYER;
	return NONE;
}


