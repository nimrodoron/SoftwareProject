#include "CatAndMouseMiniMax.h"

/* this function gets the best move for the current player 
according the current state of the game and set_number_steps*/
int getBestMove(modelBoard* currentState,int numSteps) {
	int isMaxPlayer =0;
	if (currentState->currentPlayer==MAX_PLAYER) isMaxPlayer=1;
	return (getBestChild(currentState,numSteps,getChildren,FreeState,evaluate,isMaxPlayer,MIN_EVALUATION,MAX_EVALUATION).index);
	}

/*this function evaluates the score of the game */
int evaluate(void* state) {

	int result;
	int** graph;
	int** GraphforCat;
	int** GraphForMouse;

	modelBoard* mboard = (modelBoard*)state;
	//type** board = mboard->board;

	if (mboard->isValid) {

		// If it is the min player (Cat)
		if (mboard->currentPlayer == CAT) {
			if (ChceckNeighbours(mboard->board,
								 mboard->players[CAT].playerPos.x,
								 mboard->players[CAT].playerPos.y,
								 MOUSE_PIC))
				return MIN_EVALUATION;

			if (ChceckNeighbours(mboard->board,
											 mboard->players[MOUSE].playerPos.x,
											 mboard->players[MOUSE].playerPos.y,
											 CHEESE))
				return MAX_EVALUATION;

			GraphForMouse = GenerateGraphFromMatrix(mboard,CAT_PIC);
			int pathCatFromMouse = findShortPath(GraphForMouse, mboard->players[MOUSE].playerPos.x,
								 mboard->players[MOUSE].playerPos.y,
								 mboard->players[CAT].playerPos.x,
								 mboard->players[CAT].playerPos.y);

			GraphforCat = GenerateGraphFromMatrix(mboard,CHEESE);
			int pathCatFromCheese = findShortPath(GraphforCat, mboard->players[MOUSE].playerPos.x,
					 mboard->players[MOUSE].playerPos.y,
					 mboard->cheesePos.x,
					 mboard->cheesePos.y);

			destryGraph(GraphForMouse);
			destryGraph(GraphforCat);
			return (int)(pathCatFromMouse+(1/pathCatFromCheese)*10);
		}
		// if it is the max player (Mouse)
		else
		{
			if (ChceckNeighbours(mboard->board,
											 mboard->players[CAT].playerPos.x,
											 mboard->players[CAT].playerPos.y,
											 MOUSE_PIC))
							return MIN_EVALUATION;

						if (ChceckNeighbours(mboard->board,
														 mboard->players[MOUSE].playerPos.x,
														 mboard->players[MOUSE].playerPos.y,
														 CHEESE))
							return MAX_EVALUATION;

			// find shortest path from the mouse to the cat
			graph = GenerateGraphFromMatrix(mboard,CAT_PIC);
			int path = findShortPath(graph, mboard->players[MOUSE].playerPos.x,
									 mboard->players[MOUSE].playerPos.y,
									 mboard->players[CAT].playerPos.x,
									 mboard->players[CAT].playerPos.y);
			destryGraph(graph);

			return path;
		}

	}
	else { // In case the board is not valid
		if (((modelBoard*)state)->currentPlayer == MIN_PLAYER) result = MIN_EVALUATION;
		if (((modelBoard*)state)->currentPlayer == MAX_PLAYER) result = MAX_EVALUATION;
	}

	return result;
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

	    if (movePlayerTo(childstateRef,x-1,y)) {
	    	childstateRef->isValid = true;
	    }
	    childstateRef->currentPlayer = !childstateRef->currentPlayer;
	    tempList = append(list,childstateRef);


	    // try move down
	    copyModel(&childstateRef,state);
	    childstateRef->isValid = false;
	    if (movePlayerTo(childstateRef,x+1,y)) {
	    	childstateRef->isValid = true;
	    }
	    childstateRef->currentPlayer = !childstateRef->currentPlayer;
	    tempList = append(tempList,childstateRef);

	    // try move left
	    copyModel(&childstateRef,state);
	    childstateRef->isValid = false;
	    //childstateRef->currentPlayer = !childstateRef->currentPlayer;
	    if (movePlayerTo(childstateRef,x,y-1)) {
	    	childstateRef->isValid = true;
	    }
	    childstateRef->currentPlayer = !childstateRef->currentPlayer;
	    tempList = append(tempList,childstateRef);

	    // try move right
	    copyModel(&childstateRef,state);
	    childstateRef->isValid = false;
	    //childstateRef->currentPlayer = !childstateRef->currentPlayer;
	    if (movePlayerTo(childstateRef,x,y+1)) {
	    	childstateRef->isValid = true;
	    }
	    childstateRef->currentPlayer = !childstateRef->currentPlayer;
	    tempList = append(tempList,childstateRef);
	}

	return list;
}

void FreeState(void* state) {
	modelBoard* mb = ((modelBoard*)state);
	freeModel(&mb);
}

/*this function checking if there is a winner */
playerAnimal checkForWinner(modelBoard* currentState) {
	if (evaluate(currentState) == MAX_EVALUATION) return MAX_PLAYER;
	if (evaluate(currentState) == MIN_EVALUATION) return MIN_PLAYER;
	return NONE;
}

int** GenerateGraphFromMatrix(modelBoard* model, type toType) {
	int in;
	int jn;
	int** graph;

	graph = (int**)malloc(49*sizeof(int*));
	for (int i=0; i<49; i++) {
		graph[i]= (int*)malloc(49*sizeof(int));
	}

	for (int i=0;i<49; i++)
		for (int j=0;j<49;j++)
			graph[i][j] = 0;

	for (int i=0; i<GRID_SIZE; i++) {
		for (int j=0; j<GRID_SIZE; j++) {
			if (model->board[i][j] != WALL) {
				// Top neighbour
				in = i-1;
				jn = j;
				if ((in>=0) && (in<GRID_SIZE) && (jn>=0) && (jn<GRID_SIZE))
					if ((model->board[in][jn] == EMPTY) || (model->board[in][jn] == toType))
							graph[i*GRID_SIZE+j][in*GRID_SIZE+jn] = 1;
				// Left
				in = i;
				jn = j-1;
				if ((in>=0) && (in<GRID_SIZE) && (jn>=0) && (jn<GRID_SIZE))
					if ((model->board[in][jn] == EMPTY) || (model->board[in][jn] == toType))
							graph[i*GRID_SIZE+j][in*GRID_SIZE+jn] = 1;
				// right;
				in = i;
				jn = j+1;
				if ((in>=0) && (in<GRID_SIZE) && (jn>=0) && (jn<GRID_SIZE))
					if ((model->board[in][jn] == EMPTY) || (model->board[in][jn] == toType))
							graph[i*GRID_SIZE+j][in*GRID_SIZE+jn] = 1;
				// down
				in = i+1;
				jn = j;
				if ((in>=0) && (in<GRID_SIZE) && (jn>=0) && (jn<GRID_SIZE))
					if ((model->board[in][jn] == EMPTY) || (model->board[in][jn] == toType))
							graph[i*GRID_SIZE+j][in*GRID_SIZE+jn] = 1;
			}
		}
	}
	return graph;
}

void destryGraph(int** graph) {
	for (int i=0; i<49; i++) {
			free(graph[i]);
	}
	free(graph);
}

int findShortPath(int** matrix, int s_row, int s_col, int d_row, int d_col)
{
	int q[49],visited[49],f=0,r=-1, dis[49];
	for(int i=0;i<49;i++)
	 {
	  q[i]=-1;
	  visited[i]=NOT_VISIT;
	  dis[i]=0;
	 }

	bfs(s_row*GRID_SIZE+s_col,matrix,visited,q,49,f,r,dis);

	return dis[d_row*GRID_SIZE+d_col];
}

void bfs(int v, int** a,int visited[], int q[], int n, int f,int r, int dis[])
{
	int i;

	for(i=0;i<n;i++) {
		if((a[v][i]) && (visited[i] == NOT_VISIT)) {
			q[++r]=i;
			dis[i] = dis[v]+1;
			visited[i] = IN_QUEUE;
		}
	}

	visited[v] = COMPLETED;

	if(f<=r)
	{
		visited[q[f]]=COMPLETED;
		bfs(q[f++],a,visited,q,n,f,r,dis);
	}
}

bool ChceckNeighbours(type** board, int i,int j, type type) {
	int in;
	int jn;

	// Top neighbour
	in = i-1;
	jn = j;
	if ((in>=0) && (in<GRID_SIZE) && (jn>=0) && (jn<GRID_SIZE))
		if (board[in][jn] == type)
			return true;
	// Left
	in = i;
	jn = j-1;
	if ((in>=0) && (in<GRID_SIZE) && (jn>=0) && (jn<GRID_SIZE))
			if (board[in][jn] == type)
				return true;
	// right;
	in = i;
	jn = j+1;
	if ((in>=0) && (in<GRID_SIZE) && (jn>=0) && (jn<GRID_SIZE))
			if (board[in][jn] == type)
				return true;
	// down
	in = i+1;
	jn = j;
	if ((in>=0) && (in<GRID_SIZE) && (jn>=0) && (jn<GRID_SIZE))
			if (board[in][jn] == type)
				return true;

	return false;
}

